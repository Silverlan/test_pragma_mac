/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2020 Florian Weischer
 */

#include "stdafx_cengine.h"
#include "pragma/rendering/c_render_context.hpp"
#include "pragma/rendering/render_apis.hpp"
#include <prosper_util.hpp>
#include <debug/prosper_debug.hpp>
#include <shader/prosper_shader.hpp>
#include <sharedutils/util_library.hpp>
#include <pragma/util/util_module.hpp>
#include <pragma/lua/lua_error_handling.hpp>

using namespace pragma;

extern DLLCLIENT CEngine *c_engine;

RenderContext::RenderContext()
	: m_monitor(nullptr),m_aspectRatio(1.f),m_renderAPI{"vulkan"}
{
	umath::set_flag(m_stateFlags,StateFlags::WindowedMode);
}
RenderContext::~RenderContext()
{
	m_graphicsAPILib = nullptr;
}
void RenderContext::InitializeRenderAPI()
{
	auto &renderAPI = GetRenderAPI();
	auto getRenderApiPath = [](const std::string &renderAPI,std::string &outLocation,std::string &outModulePath) {
		outLocation = pragma::rendering::get_graphics_api_module_location(renderAPI);
		outModulePath = util::get_normalized_module_path(outLocation);
	};
	auto loadRenderApiModule = [this,&getRenderApiPath](const std::string &renderAPI) -> bool {
		std::string location;
		std::string modulePath;
		getRenderApiPath(renderAPI,location,modulePath);
		m_graphicsAPILib = util::load_library_module(modulePath,util::get_default_additional_library_search_directories(modulePath));
		return (m_graphicsAPILib != nullptr);
	};
	if(loadRenderApiModule(renderAPI) == false)
	{
		// Fallback
		SetRenderAPI("vulkan");
		if(loadRenderApiModule(renderAPI) == false)
		{
			SetRenderAPI("opengl");
			loadRenderApiModule(renderAPI);
		}
	}
	auto lib = m_graphicsAPILib;
	std::string location;
	std::string modulePath;
	getRenderApiPath(renderAPI,location,modulePath);

	std::string err;
	if(lib != nullptr)
	{
		auto fInitRenderAPI = lib->FindSymbolAddress<bool(*)(const std::string&,bool,std::shared_ptr<prosper::IPrContext>&,std::string&)>("initialize_render_api");
		if(fInitRenderAPI == nullptr)
			err = "Symbol 'initialize_render_api' not found in library '" +location +"'!";
		else
		{
			std::string errMsg;
			auto success = fInitRenderAPI(engine_info::get_name(),false,m_renderContext,errMsg);
			if(success == false)
				err = errMsg;
		}
	}
	else
		err = "Module '" +modulePath +"' not found!";
	if(m_renderContext == nullptr)
		throw std::runtime_error{"Unable to load Vulkan implementation library for Prosper: " +err +"!"};

	prosper::Callbacks callbacks {};
	callbacks.validationCallback = [this](prosper::DebugMessageSeverityFlags severityFlags,const std::string &message) {
		ValidationCallback(severityFlags,message);
	};
	callbacks.onWindowInitialized = [this]() {OnWindowInitialized();};
	callbacks.onClose = [this]() {OnClose();};
	callbacks.onResolutionChanged = [this](uint32_t w,uint32_t h) {OnResolutionChanged(w,h);};
	callbacks.drawFrame = [this](prosper::IPrimaryCommandBuffer &drawCmd,uint32_t swapchainImageIdx) {DrawFrame(drawCmd,swapchainImageIdx);};
	m_renderContext->SetCallbacks(callbacks);
	if(umath::is_flag_set(m_stateFlags,StateFlags::GfxAPIValidationEnabled))
		m_renderContext->SetValidationEnabled(true);

	GetRenderContext().GetWindowCreationInfo().resizable = false;
	prosper::Shader::SetLogCallback([](prosper::Shader &shader,prosper::ShaderStage stage,const std::string &infoLog,const std::string &debugInfoLog) {
		Con::cwar<<"Unable to load shader '"<<shader.GetIdentifier()<<"':"<<Con::endl;
		Con::cwar<<"Shader Stage: "<<prosper::util::to_string(stage)<<Con::endl;
		auto filePath = (stage != prosper::ShaderStage::Unknown) ? shader.GetStageSourceFilePath(stage) : std::optional<std::string>{};
		if(filePath.has_value())
			Con::cwar<<"Shader Stage Filename: "<<*filePath<<Con::endl;
		Con::cwar<<infoLog<<Con::endl<<Con::endl;
		Con::cwar<<debugInfoLog<<Con::endl;
		});
	prosper::debug::set_debug_validation_callback([](prosper::DebugReportObjectTypeEXT objectType,const std::string &msg) {
		Con::cerr<<"[PR] "<<msg<<Con::endl;
		});
	GLFW::initialize();
}
void RenderContext::Release()
{
	if(m_renderContext == nullptr)
		return;
	GetRenderContext().Close();
	m_renderContext = nullptr;
}
const prosper::IPrContext &RenderContext::GetRenderContext() const {return const_cast<RenderContext*>(this)->GetRenderContext();}
prosper::IPrContext &RenderContext::GetRenderContext() {return *m_renderContext;}
prosper::ShaderManager &RenderContext::GetShaderManager() const {return GetRenderContext().GetShaderManager();}
void RenderContext::RegisterShader(const std::string &identifier,const std::function<prosper::Shader*(prosper::IPrContext&,const std::string&)> &fFactory)
{
	GetRenderContext().RegisterShader(identifier,fFactory);
}
::util::WeakHandle<prosper::Shader> RenderContext::GetShader(const std::string &identifier) const
{
	return GetRenderContext().GetShader(identifier);
}

GLFW::Window &RenderContext::GetWindow() {return GetRenderContext().GetWindow();}
const std::shared_ptr<prosper::IPrimaryCommandBuffer> &RenderContext::GetSetupCommandBuffer() {return GetRenderContext().GetSetupCommandBuffer();}
const std::shared_ptr<prosper::IPrimaryCommandBuffer> &RenderContext::GetDrawCommandBuffer() const {return GetRenderContext().GetDrawCommandBuffer();}
const std::shared_ptr<prosper::IPrimaryCommandBuffer> &RenderContext::GetDrawCommandBuffer(uint32_t swapchainIdx) const {return GetRenderContext().GetDrawCommandBuffer(swapchainIdx);}
void RenderContext::FlushSetupCommandBuffer() {GetRenderContext().FlushSetupCommandBuffer();}
void RenderContext::ValidationCallback(
	prosper::DebugMessageSeverityFlags severityFlags,
	const std::string &message
)
{
	if((severityFlags &(prosper::DebugMessageSeverityFlags::ErrorBit | prosper::DebugMessageSeverityFlags::WarningBit)) != prosper::DebugMessageSeverityFlags::None)
	{
		std::string strMsg = message;
		// A VkImageStencilUsageCreateInfoEXT error is caused due to a bug in Anvil: https://github.com/GPUOpen-LibrariesAndSDKs/Anvil/issues/153
		// We'll just ignore it for now, since it doesn't affect us in any way.
		// TODO: Remove this condition once the Anvil bug has been dealt with.
		if(strMsg.find("value of stencilUsage must not be 0. The Vulkan spec states: stencilUsage must not be 0") != std::string::npos)
			return;
		Con::cerr<<"[PR] "<<strMsg<<Con::endl;
		if(std::this_thread::get_id() == c_engine->GetMainThreadId())
		{
			// In many cases the error may have been caused by a Lua script, so we'll print
			// some information here about the current Lua call stack.
			auto *cl = c_engine->GetClientState();
			auto *game = cl ? static_cast<CGame*>(cl->GetGameState()) : nullptr;
			auto *l = game ? game->GetLuaState() : nullptr;
			if(l)
			{
				std::stringstream ss;
				if(Lua::get_callstack(l,ss))
					Con::cerr<<"Lua callstack: "<<ss.str()<<Con::endl;
			}
		}
	}
}

void RenderContext::OnClose() {}

void RenderContext::OnResolutionChanged(uint32_t w,uint32_t h) {}
void RenderContext::DrawFrame(prosper::IPrimaryCommandBuffer &drawCmd,uint32_t swapchainImageIdx) {}
void RenderContext::OnWindowInitialized() {m_scheduledWindowReloadInfo = nullptr;}

void RenderContext::DrawFrame()
{
	UpdateWindow();
	GetRenderContext().DrawFrame();
}

void RenderContext::UpdateWindow()
{
	if(m_scheduledWindowReloadInfo == nullptr)
		return;
	GetRenderContext().WaitIdle();
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(m_scheduledWindowReloadInfo->windowedMode.has_value())
		umath::set_flag(m_stateFlags,StateFlags::WindowedMode,*m_scheduledWindowReloadInfo->windowedMode);
	if(m_scheduledWindowReloadInfo->refreshRate.has_value())
		creationInfo.refreshRate = (*m_scheduledWindowReloadInfo->refreshRate != 0u) ? static_cast<int32_t>(*m_scheduledWindowReloadInfo->refreshRate) : GLFW_DONT_CARE;
	if(m_scheduledWindowReloadInfo->decorated.has_value())
		creationInfo.decorated = *m_scheduledWindowReloadInfo->decorated;
	if(m_scheduledWindowReloadInfo->width.has_value())
		creationInfo.width = *m_scheduledWindowReloadInfo->width;
	if(m_scheduledWindowReloadInfo->height.has_value())
		creationInfo.height = *m_scheduledWindowReloadInfo->height;
	m_aspectRatio = CFloat(creationInfo.width) /CFloat(creationInfo.height);
	if(m_scheduledWindowReloadInfo->monitor.has_value())
		creationInfo.monitor = std::move(*m_scheduledWindowReloadInfo->monitor);
	if(m_scheduledWindowReloadInfo->presentMode.has_value())
		GetRenderContext().SetPresentMode(*m_scheduledWindowReloadInfo->presentMode);
	m_scheduledWindowReloadInfo = nullptr;
	if(umath::is_flag_set(m_stateFlags,StateFlags::WindowedMode) == false)
	{
		if(creationInfo.monitor == nullptr)
			creationInfo.monitor = std::make_unique<GLFW::Monitor>(GLFW::get_primary_monitor());
	}
	else
		creationInfo.monitor = nullptr;
	GetRenderContext().ReloadWindow();
}
RenderContext::WindowChangeInfo &RenderContext::ScheduleWindowReload()
{
	if(m_scheduledWindowReloadInfo == nullptr)
		m_scheduledWindowReloadInfo = std::unique_ptr<WindowChangeInfo>(new WindowChangeInfo{});
	return *m_scheduledWindowReloadInfo;
}
void RenderContext::SetGfxAPIValidationEnabled(bool b) {umath::set_flag(m_stateFlags,StateFlags::GfxAPIValidationEnabled,b);}
void RenderContext::SetMonitor(GLFW::Monitor &monitor)
{
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(&monitor == creationInfo.monitor.get())
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.monitor = std::make_unique<GLFW::Monitor>(monitor);
}
void RenderContext::SetPresentMode(prosper::PresentModeKHR presentMode)
{
	if(presentMode == GetRenderContext().GetPresentMode())
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.presentMode = presentMode;
}
void RenderContext::SetWindowedMode(bool b)
{
	if(b == umath::is_flag_set(m_stateFlags,StateFlags::WindowedMode))
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.windowedMode = b;
}
void RenderContext::SetRefreshRate(uint32_t rate)
{
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(rate == creationInfo.refreshRate)
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.refreshRate = rate;
}
void RenderContext::SetNoBorder(bool b)
{
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(!b == creationInfo.decorated)
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.decorated = !b;
}
void RenderContext::SetResolution(const Vector2i &sz)
{
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(sz.x == creationInfo.width && sz.y == creationInfo.height)
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.width = sz.x;
	changeInfo.height = sz.y;
}
void RenderContext::SetResolutionWidth(uint32_t w)
{
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(w == creationInfo.width)
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.width = w;
}
void RenderContext::SetResolutionHeight(uint32_t h)
{
	auto &creationInfo = GetRenderContext().GetWindowCreationInfo();
	if(h == creationInfo.height)
		return;
	auto &changeInfo = ScheduleWindowReload();
	changeInfo.width = h;
}
float RenderContext::GetAspectRatio() const {return m_aspectRatio;}
void RenderContext::SetRenderAPI(const std::string &renderAPI) {m_renderAPI = renderAPI;}
const std::string &RenderContext::GetRenderAPI() const {return m_renderAPI;}
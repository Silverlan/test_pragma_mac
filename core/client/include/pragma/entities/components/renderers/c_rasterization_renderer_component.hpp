/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2020 Florian Weischer
 */

#ifndef __C_RASTERIZATION_RENDERER_COMPONENT_HPP__
#define __C_RASTERIZATION_RENDERER_COMPONENT_HPP__

#include "pragma/clientdefinitions.h"
#include <pragma/entities/components/base_entity_component.hpp>
#include "pragma/entities/c_baseentity.h"
#include "pragma/rendering/renderers/base_renderer.hpp"
#include "pragma/entities/components/renderers/rasterization/glow_data.hpp"
#include "pragma/entities/components/renderers/rasterization/hdr_data.hpp"
#include "pragma/entities/components/renderers/rasterization/glow_data.hpp"
#include "pragma/entities/components/renderers/rasterization/hdr_data.hpp"
#include "pragma/rendering/c_rendermode.h"
#include <unordered_set>
#include <prosper_swap_command_buffer.hpp>
#include <mathutil/plane.hpp>
#include <sharedutils/util_weak_handle.hpp>
#include <string>
#include <vector>

#define DEBUG_RENDER_PERFORMANCE_TEST_ENABLED 0

namespace prosper
{
	class Texture;
	class IDescriptorSetGroup;
	class IPrimaryCommandBuffer;
	class IDescriptorSet;
	class ISwapCommandBufferGroup;
};
class SSAOInfo;
namespace pragma
{
	struct DLLCLIENT RendererData
	{
		enum class Flags : uint32_t
		{
			None = 0u,
			SSAOEnabled = 1u
		};
		void SetResolution(uint32_t w,uint32_t h)
		{
			vpResolution = w<<16 | (static_cast<uint16_t>(h));
		}
		Flags flags = Flags::None;
		uint32_t vpResolution = 0;
		uint32_t tileInfo; // First 16 bits = number of tiles (x-axis), second 16 bits = tile size
		float lightmapExposurePow = 0.f;
	};

	class ShaderGameWorldLightingPass;
	class ShaderPrepassBase;
	class CLightComponent;
	class CParticleSystemComponent;
	class CLightDirectionalComponent;
	class CSkyCameraComponent;
	class CSceneComponent;
	class CRendererComponent;
	namespace rendering
	{
		class Prepass;
		class ForwardPlusInstance;
	};
	class CLightMapComponent;
	class DLLCLIENT CRasterizationRendererComponent final
		: public BaseEntityComponent
	{
	public:
		static ComponentEventId EVENT_ON_RECORD_PREPASS;
		static ComponentEventId EVENT_ON_RECORD_LIGHTING_PASS;
		static ComponentEventId EVENT_PRE_EXECUTE_PREPASS;
		static ComponentEventId EVENT_POST_EXECUTE_PREPASS;
		static ComponentEventId EVENT_PRE_EXECUTE_LIGHTING_PASS;
		static ComponentEventId EVENT_POST_EXECUTE_LIGHTING_PASS;
		static ComponentEventId EVENT_PRE_PREPASS;
		static ComponentEventId EVENT_POST_PREPASS;
		static ComponentEventId EVENT_PRE_LIGHTING_PASS;
		static ComponentEventId EVENT_POST_LIGHTING_PASS;
		static void RegisterEvents(pragma::EntityComponentManager &componentManager);

		static void UpdateLightmap(CLightMapComponent &lightMapC);
		enum class PrepassMode : uint32_t
		{
			NoPrepass = 0,
			DepthOnly,
			Extended
		};

		enum class StateFlags : uint32_t
		{
			None = 0u,
			DepthResolved = 1u,
			BloomResolved = DepthResolved<<1u,
			RenderResolved = BloomResolved<<1u,

			SSAOEnabled = RenderResolved<<1u,
			PrepassEnabled = SSAOEnabled<<1u
		};

		enum class Stage : uint8_t
		{
			Initial = 0,
			OcclusionCulling,
			CollectRenderObjects,
			Prepass,
			SSAOPass,
			LightCullingPass,
			LightingPass,
			PostProcessingPass,
			PPFog,
			PPGlow,
			PPBloom,
			PPToneMapping,
			PPFXAA,

			Final
		};

		struct DLLCLIENT LightMapInfo
		{
			~LightMapInfo()
			{
				if(cbExposure.IsValid())
					cbExposure.Remove();
			}
			std::shared_ptr<prosper::Texture> lightMapTexture = nullptr;
			util::WeakHandle<pragma::CLightMapComponent> lightMapComponent {};
			CallbackHandle cbExposure {};
		};

		CRasterizationRendererComponent(BaseEntity &ent);
		virtual luabind::object InitializeLuaObject(lua_State *l) override;
		virtual void Initialize() override;

		friend SceneRenderDesc;
		virtual ~CRasterizationRendererComponent() override;

		void ReloadPresentationRenderTarget();

		void SetPrepassMode(PrepassMode mode);
		PrepassMode GetPrepassMode() const;

		void SetLightMap(pragma::CLightMapComponent &lightMapC);
		const util::WeakHandle<pragma::CLightMapComponent> &GetLightMap() const;

		void SetShaderOverride(const std::string &srcShader,const std::string &shaderOverride);
		pragma::ShaderGameWorldLightingPass *GetShaderOverride(pragma::ShaderGameWorldLightingPass *srcShader) const;
		void ClearShaderOverride(const std::string &srcShader);

		const std::vector<umath::Plane> &GetFrustumPlanes() const;
		const std::vector<umath::Plane> &GetClippedFrustumPlanes() const;

		// SSAO
		bool IsSSAOEnabled() const;
		void SetSSAOEnabled(bool b);

		Float GetHDRExposure() const;
		Float GetMaxHDRExposure() const;
		void SetMaxHDRExposure(Float exposure);
		const rendering::HDRData &GetHDRInfo() const;
		rendering::HDRData &GetHDRInfo();
		// GlowData &GetGlowInfo();
		SSAOInfo &GetSSAOInfo();

		prosper::IDescriptorSet *GetDepthDescriptorSet() const;
		void SetFogOverride(const std::shared_ptr<prosper::IDescriptorSetGroup> &descSetGroup);
		prosper::IDescriptorSet *GetRendererDescriptorSet() const;

		pragma::rendering::Prepass &GetPrepass();
		const pragma::rendering::ForwardPlusInstance &GetForwardPlusInstance() const;
		pragma::rendering::ForwardPlusInstance &GetForwardPlusInstance();
		prosper::SampleCountFlags GetSampleCount() const;
		bool IsMultiSampled() const;

		prosper::RenderTarget *BeginRenderPass(const util::DrawSceneInfo &drawSceneInfo,prosper::IRenderPass *customRenderPass=nullptr,bool secondaryCommandBuffers=false);
		bool EndRenderPass(const util::DrawSceneInfo &drawSceneInfo);
		bool ResolveRenderPass(const util::DrawSceneInfo &drawSceneInfo);

		pragma::ShaderPrepassBase &GetPrepassShader() const;

		// Render
		void RenderParticleSystems(const util::DrawSceneInfo &drawSceneInfo,std::vector<pragma::CParticleSystemComponent*> &particles,RenderMode renderMode,Bool bloom=false,std::vector<pragma::CParticleSystemComponent*> *bloomParticles=nullptr);

		// Renders all meshes from m_glowInfo.tmpGlowMeshes, and clears the container when done
		void RenderGlowMeshes(std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd,const CSceneComponent &scene,RenderMode renderMode);

		// If this flag is set, the prepass depth buffer will be blitted into a sampleable buffer
		// before rendering, which can then be used as shader sampler input. This flag will be reset once
		// rendering has finished.
		void SetFrameDepthBufferSamplingRequired();

		prosper::IDescriptorSet *GetLightSourceDescriptorSet() const;
		prosper::IDescriptorSet *GetLightSourceDescriptorSetCompute() const;

		prosper::Shader *GetWireframeShader() const;
		void UpdateCSMDescriptorSet(pragma::CLightDirectionalComponent &lightSource);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		CRendererComponent *GetRendererComponent() {return m_rendererComponent;}
		const CRendererComponent *GetRendererComponent() const {return const_cast<CRasterizationRendererComponent*>(this)->GetRendererComponent();}

		void StartPrepassRecording(const util::DrawSceneInfo &drawSceneInfo);
		void StartLightingPassRecording(const util::DrawSceneInfo &drawSceneInfo);

		void RecordLightingPass(const util::DrawSceneInfo &drawSceneInfo);
		void ExecuteLightingPass(const util::DrawSceneInfo &drawSceneInfo);

		void UpdatePrepassRenderBuffers(const util::DrawSceneInfo &drawSceneInfo);
		void UpdateLightingPassRenderBuffers(const util::DrawSceneInfo &drawSceneInfo);
		void RecordPrepass(const util::DrawSceneInfo &drawSceneInfo);
		void ExecutePrepass(const util::DrawSceneInfo &drawSceneInfo);

		const std::shared_ptr<prosper::ISwapCommandBufferGroup> &GetPrepassCommandBufferRecorder() const {return m_prepassCommandBufferGroup;}
		const std::shared_ptr<prosper::ISwapCommandBufferGroup> &GetShadowCommandBufferRecorder() const {return m_shadowCommandBufferGroup;}
		const std::shared_ptr<prosper::ISwapCommandBufferGroup> &GetLightingPassCommandBufferRecorder() const {return m_lightingCommandBufferGroup;}

		// For internal use only
		void RenderPrepass(const util::DrawSceneInfo &drawSceneInfo);
	private:
		void UpdateRendererBuffer(std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd);
		void UpdateRenderSettings();
		bool ReloadRenderTarget(uint32_t width,uint32_t height);
		void InitializeLightDescriptorSets();
		void RecordCommandBuffers(const util::DrawSceneInfo &drawSceneInfo);
		void Render(const util::DrawSceneInfo &drawSceneInfo);

		void EndRendering();
		void BeginRendering(const util::DrawSceneInfo &drawSceneInfo);

		virtual void OnEntityComponentAdded(BaseEntityComponent &component) override;
		virtual void OnEntityComponentRemoved(BaseEntityComponent &component) override;

		prosper::RenderTarget *GetPrepassRenderTarget(const util::DrawSceneInfo &drawSceneInfo);
		prosper::RenderTarget *GetLightingPassRenderTarget(const util::DrawSceneInfo &drawSceneInfo);

		void RenderSSAO(const util::DrawSceneInfo &drawSceneInfo);
		void CullLightSources(const util::DrawSceneInfo &drawSceneInfo);
		void RenderShadows(const util::DrawSceneInfo &drawSceneInfo);
		void RenderGlowObjects(const util::DrawSceneInfo &drawSceneInfo);
		void RenderBloom(const util::DrawSceneInfo &drawSceneInfo);
		void RenderToneMapping(const util::DrawSceneInfo &drawSceneInfo,prosper::IDescriptorSet &descSetHdrResolve);
		void RenderFXAA(const util::DrawSceneInfo &drawSceneInfo);

		void RenderSceneFog(const util::DrawSceneInfo &drawSceneInfo);

		void InitializeCommandBufferGroups();

		std::shared_ptr<prosper::ISwapCommandBufferGroup> m_prepassCommandBufferGroup = nullptr;
		std::shared_ptr<prosper::ISwapCommandBufferGroup> m_shadowCommandBufferGroup = nullptr;
		std::shared_ptr<prosper::ISwapCommandBufferGroup> m_lightingCommandBufferGroup = nullptr;

		StateFlags m_stateFlags = StateFlags::PrepassEnabled;
		CRendererComponent *m_rendererComponent = nullptr;

		prosper::SampleCountFlags m_sampleCount = prosper::SampleCountFlags::e1Bit;
		std::shared_ptr<prosper::IDescriptorSetGroup> m_descSetGroupFogOverride = nullptr;

		LightMapInfo m_lightMapInfo = {};
		bool m_bFrameDepthBufferSamplingRequired = false;
		std::shared_ptr<prosper::IDescriptorSetGroup> m_dsgLights;
		std::shared_ptr<prosper::IDescriptorSetGroup> m_dsgLightsCompute;

		std::vector<pragma::CLightComponent*> m_visLightSources;
		std::vector<util::WeakHandle<pragma::CLightComponent>> m_visShadowedLights;

		// HDR
		rendering::HDRData m_hdrInfo;
		// GlowData m_glowInfo;

		// Frustum planes (Required for culling)
		std::vector<umath::Plane> m_frustumPlanes = {};
		std::vector<umath::Plane> m_clippedFrustumPlanes = {};
		void UpdateFrustumPlanes(CSceneComponent &scene);

		RendererData m_rendererData {};
		std::shared_ptr<prosper::IBuffer> m_rendererBuffer = nullptr;
		std::shared_ptr<prosper::IDescriptorSetGroup> m_descSetGroupRenderer = nullptr;

		std::unordered_map<size_t,::util::WeakHandle<prosper::Shader>> m_shaderOverrides;
		mutable ::util::WeakHandle<prosper::Shader> m_whShaderWireframe = {};
	};
};
REGISTER_BASIC_BITWISE_OPERATORS(pragma::CRasterizationRendererComponent::StateFlags)
REGISTER_BASIC_BITWISE_OPERATORS(pragma::RendererData::Flags)

class EntityHandle;
class DLLCLIENT CRasterizationRenderer
	: public CBaseEntity
{
public:
	virtual void Initialize() override;
};

#endif
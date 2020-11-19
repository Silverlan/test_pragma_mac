/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2020 Florian Weischer
 */

#ifndef __C_GAME_H__
#define __C_GAME_H__

#include "pragma/c_enginedefinitions.h"
#include "pragma/clientdefinitions.h"
#include "pragma/entities/c_world.h"
#include "pragma/entities/components/c_scene_component.hpp"
#include "pragma/rendering/c_renderflags.h"
#include "pragma/lua/c_lua_gui_manager.h"
#include "pragma/rendering/rendersystem.h"
#include "pragma/rendering/lighting/shadows/c_shadow_type.hpp"
#include "pragma/lua/c_listener_handle.hpp"
#include <material.h>
#include <pragma/game/game.h>
#include <pragma/input/inkeys.h>
#include <mathutil/color.h>
#include <pragma/util/bulletinfo.h>
#include <queue>
#include <wgui/wihandle.h>
#include <sharedutils/property/util_property.hpp>

static constexpr auto LOD_SWAP_DISTANCE = 500.f;
static constexpr auto LOD_SWAP_DISTANCE_SQR = umath::pow2(LOD_SWAP_DISTANCE);

struct DLLCLIENT KeyAction
{
	KeyAction(int key,int action)
	{
		this->key = key;
		this->action = action;
	}
	int key,action;
};

class CBaseEntity;
class WIBase;
class WIHandle;
class ShaderScreen;
class CBrushMesh;
class CModelMesh;
class CSide;
class CBaseLuaEntity;
class CMaterial;
enum class ShadowType : uint8_t;
class WorldEnvironment;
template<class T>
	class OcclusionOctree;
enum class UniformBinding : uint32_t;
namespace al {class Effect;};
namespace GLFW
{
	enum class MouseButton : uint32_t;
	enum class Key : int32_t;
	enum class KeyState : uint32_t;
	enum class Modifier : uint32_t;
};

namespace pragma
{
	namespace debug {class GPUProfilingStage;};
	namespace physics {class IVisualDebugger;};
	namespace rendering {class RenderQueueBuilder;};
	class LuaShaderManager;
	class LuaParticleModifierManager;
	class CPlayerComponent;
	class CViewModelComponent;
	class CViewBodyComponent;
	class BaseWorldComponent;
	class CListenerComponent;
	class CParticleSystemComponent;
	class CLightDirectionalComponent;
	class CCameraComponent;
	class CSceneComponent;
};
namespace uimg {class ImageBuffer; struct TextureInfo;};
namespace prosper {class DescriptorSetGroup; class IImage; class IDescriptorSet;};
namespace util {struct DrawSceneInfo;};
#pragma warning(push)
#pragma warning(disable : 4251)
class DLLCLIENT CGame
	: public Game
{
public:
	struct DLLCLIENT DroppedFile
	{
		DroppedFile(const std::string &fullPath);
		std::string fullPath;
		std::string fileName;
	};
	struct GlobalRenderSettingsBufferData
	{
		GlobalRenderSettingsBufferData();
		std::shared_ptr<prosper::IBuffer> debugBuffer = nullptr;
		std::shared_ptr<prosper::IBuffer> timeBuffer = nullptr;
		std::shared_ptr<prosper::IBuffer> csmBuffer = nullptr;
		std::shared_ptr<prosper::IDescriptorSetGroup> descSetGroup = nullptr;
	};
public:
	CGame(NetworkState *state);
	virtual ~CGame() override;
	virtual void OnRemove() override;

	enum class SoundCacheFlags : uint32_t
	{
		None = 0,
		BakeConvolution = 1,
		BakeParametric = BakeConvolution<<1,
		SaveProbeBoxes = BakeParametric<<1,

		BakeAll = BakeConvolution | BakeParametric,
		All = BakeAll | SaveProbeBoxes
	};

	// List of generic shaders used by the rendering pipeline for direct access to m_gameShaders
	enum class GameShader
	{
		Shadow = 0u,
		ShadowSpot,
		ShadowTransparent,
		ShadowTransparentSpot,
		ShadowCSM,
		ShadowCSMTransparent,

		PPFog,
		PPFXAA,
		PPTonemapping,

		Debug,
		DebugTexture,
		DebugVertex,

		Count
	};
	enum class CPUProfilingPhase : uint32_t
	{
		Present = 0u,
		BuildRenderQueue,
		Prepass,
		SSAO,
		CullLightSources,
		Shadows,
		RenderWorld,
		PostProcessing,

		Count
	};
	enum class GPUProfilingPhase : uint32_t
	{
		Scene = 0u,
		Prepass,
		SSAO,
		PostProcessing,
		Present,

		Skybox,
		World,
		Particles,
		Debug,
		Water,
		View,

		PostProcessingFog,
		PostProcessingFXAA,
		PostProcessingGlow,
		PostProcessingBloom,
		PostProcessingHDR,
		CullLightSources,
		Shadows,

		Count
	};

	void ReloadSoundCache(bool bReloadBakedCache=false,SoundCacheFlags cacheFlags=SoundCacheFlags::All,float spacing=1'024.f);
	void ClearSoundCache();

	void SetRenderClipPlane(const Vector4 &clipPlane);
	const Vector4 &GetRenderClipPlane() const;

	void ReloadMaterialShader(CMaterial *mat);
	void SetRenderModeEnabled(RenderMode renderMode,bool bEnabled);
	void EnableRenderMode(RenderMode renderMode);
	void DisableRenderMode(RenderMode renderMode);
	bool IsRenderModeEnabled(RenderMode renderMode) const;

	std::shared_ptr<prosper::IPrimaryCommandBuffer> GetCurrentDrawCommandBuffer() const;
	void InitializeLua();
	void SetupLua();
	void SetUp();
	bool IsServer();
	bool IsClient();
	bool IsInMainRenderPass() const;
	void RegisterLua();
	void RegisterLuaLibraries();
	void RegisterLuaClasses();
	void HandleLuaNetPacket(NetPacket &packet);
	void SendUserInput();
	void CreateGiblet(const GibletCreateInfo &info,pragma::CParticleSystemComponent **particle);
	virtual pragma::BaseEntityComponent *CreateLuaEntityComponent(BaseEntity &ent,std::string classname) override;
	virtual void CreateGiblet(const GibletCreateInfo &info) override;
	virtual std::shared_ptr<ModelMesh> CreateModelMesh() const override;
	virtual std::shared_ptr<ModelSubMesh> CreateModelSubMesh() const override;

	bool StartProfilingStage(GPUProfilingPhase stage);
	bool StopProfilingStage(GPUProfilingPhase stage);
	pragma::debug::ProfilingStageManager<pragma::debug::GPUProfilingStage,GPUProfilingPhase> *GetGPUProfilingStageManager();

	template<class TEfxProperties>
		std::shared_ptr<al::Effect> CreateAuxEffect(const std::string &name,const TEfxProperties &props);
	std::shared_ptr<al::Effect> GetAuxEffect(const std::string &name);

	pragma::debug::ProfilingStageManager<pragma::debug::ProfilingStage,CPUProfilingPhase> *GetProfilingStageManager();
	bool StartProfilingStage(CPUProfilingPhase stage);
	bool StopProfilingStage(CPUProfilingPhase stage);

	// Config
	Bool RawMouseInput(GLFW::MouseButton button,GLFW::KeyState state,GLFW::Modifier mods);
	Bool RawKeyboardInput(GLFW::Key key,int scanCode,GLFW::KeyState state,GLFW::Modifier mods,float magnitude=1.f);
	Bool RawCharInput(unsigned int c);
	Bool RawScrollInput(Vector2 offset);

	Bool MouseInput(GLFW::MouseButton button,GLFW::KeyState state,GLFW::Modifier mods);
	Bool KeyboardInput(GLFW::Key key,int scanCode,GLFW::KeyState state,GLFW::Modifier mods,float magnitude=1.f);
	Bool CharInput(unsigned int c);
	Bool ScrollInput(Vector2 offset);
	void OnFilesDropped(std::vector<std::string> &files);

	// Game
	void Think();
	void Tick();
	virtual bool LoadMap(const std::string &map,const Vector3 &origin={},std::vector<EntityHandle> *entities=nullptr) override;
	void BuildVMF(const char *map);
	double &ServerTime();
	void SetServerTime(double t);
	// Entities
	CBaseEntity *CreateLuaEntity(std::string classname,bool bLoadIfNotExists=false);
	CBaseEntity *CreateLuaEntity(std::string classname,unsigned int idx,bool bLoadIfNotExists=false);
	virtual CBaseEntity *GetEntity(unsigned int idx) override;
	virtual BaseEntity *GetEntityByLocalIndex(uint32_t idx) override;
	CBaseEntity *GetEntityByClientIndex(unsigned int idx);
	virtual void GetPlayers(std::vector<BaseEntity*> *ents) override;
	virtual void GetNPCs(std::vector<BaseEntity*> *ents) override;
	virtual void GetWeapons(std::vector<BaseEntity*> *ents) override;
	virtual void GetVehicles(std::vector<BaseEntity*> *ents) override;

	virtual void GetPlayers(std::vector<EntityHandle> *ents) override;
	virtual void GetNPCs(std::vector<EntityHandle> *ents) override;
	virtual void GetWeapons(std::vector<EntityHandle> *ents) override;
	virtual void GetVehicles(std::vector<EntityHandle> *ents) override;

	CBaseEntity *CreateEntity(std::string classname);
	template<class T> T *CreateEntity();
	template<class T> T *CreateEntity(unsigned int idx);
	void RemoveEntity(BaseEntity *ent);
	pragma::CListenerComponent *GetListener();
	pragma::CPlayerComponent *GetLocalPlayer();
	void SetLocalPlayer(pragma::CPlayerComponent *pl);
	void SpawnEntity(BaseEntity *ent);
	void GetEntities(std::vector<CBaseEntity*> **ents);
	void GetEntities(std::vector<BaseEntity*> **ents);
	void GetSharedEntities(std::vector<CBaseEntity*> **ents);
	void GetSharedEntities(std::vector<BaseEntity*> **ents);

	// Sockets
	void ReceiveSnapshot(NetPacket &packet);

	virtual Float GetFrictionScale() const override;
	virtual Float GetRestitutionScale() const override;

	pragma::CParticleSystemComponent *CreateParticleTracer(const Vector3 &start,const Vector3 &end,float radius=BulletInfo::DEFAULT_TRACER_RADIUS,const Color &col=BulletInfo::DEFAULT_TRACER_COLOR,float length=BulletInfo::DEFAULT_TRACER_LENGTH,float speed=BulletInfo::DEFAULT_TRACER_SPEED,const std::string &material=BulletInfo::DEFAULT_TRACER_MATERIAL,float bloomScale=BulletInfo::DEFAULT_TRACER_BLOOM);

	virtual bool IsPhysicsSimulationEnabled() const override;

	// Debug
	virtual void DrawLine(const Vector3 &start,const Vector3 &end,const Color &color,float duration=0.f) override;
	virtual void DrawBox(const Vector3 &start,const Vector3 &end,const EulerAngles &ang,const Color &color,float duration=0.f) override;
	virtual void DrawPlane(const Vector3 &n,float dist,const Color &color,float duration=0.f) override;
	void RenderDebugPhysics(std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd,pragma::CCameraComponent &cam);

	using Game::LoadNavMesh;
	const std::vector<DroppedFile> &GetDroppedFiles() const;

	void OnReceivedRegisterNetEvent(NetPacket &packet);
	virtual pragma::NetEventId SetupNetEvent(const std::string &name) override;

	void SetLODBias(int32_t bias);
	int32_t GetLODBias() const;
	uint32_t GetLOD(float dist,uint32_t maxLod=std::numeric_limits<uint32_t>::max()) const;
	LuaCallbackHandler &GetInputCallbackHandler();
	uint32_t GetMSAASampleCount();
	void SetMaterialOverride(Material *mat);
	Material *GetMaterialOverride();
	void SetColorScale(const Vector4 &col);
	Vector4 &GetColorScale();
	void SetAlphaScale(float a);
	float GetAlphaScale();
	LuaGUIManager &GetLuaGUIManager();
	pragma::LuaShaderManager &GetLuaShaderManager();
	pragma::LuaParticleModifierManager &GetLuaParticleModifierManager();
	Material *GetLoadMaterial();
	virtual bool RunLua(const std::string &lua) override;
	virtual bool InvokeEntityEvent(pragma::BaseEntityComponent &component,uint32_t eventId,int32_t argsIdx,bool bInject) override;
	void OnReceivedPlayerInputResponse(uint8_t userInputId);
	uint16_t GetLatency() const;
	// Returns the number of lost snapshot packets within the last second
	uint32_t GetLostPacketCount();

	pragma::CCameraComponent *CreateCamera(uint32_t width,uint32_t height,float fov,float nearZ,float farZ);
	pragma::CCameraComponent *CreateCamera(float aspectRatio,float fov,float nearZ,float farZ);
	pragma::CCameraComponent *GetPrimaryCamera() const;
	const pragma::CSceneComponent *GetScene() const;
	pragma::CSceneComponent *GetScene();
	const WorldEnvironment &GetWorldEnvironment() const;
	WorldEnvironment &GetWorldEnvironment();

	virtual float GetTimeScale() override;
	virtual void SetTimeScale(float t) override;
	void RequestResource(const std::string &fileName);

	void UpdateEntityModel(CBaseEntity *ent);
	pragma::CViewModelComponent *GetViewModel();
	pragma::CViewBodyComponent *GetViewBody();
	void ReloadRenderFrameBuffer();

	void RenderScenes(util::DrawSceneInfo &drawSceneInfo);
	void RenderScene(const util::DrawSceneInfo &drawSceneInfo);

	// GUI
	void PreGUIDraw(std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd);
	void PostGUIDraw(std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd);

	// HDR
	void Resize();
	Float GetHDRExposure() const;
	Float GetMaxHDRExposure() const;
	void SetMaxHDRExposure(Float exposure);

	WIBase *CreateGUIElement(std::string name,WIBase *parent=NULL);
	WIBase *CreateGUIElement(std::string name,WIHandle *hParent);
	template<class TElement>
		TElement *CreateGUIElement(WIBase *parent=NULL);
	template<class TElement>
		TElement *CreateGUIElement(WIHandle *parent);
	void Initialize();
	virtual void InitializeGame() override;

	void SetViewModelFOV(float fov);
	const util::PFloatProperty &GetViewModelFOVProperty() const;
	float GetViewModelFOV() const;
	float GetViewModelFOVRad() const;
	Mat4 GetViewModelProjectionMatrix() const;

	// Shaders
	const util::WeakHandle<prosper::Shader> &GetGameShader(GameShader shader) const;

	// Lights
	pragma::CLightDirectionalComponent *GetEnvironmentLightSource() const;
	void UpdateEnvironmentLightSource();

	// Inputs
	void SetActionInput(Action action,bool b,bool bKeepMagnitude);
	void SetActionInput(Action action,bool b,float magnitude=1.f);
	bool GetActionInput(Action action);

	// Util
	bool SaveImage(prosper::IImage &image,const std::string &fileName,const uimg::TextureInfo &imageWriteInfo) const;
	bool SaveImage(
		const std::vector<std::vector<const void*>> &imgLayerMipmapData,uint32_t width,uint32_t height,uint32_t szPerPixel,
		const std::string &fileName,const uimg::TextureInfo &imageWriteInfo,bool cubemap=false
	) const;
	bool SaveImage(uimg::ImageBuffer &imgBuffer,const std::string &fileName,const uimg::TextureInfo &imageWriteInfo,bool cubemap=false) const;

	virtual std::string GetLuaNetworkDirectoryName() const override;
	virtual std::string GetLuaNetworkFileName() const override;

	void QueueForRendering(const util::DrawSceneInfo &drawSceneInfo);
	void SetRenderScene(pragma::CSceneComponent &scene);
	void ResetRenderScene();
	pragma::CSceneComponent *GetRenderScene();
	const pragma::CSceneComponent *GetRenderScene() const;
	pragma::CCameraComponent *GetRenderCamera() const;

	pragma::rendering::RenderQueueBuilder &GetRenderQueueBuilder();
	prosper::IDescriptorSet &GetGlobalRenderSettingsDescriptorSet();
	GlobalRenderSettingsBufferData &GetGlobalRenderSettingsBufferData();
protected:
	virtual void RegisterLuaEntityComponents(luabind::module_ &gameMod) override;
	virtual void OnMapLoaded() override;
	virtual void InitializeWorldData(pragma::asset::WorldData &worldData) override;
	virtual void InitializeMapEntities(pragma::asset::WorldData &worldData,std::vector<EntityHandle> &outEnts);

	template<class T>
		void GetPlayers(std::vector<T*> *ents);
	template<class T>
		void GetNPCs(std::vector<T*> *ents);
	template<class T>
		void GetWeapons(std::vector<T*> *ents);
	template<class T>
		void GetVehicles(std::vector<T*> *ents);

	virtual void UpdateTime() override;
	virtual void OnEntityCreated(BaseEntity *ent) override;
	virtual unsigned int GetFreeEntityIndex() override;
	virtual void SetupEntity(BaseEntity *ent,unsigned int idx) override;
	virtual std::shared_ptr<pragma::EntityComponentManager> InitializeEntityComponentManager() override;
private:
	std::queue<WIHandle> m_luaGUIObjects = {};
	double m_tLastClientUpdate = 0.0;
	std::array<bool,umath::to_integral(RenderMode::Count)> m_renderModesEnabled;
	CallbackHandle m_hCbDrawFrame = {};

	CallbackHandle m_cbGPUProfilingHandle = {};
	std::unique_ptr<pragma::debug::ProfilingStageManager<pragma::debug::GPUProfilingStage,GPUProfilingPhase>> m_gpuProfilingStageManager = nullptr;
	CallbackHandle m_cbProfilingHandle = {};
	std::unique_ptr<pragma::debug::ProfilingStageManager<pragma::debug::ProfilingStage,CPUProfilingPhase>> m_profilingStageManager = nullptr;

	std::vector<DroppedFile> m_droppedFiles = {}; // Only contains files during OnFilesDropped-call

	struct DLLCLIENT MessagePacketTracker
	{
		MessagePacketTracker();
		uint8_t lastInMessageId;
		uint8_t outMessageId;
		// Looks for lost packets and updates 'lastInMessageId'
		void CheckMessages(uint8_t messageId,std::vector<double> &lostPacketTimestamps,const double &tCur);
		void CheckMessages(uint8_t messageId,std::vector<double> &lostPacketTimestamps);
		bool IsMessageInOrder(uint8_t messageId) const;
		std::array<double,std::numeric_limits<decltype(lastInMessageId)>::max() +1> messageTimestamps;
	};
	MessagePacketTracker m_snapshotTracker;
	MessagePacketTracker m_userInputTracker;
	std::vector<double> m_lostPackets;
	void UpdateLostPackets();

	std::vector<std::string> m_requestedResources;

	LuaGUIManager m_luaGUIElements = {};
	std::shared_ptr<pragma::LuaShaderManager> m_luaShaderManager = nullptr;
	std::shared_ptr<pragma::LuaParticleModifierManager> m_luaParticleModifierManager = nullptr;
	double m_tServer = 0.0;
	LuaCallbackHandler m_inputCallbackHandler;

	// Shaders
	void InitShaders();
	void LoadLuaShaders();
	void LoadLuaShader(std::string file);
	MaterialHandle m_matLoad = {};

	// FOV used for view-models
	util::PFloatProperty m_viewFov = nullptr;

	// Sound
	bool LoadAuxEffects(const std::string &fname);

	// Render
	std::vector<util::DrawSceneInfo> m_sceneRenderQueue {};
	std::shared_ptr<pragma::rendering::RenderQueueBuilder> m_renderQueueBuilder = nullptr;
	Vector4 m_clipPlane = {};
	Vector4 m_colScale = {};
	Material *m_matOverride = nullptr;
	bool m_bMainRenderPass = true;
	std::weak_ptr<prosper::IPrimaryCommandBuffer> m_currentDrawCmd = {};
	std::array<util::WeakHandle<prosper::Shader>,umath::to_integral(GameShader::Count)> m_gameShaders = {};
	void RenderScenePresent(std::shared_ptr<prosper::IPrimaryCommandBuffer> &drawCmd,prosper::Texture &texPostHdr,prosper::IImage *optOutImage,uint32_t layerId=0u);

	std::unique_ptr<GlobalRenderSettingsBufferData> m_globalRenderSettingsBufferData = nullptr;

	// Scene
	util::WeakHandle<pragma::CSceneComponent> m_scene = {};
	std::shared_ptr<WorldEnvironment> m_worldEnvironment = nullptr;

	void OnEnvironmentLightSourceChanged(pragma::CLightDirectionalComponent *oldSource,pragma::CLightDirectionalComponent *newSource);

	void CalcView();
	void CalcLocalPlayerOrientation();
	Quat m_curFrameRotationModifier = uquat::identity();
	void UpdateShaderTimeData();

	// Entities
	std::vector<CBaseEntity*> m_ents;
	std::vector<CBaseEntity*> m_shEnts;
	std::vector<CBaseEntity*> m_entsOccluded;
	std::vector<BaseEntity*> m_shBaseEnts;
	util::WeakHandle<pragma::CLightDirectionalComponent> m_hEnvLight = {};
	util::WeakHandle<pragma::CListenerComponent> m_listener = {};
	util::WeakHandle<pragma::CPlayerComponent> m_plLocal = {};
	util::WeakHandle<pragma::CViewModelComponent> m_viewModel = {};
	util::WeakHandle<pragma::CViewBodyComponent> m_viewBody = {};
	util::WeakHandle<pragma::CCameraComponent> m_primaryCamera = {};

	util::WeakHandle<pragma::CSceneComponent> m_renderScene = {};

	// Map
	virtual std::shared_ptr<pragma::nav::Mesh> LoadNavMesh(const std::string &fname) override;

	// Entities
	void GetOccludedEntities(std::vector<CBaseEntity*> &entsOccluded);

	virtual void InitializeEntityComponents(pragma::EntityComponentManager &componentManager) override;
	void InitializeWorldEnvironment();
};
REGISTER_BASIC_BITWISE_OPERATORS(CGame::SoundCacheFlags);
REGISTER_BASIC_BITWISE_OPERATORS(CGame::GameShader);
#pragma warning(pop)

template<class T>
	T *CGame::CreateEntity(unsigned int idx)
{
	T *ent = new T();
	SetupEntity(ent,idx);
	return ent;
}

template<class T>
	T *CGame::CreateEntity()
{return CreateEntity<T>(GetFreeEntityIndex());}

#endif
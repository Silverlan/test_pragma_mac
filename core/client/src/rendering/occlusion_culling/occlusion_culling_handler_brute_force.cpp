#include "stdafx_client.h"
#include "pragma/rendering/occlusion_culling/occlusion_culling_handler_brute_force.hpp"
#include "pragma/rendering/renderers/rasterization_renderer.hpp"
#include "pragma/model/c_modelmesh.h"

using namespace pragma;

extern DLLCLIENT CGame *c_game;

void OcclusionCullingHandlerBruteForce::PerformCulling(
	const pragma::rendering::RasterizationRenderer &renderer,const Vector3 &camPos,
	std::vector<OcclusionMeshInfo> &culledMeshesOut,bool cullByViewFrustum
)
{
	auto &scene = renderer.GetScene();
	//auto d = uvec::distance(m_lastLodCamPos,posCam);
	//auto bUpdateLod = (d >= LOD_SWAP_DISTANCE) ? true : false;
	culledMeshesOut.clear();

	std::vector<CBaseEntity*> *ents;
	c_game->GetEntities(&ents);
	for(auto *ent : *ents)
	{
		if(ent == nullptr)
			continue;
		auto pRenderComponent = ent->GetRenderComponent();
		if(pRenderComponent.expired())
			continue;
		bool bViewModel = false;
		std::vector<Plane> *planes = nullptr;
		if((ShouldExamine(renderer,*ent,bViewModel,cullByViewFrustum ? &planes : nullptr) == true))
		{
			//if(bUpdateLod == true) // Needs to be updated every frame (in case the entity is moving towards or away from us)
			pRenderComponent->GetModelComponent()->UpdateLOD(camPos);
			if(pRenderComponent.valid())
			{
				auto pTrComponent = ent->GetTransformComponent();
				auto &meshes = pRenderComponent->GetLODMeshes();
				auto numMeshes = meshes.size();
				auto pos = pTrComponent.valid() ? pTrComponent->GetPosition() : Vector3{};
				for(auto itMesh=meshes.begin();itMesh!=meshes.end();++itMesh)
				{
					auto *mesh = static_cast<CModelMesh*>(itMesh->get());
					if(ShouldExamine(*mesh,pos,bViewModel,numMeshes,planes) == true)
					{
						if(culledMeshesOut.capacity() -culledMeshesOut.size() == 0)
							culledMeshesOut.reserve(culledMeshesOut.capacity() +100);
						culledMeshesOut.push_back(OcclusionMeshInfo{*ent,*mesh});
					}
				}
			}
		}
	}
	//if(bUpdateLod == true)
	//	m_lastLodCamPos = posCam;
}

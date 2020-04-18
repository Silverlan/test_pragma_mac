#include "stdafx_client.h"
#include "pragma/rendering/shaders/world/c_shader_textured_alpha_transition.hpp"
#include "pragma/model/c_modelmesh.h"
#include "pragma/model/vk_mesh.h"
#include <buffers/prosper_buffer.hpp>
#include <prosper_util.hpp>
#include <prosper_descriptor_set_group.hpp>

using namespace pragma;

extern DLLCENGINE CEngine *c_engine;

decltype(ShaderTexturedAlphaTransition::VERTEX_BINDING_ALPHA) ShaderTexturedAlphaTransition::VERTEX_BINDING_ALPHA = {Anvil::VertexInputRate::VERTEX};
decltype(ShaderTexturedAlphaTransition::VERTEX_ATTRIBUTE_ALPHA) ShaderTexturedAlphaTransition::VERTEX_ATTRIBUTE_ALPHA = {VERTEX_BINDING_ALPHA,Anvil::Format::R32G32_SFLOAT};
decltype(ShaderTexturedAlphaTransition::DESCRIPTOR_SET_MATERIAL) ShaderTexturedAlphaTransition::DESCRIPTOR_SET_MATERIAL = {
	&ShaderTextured3DBase::DESCRIPTOR_SET_MATERIAL,
	{
		prosper::Shader::DescriptorSetInfo::Binding { // Diffuse Map 2
			Anvil::DescriptorType::COMBINED_IMAGE_SAMPLER,
			Anvil::ShaderStageFlagBits::FRAGMENT_BIT
		},
		prosper::Shader::DescriptorSetInfo::Binding { // Diffuse Map 3
			Anvil::DescriptorType::COMBINED_IMAGE_SAMPLER,
			Anvil::ShaderStageFlagBits::FRAGMENT_BIT
		}
	}
};
ShaderTexturedAlphaTransition::ShaderTexturedAlphaTransition(prosper::Context &context,const std::string &identifier)
	: ShaderTextured3DBase(context,identifier,"world/vs_textured_alpha_transition","world/fs_textured_alpha_transition")
{
	// SetBaseShader<ShaderTextured3DBase>();
}

std::shared_ptr<prosper::DescriptorSetGroup> ShaderTexturedAlphaTransition::InitializeMaterialDescriptorSet(CMaterial &mat)
{
	auto descSetGroup = ShaderTextured3DBase::InitializeMaterialDescriptorSet(mat,DESCRIPTOR_SET_MATERIAL);
	if(descSetGroup == nullptr)
		return nullptr;
	auto &descSet = *descSetGroup->GetDescriptorSet();

	auto *diffuseMap2 = mat.GetTextureInfo("diffusemap2");
	if(diffuseMap2 != nullptr && diffuseMap2->texture != nullptr)
	{
		auto texture = std::static_pointer_cast<Texture>(diffuseMap2->texture);
		if(texture->HasValidVkTexture())
			prosper::util::set_descriptor_set_binding_texture(descSet,*texture->GetVkTexture(),umath::to_integral(MaterialBinding::DiffuseMap2));
	}

	auto *diffuseMap3 = mat.GetTextureInfo("diffusemap3");
	if(diffuseMap3 != nullptr && diffuseMap3->texture != nullptr)
	{
		auto texture = std::static_pointer_cast<Texture>(diffuseMap3->texture);
		if(texture->HasValidVkTexture())
			prosper::util::set_descriptor_set_binding_texture(descSet,*texture->GetVkTexture(),umath::to_integral(MaterialBinding::DiffuseMap3));
	}
	return descSetGroup;
}
prosper::Shader::DescriptorSetInfo &ShaderTexturedAlphaTransition::GetMaterialDescriptorSetInfo() const {return DESCRIPTOR_SET_MATERIAL;}
void ShaderTexturedAlphaTransition::InitializeGfxPipelinePushConstantRanges(Anvil::GraphicsPipelineCreateInfo &pipelineInfo,uint32_t pipelineIdx)
{
	AttachPushConstantRange(pipelineInfo,0u,sizeof(ShaderTextured3DBase::PushConstants) +sizeof(PushConstants),Anvil::ShaderStageFlagBits::FRAGMENT_BIT | Anvil::ShaderStageFlagBits::VERTEX_BIT);
}
void ShaderTexturedAlphaTransition::InitializeGfxPipeline(Anvil::GraphicsPipelineCreateInfo &pipelineInfo,uint32_t pipelineIdx)
{
	ShaderTextured3DBase::InitializeGfxPipeline(pipelineInfo,pipelineIdx);

	AddVertexAttribute(pipelineInfo,VERTEX_ATTRIBUTE_ALPHA);
}

bool ShaderTexturedAlphaTransition::Draw(CModelSubMesh &mesh)
{
	auto numAlpha = 0;
	auto alphaBuffer = c_engine->GetDummyBuffer();
	auto &vkMesh = mesh.GetVKMesh();
	if(vkMesh != nullptr)
	{
		auto &meshAlphaBuffer = vkMesh->GetAlphaBuffer();
		if(meshAlphaBuffer != nullptr)
		{
			alphaBuffer = meshAlphaBuffer;
			numAlpha = mesh.GetAlphaCount();
		}
	}
	return RecordPushConstants(PushConstants{numAlpha},sizeof(ShaderTextured3DBase::PushConstants)) == true &&
		RecordBindVertexBuffer(alphaBuffer->GetAnvilBuffer(),VERTEX_BINDING_VERTEX.GetBindingIndex() +2u) == true &&
		ShaderTextured3DBase::Draw(mesh) == true;
}

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan */

#include "stdafx_shared.h"
#include "pragma/lua/classes/entity_components.hpp"
#include "pragma/entities/components/base_attachable_component.hpp"
#include "pragma/lua/policies/optional_policy.hpp"
#include "pragma/lua/policies/game_object_policy.hpp"
#include "pragma/lua/policies/default_parameter_policy.hpp"
#include "pragma/lua/policies/vector_policy.hpp"
#include "pragma/lua/policies/property_policy.hpp"
#include "pragma/lua/policies/pair_policy.hpp"
#include "pragma/lua/policies/shared_from_this_policy.hpp"
#include "pragma/lua/lua_component_event.hpp"
#include "pragma/entities/components/base_parent_component.hpp"
#include <udm.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/copy_policy.hpp>

namespace Lua
{
	template<class T>
		using ComponentClass = luabind::class_<T,pragma::BaseEntityComponent>;
};

namespace pragma::lua
{
	namespace base_ai_component {static void register_class(luabind::module_ &mod);};
	namespace base_animated_component {static void register_class(luabind::module_ &mod);};
	namespace base_attachable_component {static void register_class(luabind::module_ &mod);};
	namespace base_bot_component {static void register_class(luabind::module_ &mod);};
	namespace base_character_component {static void register_class(luabind::module_ &mod);};
	namespace base_color_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_box_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_cone_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_cylinder_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_line_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_plane_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_point_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_sphere_component {static void register_class(luabind::module_ &mod);};
	namespace base_debug_text_component {static void register_class(luabind::module_ &mod);};
	namespace base_decal_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_camera_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_explosion_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_filter_class_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_filter_name_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_fire_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_fog_controller_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_light_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_light_directional_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_light_point_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_light_spot_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_light_spot_vol_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_microphone_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_particle_system_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_quake_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_smoke_trail_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_soundscape_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_sound_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_sound_dsp_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_sprite_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_timescale_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_weather_component {static void register_class(luabind::module_ &mod);};
	namespace base_env_wind_component {static void register_class(luabind::module_ &mod);};
	namespace base_flammable_component {static void register_class(luabind::module_ &mod);};
	namespace base_flashlight_component {static void register_class(luabind::module_ &mod);};
	namespace base_flex_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_brush_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_button_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_kinematic_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_physics_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_portal_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_soft_physics_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_surface_material_component {static void register_class(luabind::module_ &mod);};
	namespace base_func_water_component {static void register_class(luabind::module_ &mod);};
	namespace base_gamemode_component {static void register_class(luabind::module_ &mod);};
	namespace base_generic_component {static void register_class(luabind::module_ &mod);};
	namespace base_health_component {static void register_class(luabind::module_ &mod);};
	namespace base_info_landmark_component {static void register_class(luabind::module_ &mod);};
	namespace base_io_component {static void register_class(luabind::module_ &mod);};
	namespace base_logic_relay_component {static void register_class(luabind::module_ &mod);};
	namespace base_model_component {static void register_class(luabind::module_ &mod);};
	namespace base_name_component {static void register_class(luabind::module_ &mod);};
	namespace base_networked_component {static void register_class(luabind::module_ &mod);};
	namespace base_observable_component {static void register_class(luabind::module_ &mod);};
	namespace base_ownable_component {static void register_class(luabind::module_ &mod);};
	namespace base_parent_component {static void register_class(luabind::module_ &mod);};
	namespace base_physics_component {static void register_class(luabind::module_ &mod);};
	namespace base_player_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_at_target_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_constraint_ball_socket_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_constraint_cone_twist_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_constraint_dof_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_constraint_fixed_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_constraint_hinge_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_constraint_slider_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_path_node_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_render_target_component {static void register_class(luabind::module_ &mod);};
	namespace base_point_target_component {static void register_class(luabind::module_ &mod);};
	namespace base_prop_component {static void register_class(luabind::module_ &mod);};
	namespace base_prop_dynamic_component {static void register_class(luabind::module_ &mod);};
	namespace base_prop_physics_component {static void register_class(luabind::module_ &mod);};
	namespace base_radius_component {static void register_class(luabind::module_ &mod);};
	namespace base_render_component {static void register_class(luabind::module_ &mod);};
	namespace base_score_component {static void register_class(luabind::module_ &mod);};
	namespace base_shooter_component {static void register_class(luabind::module_ &mod);};
	namespace base_skybox_component {static void register_class(luabind::module_ &mod);};
	namespace base_soft_body_component {static void register_class(luabind::module_ &mod);};
	namespace base_sound_emitter_component {static void register_class(luabind::module_ &mod);};
	namespace base_time_scale_component {static void register_class(luabind::module_ &mod);};
	namespace base_toggle_component {static void register_class(luabind::module_ &mod);};
	namespace base_touch_component {static void register_class(luabind::module_ &mod);};
	namespace base_transform_component {static void register_class(luabind::module_ &mod);};
	namespace base_trigger_gravity_component {static void register_class(luabind::module_ &mod);};
	namespace base_trigger_hurt_component {static void register_class(luabind::module_ &mod);};
	namespace base_trigger_push_component {static void register_class(luabind::module_ &mod);};
	namespace base_trigger_remove_component {static void register_class(luabind::module_ &mod);};
	namespace base_trigger_teleport_component {static void register_class(luabind::module_ &mod);};
	namespace base_vehicle_component {static void register_class(luabind::module_ &mod);};
	namespace base_weapon_component {static void register_class(luabind::module_ &mod);};
	namespace base_wheel_component {static void register_class(luabind::module_ &mod);};
	namespace base_world_component {static void register_class(luabind::module_ &mod);};
};
void pragma::lua::register_entity_component_classes(luabind::module_ &mod)
{
	auto entityComponentDef = luabind::class_<pragma::BaseEntityComponent>("EntityComponent");
	entityComponentDef.def("BroadcastEvent",static_cast<util::EventReply(pragma::BaseEntityComponent::*)(pragma::ComponentEventId) const>(&pragma::BaseEntityComponent::BroadcastEvent));
	entityComponentDef.def("BroadcastEvent",static_cast<util::EventReply(*)(lua_State*,pragma::BaseEntityComponent&,uint32_t,const luabind::tableT<void>&)>([](lua_State *l,pragma::BaseEntityComponent &hComponent,uint32_t eventId,const luabind::tableT<void> &eventArgs) {
		int32_t t = 3;
		if(pragma::get_engine()->GetNetworkState(l)->GetGameState()->BroadcastEntityEvent(hComponent,eventId,t) == false)
		{
			LuaComponentEvent luaEvent {};
			auto numArgs = Lua::GetObjectLength(l,t);
			luaEvent.arguments.reserve(numArgs);
			for(auto i=decltype(numArgs){0u};i<numArgs;++i)
			{
				Lua::PushInt(l,i +1u);
				Lua::GetTableValue(l,t);
				luaEvent.arguments.push_back(luabind::object(luabind::from_stack(l,-1)));
				Lua::Pop(l,1);
			}
			auto handled = hComponent.BroadcastEvent(eventId,luaEvent);
			//hComponent->InvokeEventCallbacks(eventId,luaEvent);
			return handled;
		}
		return util::EventReply::Handled;
	}));
	entityComponentDef.def("InvokeEventCallbacks",static_cast<util::EventReply(pragma::BaseEntityComponent::*)(pragma::ComponentEventId) const>(&pragma::BaseEntityComponent::InvokeEventCallbacks));
	entityComponentDef.def("InvokeEventCallbacks",static_cast<util::EventReply(*)(lua_State*,pragma::BaseEntityComponent&,uint32_t,const luabind::tableT<void>&)>([](lua_State *l,pragma::BaseEntityComponent &hComponent,uint32_t eventId,const luabind::tableT<void> &eventArgs) {
		int32_t t = 3;

		LuaComponentEvent luaEvent {};
		auto numArgs = Lua::GetObjectLength(l,t);
		luaEvent.arguments.reserve(numArgs);
		for(auto i=decltype(numArgs){0u};i<numArgs;++i)
		{
			Lua::PushInt(l,i +1u);
			Lua::GetTableValue(l,t);
			luaEvent.arguments.push_back(luabind::object(luabind::from_stack(l,-1)));
			Lua::Pop(l,1);
		}
		return hComponent.InvokeEventCallbacks(eventId,luaEvent);
	}));
	entityComponentDef.def("GetEntity",static_cast<BaseEntity&(pragma::BaseEntityComponent::*)()>(&pragma::BaseEntityComponent::GetEntity),luabind::game_object_policy<0>{});
	entityComponentDef.def("GetComponentId",&pragma::BaseEntityComponent::GetComponentId);
	entityComponentDef.def("SetTickPolicy",&pragma::BaseEntityComponent::SetTickPolicy);
	entityComponentDef.def("GetTickPolicy",&pragma::BaseEntityComponent::GetTickPolicy);
	entityComponentDef.def("GetNextTick",&pragma::BaseEntityComponent::GetNextTick);
	entityComponentDef.def("SetNextTick",&pragma::BaseEntityComponent::SetNextTick);
	entityComponentDef.def("IsValid",static_cast<bool(*)(lua_State*,pragma::BaseEntityComponent*)>([](lua_State *l,pragma::BaseEntityComponent *hComponent) {
		return hComponent != nullptr;
	}));
	entityComponentDef.def("RegisterNetEvent",static_cast<void(*)(lua_State*,pragma::BaseEntityComponent&,const std::string&)>([](lua_State *l,pragma::BaseEntityComponent &hComponent,const std::string &eventName) {
		hComponent.SetupNetEvent(eventName);
		auto *nw = pragma::get_engine()->GetNetworkState(l);
		auto *game = nw->GetGameState();
		auto *componentInfo = game->GetEntityComponentManager().GetComponentInfo(hComponent.GetComponentId());
		if(componentInfo && umath::is_flag_set(componentInfo->flags,pragma::ComponentFlags::Networked) == false)
			Con::cwar<<"WARNING: Component '"<<componentInfo->name<<"' has uses net-events, but was not registered as networked, this means networking will be disabled for this component! Set the 'ents.EntityComponent.FREGISTER_BIT_NETWORKED' flag when registering the component to fix this!"<<Con::endl;
	}));
	entityComponentDef.def("GetComponentName",static_cast<std::string(*)(lua_State*,pragma::BaseEntityComponent&)>([](lua_State *l,pragma::BaseEntityComponent &component) {
		auto *nw = pragma::get_engine()->GetNetworkState(l);
		auto *game = nw->GetGameState();
		auto &componentManager = game->GetEntityComponentManager();
		auto &info = *componentManager.GetComponentInfo(component.GetComponentId());
		return info.name;
	}));
	entityComponentDef.def("AddEventCallback",static_cast<CallbackHandle(*)(lua_State*,pragma::BaseEntityComponent&,uint32_t,const Lua::func<void>&)>([](lua_State *l,pragma::BaseEntityComponent &hComponent,uint32_t eventId,const Lua::func<void> &function) {
		auto hCb = hComponent.AddEventCallback(eventId,[l,function](std::reference_wrapper<pragma::ComponentEvent> ev) -> util::EventReply {
			// We need to create a copy of the lua-state pointer, since the callback can remove itself, which
			// would also cause the std::function-object to be destroyed (and therefore the captured variables).
			auto lTmp = l;
			auto oCallbackTmp = function;

			auto nstack = Lua::GetStackTop(l);
			auto c = Lua::CallFunction(l,[&oCallbackTmp,&ev](lua_State *l) -> Lua::StatusCode {
				oCallbackTmp.push(l);
				ev.get().PushArguments(l);
				return Lua::StatusCode::Ok;
			},LUA_MULTRET);
			auto numRet = Lua::GetStackTop(l) -nstack;
			if(c == Lua::StatusCode::Ok && numRet > 0 && Lua::IsNone(lTmp,-1) == false)
			{
				auto result = Lua::IsNumber(lTmp,-numRet) ? static_cast<util::EventReply>(Lua::CheckInt(lTmp,-numRet)) : util::EventReply::Unhandled;
				if(result == util::EventReply::Handled)
					ev.get().HandleReturnValues(l);
				Lua::Pop(lTmp,numRet); // Pop result(s)
				return result;
			}
			return util::EventReply::Unhandled;
		});
		return hCb;
	}));
	entityComponentDef.def("InjectEvent",static_cast<util::EventReply(pragma::BaseEntityComponent::*)(pragma::ComponentEventId)>(&pragma::BaseEntityComponent::InjectEvent));
	entityComponentDef.def("InjectEvent",static_cast<void(*)(lua_State*,pragma::BaseEntityComponent&,uint32_t,const luabind::tableT<void>&)>([](lua_State *l,pragma::BaseEntityComponent &hComponent,uint32_t eventId,const luabind::tableT<void> &eventArgs) {
		int32_t t = 3;
		if(pragma::get_engine()->GetNetworkState(l)->GetGameState()->InjectEntityEvent(hComponent,eventId,t) == false)
		{
			LuaComponentEvent luaEvent {};
			auto numArgs = Lua::GetObjectLength(l,t);
			luaEvent.arguments.reserve(numArgs);
			for(auto i=decltype(numArgs){0u};i<numArgs;++i)
			{
				Lua::PushInt(l,i +1u);
				Lua::GetTableValue(l,t);
				luaEvent.arguments.push_back(luabind::object(luabind::from_stack(l,-1)));
				Lua::Pop(l,1);
			}
			hComponent.InjectEvent(eventId,luaEvent);
		}
	}));
	entityComponentDef.def("Save",&pragma::BaseEntityComponent::Save);
	entityComponentDef.def("Load",static_cast<void(pragma::BaseEntityComponent::*)(udm::LinkedPropertyWrapperArg)>(&pragma::BaseEntityComponent::Load));
	entityComponentDef.def("Copy",static_cast<void(*)(lua_State*,pragma::BaseEntityComponent&,pragma::BaseEntityComponent&)>([](lua_State *l,pragma::BaseEntityComponent &hComponent,pragma::BaseEntityComponent &hComponentOther) {
		if(hComponent.GetComponentId() != hComponentOther.GetComponentId() || &hComponent == &hComponentOther)
			return;
		auto el = udm::Property::Create<udm::Element>();
		udm::LinkedPropertyWrapper prop {*el};
		hComponent.Save(prop);
		hComponentOther.Load(prop);
	}));
	entityComponentDef.add_static_constant("FREGISTER_NONE",umath::to_integral(pragma::ComponentFlags::None));
	entityComponentDef.add_static_constant("FREGISTER_BIT_NETWORKED",umath::to_integral(pragma::ComponentFlags::Networked));

	entityComponentDef.add_static_constant("CALLBACK_TYPE_ENTITY",umath::to_integral(pragma::BaseEntityComponent::CallbackType::Entity));
	entityComponentDef.add_static_constant("CALLBACK_TYPE_COMPONENT",umath::to_integral(pragma::BaseEntityComponent::CallbackType::Component));
	mod[entityComponentDef];

	base_ai_component::register_class(mod);
	base_animated_component::register_class(mod);
	base_attachable_component::register_class(mod);
	base_bot_component::register_class(mod);
	base_character_component::register_class(mod);
	base_color_component::register_class(mod);
	base_debug_box_component::register_class(mod);
	base_debug_cone_component::register_class(mod);
	base_debug_cylinder_component::register_class(mod);
	base_debug_line_component::register_class(mod);
	base_debug_plane_component::register_class(mod);
	base_debug_point_component::register_class(mod);
	base_debug_sphere_component::register_class(mod);
	base_debug_text_component::register_class(mod);
	base_decal_component::register_class(mod);
	base_env_camera_component::register_class(mod);
	base_env_explosion_component::register_class(mod);
	base_env_filter_class_component::register_class(mod);
	base_env_filter_name_component::register_class(mod);
	base_env_fire_component::register_class(mod);
	base_env_fog_controller_component::register_class(mod);
	base_env_light_component::register_class(mod);
	base_env_light_directional_component::register_class(mod);
	base_env_light_point_component::register_class(mod);
	base_env_light_spot_component::register_class(mod);
	base_env_light_spot_vol_component::register_class(mod);
	base_env_microphone_component::register_class(mod);
	base_env_particle_system_component::register_class(mod);
	base_env_quake_component::register_class(mod);
	base_env_smoke_trail_component::register_class(mod);
	base_env_soundscape_component::register_class(mod);
	base_env_sound_component::register_class(mod);
	base_env_sound_dsp_component::register_class(mod);
	base_env_sprite_component::register_class(mod);
	base_env_timescale_component::register_class(mod);
	base_env_weather_component::register_class(mod);
	base_env_wind_component::register_class(mod);
	base_flammable_component::register_class(mod);
	base_flashlight_component::register_class(mod);
	base_flex_component::register_class(mod);
	base_func_brush_component::register_class(mod);
	base_func_button_component::register_class(mod);
	base_func_kinematic_component::register_class(mod);
	base_func_physics_component::register_class(mod);
	base_func_portal_component::register_class(mod);
	base_func_soft_physics_component::register_class(mod);
	base_func_surface_material_component::register_class(mod);
	base_func_water_component::register_class(mod);
	base_gamemode_component::register_class(mod);
	base_generic_component::register_class(mod);
	base_health_component::register_class(mod);
	base_info_landmark_component::register_class(mod);
	base_io_component::register_class(mod);
	base_logic_relay_component::register_class(mod);
	base_model_component::register_class(mod);
	base_name_component::register_class(mod);
	base_networked_component::register_class(mod);
	base_observable_component::register_class(mod);
	base_ownable_component::register_class(mod);
	base_parent_component::register_class(mod);
	base_physics_component::register_class(mod);
	base_player_component::register_class(mod);
	base_point_at_target_component::register_class(mod);
	base_point_constraint_ball_socket_component::register_class(mod);
	base_point_constraint_cone_twist_component::register_class(mod);
	base_point_constraint_dof_component::register_class(mod);
	base_point_constraint_fixed_component::register_class(mod);
	base_point_constraint_hinge_component::register_class(mod);
	base_point_constraint_slider_component::register_class(mod);
	base_point_path_node_component::register_class(mod);
	base_point_render_target_component::register_class(mod);
	base_point_target_component::register_class(mod);
	base_prop_component::register_class(mod);
	base_prop_dynamic_component::register_class(mod);
	base_prop_physics_component::register_class(mod);
	base_radius_component::register_class(mod);
	base_render_component::register_class(mod);
	base_score_component::register_class(mod);
	base_shooter_component::register_class(mod);
	base_skybox_component::register_class(mod);
	base_soft_body_component::register_class(mod);
	base_sound_emitter_component::register_class(mod);
	base_time_scale_component::register_class(mod);
	base_toggle_component::register_class(mod);
	base_touch_component::register_class(mod);
	base_transform_component::register_class(mod);
	base_trigger_gravity_component::register_class(mod);
	base_trigger_hurt_component::register_class(mod);
	base_trigger_push_component::register_class(mod);
	base_trigger_remove_component::register_class(mod);
	base_trigger_teleport_component::register_class(mod);
	base_vehicle_component::register_class(mod);
	base_weapon_component::register_class(mod);
	base_wheel_component::register_class(mod);
	base_world_component::register_class(mod);
}
void pragma::lua::base_attachable_component::register_class(luabind::module_ &mod)
{
	Lua::ComponentClass<pragma::BaseAttachableComponent> def {"BaseAttachableComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	def.def("AttachToEntity",&pragma::BaseAttachableComponent::AttachToEntity);
	//def.def("AttachToEntity",&pragma::BaseAttachableComponent::AttachToEntity,luabind::default_parameter_policy<0,AttachmentInfo,att>{});
	//def.def("AttachToEntity",std::bind(&pragma::BaseAttachableComponent::AttachToEntity,std::placeholders::_1,AttachmentInfo{}));
	def.def("ClearAttachment",&pragma::BaseAttachableComponent::ClearAttachment);
	def.def("AttachToAttachment",static_cast<AttachmentData*(pragma::BaseAttachableComponent::*)(BaseEntity*,uint32_t,const AttachmentInfo&)>(&pragma::BaseAttachableComponent::AttachToAttachment));
	//def.def("AttachToAttachment",std::bind(static_cast<AttachmentData*(pragma::BaseAttachableComponent::*)(BaseEntity*,uint32_t,const AttachmentInfo&)>(&pragma::BaseAttachableComponent::AttachToAttachment),std::placeholders::_1,std::placeholders::_2,AttachmentInfo{}));
	def.def("AttachToAttachment",static_cast<AttachmentData*(pragma::BaseAttachableComponent::*)(BaseEntity*,std::string,const AttachmentInfo&)>(&pragma::BaseAttachableComponent::AttachToAttachment));
	//def.def("AttachToAttachment",std::bind(static_cast<AttachmentData*(pragma::BaseAttachableComponent::*)(BaseEntity*,std::string,const AttachmentInfo&)>(&pragma::BaseAttachableComponent::AttachToAttachment),std::placeholders::_1,std::placeholders::_2,AttachmentInfo{}));
	def.def("AttachToBone",static_cast<void(*)(lua_State*,pragma::BaseAttachableComponent&,BaseEntity&,std::string,AttachmentInfo&)>([](lua_State *l,pragma::BaseAttachableComponent &hEnt,BaseEntity &parent,std::string bone,AttachmentInfo &attInfo) {
		
		hEnt.AttachToBone(&parent,bone,attInfo);
	}));
	def.def("AttachToBone",static_cast<void(*)(lua_State*,pragma::BaseAttachableComponent&,BaseEntity&,std::string)>([](lua_State *l,pragma::BaseAttachableComponent &hEnt,BaseEntity &parent,std::string bone) {
		
		hEnt.AttachToBone(&parent,bone);
	}));
	def.def("AttachToBone",static_cast<void(*)(lua_State*,pragma::BaseAttachableComponent&,BaseEntity&,int,AttachmentInfo&)>([](lua_State *l,pragma::BaseAttachableComponent &hEnt,BaseEntity &parent,int bone,AttachmentInfo &attInfo) {
		
		hEnt.AttachToBone(&parent,bone,attInfo);
	}));
	def.def("AttachToBone",static_cast<void(*)(lua_State*,pragma::BaseAttachableComponent&,BaseEntity&,int)>([](lua_State *l,pragma::BaseAttachableComponent &hEnt,BaseEntity &parent,int bone) {
		
		hEnt.AttachToBone(&parent,bone);
	}));
	def.def("GetLocalPose",&pragma::BaseAttachableComponent::GetLocalPose,luabind::optional_policy<0>{});
	def.def("SetLocalPose",&pragma::BaseAttachableComponent::SetLocalPose,luabind::optional_policy<0>{});
	def.def("GetParent",&pragma::BaseAttachableComponent::GetParent,luabind::game_object_policy<0>{});

	def.def("GetBone",static_cast<luabind::object(*)(lua_State*,pragma::BaseAttachableComponent&)>([](lua_State *l,pragma::BaseAttachableComponent &hEnt) -> luabind::object {
		
		auto *data = hEnt.GetAttachmentData();
		if(data == nullptr)
			return luabind::object{};
		return luabind::object{l,data->bone};
	}));
	def.def("SetAttachmentFlags",&pragma::BaseAttachableComponent::SetAttachmentFlags);
	def.def("GetAttachmentFlags",&pragma::BaseAttachableComponent::GetAttachmentFlags);

	auto defAttInfo = luabind::class_<AttachmentInfo>("AttachmentInfo");
	defAttInfo.def(luabind::constructor<>());
	defAttInfo.def("SetOffset",static_cast<void(*)(lua_State*,AttachmentInfo&,const Vector3&)>([](lua_State *l,AttachmentInfo &attInfo,const Vector3 &offset) {
		attInfo.offset = offset;
	}));
	defAttInfo.def("SetOffset",static_cast<void(*)(lua_State*,AttachmentInfo&)>([](lua_State *l,AttachmentInfo &attInfo) {
		attInfo.offset.reset();
	}));
	defAttInfo.def("SetRotation",static_cast<void(*)(lua_State*,AttachmentInfo&,const Quat&)>([](lua_State *l,AttachmentInfo &attInfo,const Quat &rotation) {
		attInfo.rotation = rotation;
	}));
	defAttInfo.def("SetRotation",static_cast<void(*)(lua_State*,AttachmentInfo&)>([](lua_State *l,AttachmentInfo &attInfo) {
		attInfo.rotation.reset();
	}));
	defAttInfo.def_readwrite("flags",reinterpret_cast<std::underlying_type_t<decltype(AttachmentInfo::flags)> AttachmentInfo::*>(&AttachmentInfo::flags));
	def.scope[defAttInfo];

	def.add_static_constant("EVENT_ON_ATTACHMENT_UPDATE",pragma::BaseAttachableComponent::EVENT_ON_ATTACHMENT_UPDATE);

	def.add_static_constant("FATTACHMENT_MODE_POSITION_ONLY",umath::to_integral(FAttachmentMode::PositionOnly));
	def.add_static_constant("FATTACHMENT_MODE_BONEMERGE",umath::to_integral(FAttachmentMode::BoneMerge));
	def.add_static_constant("FATTACHMENT_MODE_UPDATE_EACH_FRAME",umath::to_integral(FAttachmentMode::UpdateEachFrame));
	def.add_static_constant("FATTACHMENT_MODE_PLAYER_VIEW",umath::to_integral(FAttachmentMode::PlayerView));
	def.add_static_constant("FATTACHMENT_MODE_PLAYER_VIEW_YAW",umath::to_integral(FAttachmentMode::PlayerViewYaw));
	def.add_static_constant("FATTACHMENT_MODE_SNAP_TO_ORIGIN",umath::to_integral(FAttachmentMode::SnapToOrigin));
	def.add_static_constant("FATTACHMENT_MODE_FORCE_TRANSLATION_IN_PLACE",umath::to_integral(FAttachmentMode::ForceTranslationInPlace));
	def.add_static_constant("FATTACHMENT_MODE_FORCE_ROTATION_IN_PLACE",umath::to_integral(FAttachmentMode::ForceRotationInPlace));
	def.add_static_constant("FATTACHMENT_MODE_FORCE_IN_PLACE",umath::to_integral(FAttachmentMode::ForceInPlace));
}

#include "pragma/entities/components/base_animated_component.hpp"
#include "pragma/model/animation/animation.hpp"
#include "pragma/lua/classes/lproperty.hpp"
#include "pragma/model/model.h"
	namespace pragma
	{
		class BaseFuncWaterComponent;
	};


namespace Lua
{
	DLLNETWORK bool get_bullet_master(BaseEntity &ent);
	DLLNETWORK AnimationEvent get_animation_event(lua_State *l,int32_t tArgs,uint32_t eventId);
	namespace Animated
	{
		static BoneId get_bone_id(lua_State *l,pragma::BaseAnimatedComponent &hAnim,uint32_t boneId)
		{
			
			return boneId;
		}
		static BoneId get_bone_id(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const std::string &boneId)
		{
			
			auto &ent = hAnim.GetEntity();
			auto &mdl = ent.GetModel();
			if(!mdl)
				return std::numeric_limits<BoneId>::max();
			return mdl->LookupBone(boneId);
		}
		template<typename TBoneId>
			static void GetBoneMatrix(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier)
		{
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto mat = hAnim.GetBoneMatrix(boneId);
			if(mat.has_value() == false)
				return;
			luabind::object(l,*mat).push(l);
		}
		template<typename TBoneId>
			static void GetBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			Vector3 pos = {};
			auto rot = uquat::identity();
			Vector3 scale = {1.f,1.f,1.f};
			auto r = hAnim.GetBonePosition(boneId,pos,rot,scale);
			if(r == false)
				return;
			Lua::Push<Vector3>(l,pos);
			Lua::Push<Quat>(l,rot);
			Lua::Push<Vector3>(l,scale);
		}
		template<typename TBoneId>
			static void GetBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			Vector3 pos = {};
			auto rot = uquat::identity();
			Vector3 scale = {1.f,1.f,1.f};
			auto r = hAnim.GetBonePosition(boneId,pos,rot,scale);
			if(r == false)
				return;
			Lua::Push<umath::ScaledTransform>(l,umath::ScaledTransform{pos,rot,scale});
		}
		template<typename TBoneId>
			static void GetBoneBindPose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto &ent = hAnim.GetEntity();
			auto mdl = ent.GetModel();
			if(mdl == nullptr)
				return;
			auto &ref = mdl->GetReference();
			umath::ScaledTransform transform;
			if(ref.GetBonePose(boneId,transform) == false)
				return;
			Lua::Push<umath::ScaledTransform>(l,transform);
		}
		template<typename TBoneId>
			static void GetBonePos(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto *pos = hAnim.GetBonePosition(boneId);
			if(pos == nullptr)
				return;
			Lua::Push<Vector3>(l,*pos);
		}
		template<typename TBoneId>
			static void GetBoneRot(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto *rot = hAnim.GetBoneRotation(boneId);
			if(rot == nullptr)
				return;
			Lua::Push<Quat>(l,*rot);
		}
		template<typename TBoneId>
			static void GetLocalBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			Vector3 pos = {};
			auto rot = uquat::identity();
			Vector3 scale(1.f,1.f,1.f);
			auto r = hAnim.GetLocalBonePosition(boneId,pos,rot,&scale);
			if(r == false)
				return;
			Lua::Push<Vector3>(l,pos);
			Lua::Push<Quat>(l,rot);
			Lua::Push<Vector3>(l,scale);
		}
		template<typename TBoneId>
			static void GetLocalBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			Vector3 pos = {};
			auto rot = uquat::identity();
			Vector3 scale(1.f,1.f,1.f);
			auto r = hAnim.GetLocalBonePosition(boneId,pos,rot,&scale);
			if(r == false)
				return;
			Lua::Push<umath::ScaledTransform>(l,{pos,rot,scale});
		}
		template<typename TBoneId>
			static void GetGlobalBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			Vector3 pos = {};
			auto rot = uquat::identity();
			Vector3 scale(1.f,1.f,1.f);
			auto r = hAnim.GetGlobalBonePosition(boneId,pos,rot,&scale);
			if(r == false)
				return;
			Lua::Push<Vector3>(l,pos);
			Lua::Push<Quat>(l,rot);
			Lua::Push<Vector3>(l,scale);
		}
		template<typename TBoneId>
			static void GetGlobalBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			Vector3 pos = {};
			auto rot = uquat::identity();
			Vector3 scale(1.f,1.f,1.f);
			auto r = hAnim.GetGlobalBonePosition(boneId,pos,rot,&scale);
			if(r == false)
				return;
			Lua::Push<umath::ScaledTransform>(l,{pos,rot,scale});
		}
		template<typename TBoneId>
			static void GetBoneRotation(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto *rot = hAnim.GetBoneRotation(boneId);
			if(rot == nullptr)
				return;
			Lua::Push<Quat>(l,*rot);
		}
		template<typename TBoneId>
			static void GetBoneAngles(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			EulerAngles ang;
			auto r = hAnim.GetBoneAngles(boneId,ang);
			if(r == false)
				return;
			Lua::Push<EulerAngles>(l,ang);
		}
		template<typename TBoneId>
			static void SetBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos,const Quat &rot,const Vector3 &scale) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pos,rot,scale);
		}
		template<typename TBoneId>
			static void SetBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos,const Quat &rot) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pos,rot);
		}
		template<typename TBoneId>
			static void SetBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos,const EulerAngles &ang,const Vector3 &scale) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pos,uquat::create(ang),scale);
		}
		template<typename TBoneId>
			static void SetBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos,const EulerAngles &ang) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pos,ang);
		}
		template<typename TBoneId>
			static void SetBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const umath::ScaledTransform &pose) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pose.GetOrigin(),pose.GetRotation(),pose.GetScale());
		}
		template<typename TBoneId>
			static void SetBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const umath::Transform &pose) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pose.GetOrigin(),pose.GetRotation());
		}

		template<typename TBoneId>
			static void SetBonePos(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBonePosition(boneId,pos);
		}
		template<typename TBoneId>
			static void SetBoneRot(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Quat &rot) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBoneRotation(boneId,rot);
		}
		template<typename TBoneId>
			static void SetBoneAngles(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const EulerAngles &ang) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBoneRotation(boneId,uquat::create(ang));
		}
		template<typename TBoneId>
			static void SetBoneScale(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &scale) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetBoneScale(boneId,scale);
		}
		template<typename TBoneId>
			static void GetBoneScale(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto *scale = hAnim.GetBoneScale(boneId);
			if(scale == nullptr)
				return;
			Lua::Push<Vector3>(l,*scale);
		}

		template<typename TBoneId>
			static void SetLocalBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos,const Quat &rot,const Vector3 &scale) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetLocalBonePosition(boneId,pos,rot,scale);
		}
		template<typename TBoneId>
			static void SetLocalBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const umath::ScaledTransform &pose) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetLocalBonePosition(boneId,pose.GetOrigin(),pose.GetRotation(),pose.GetScale());
		}
		template<typename TBoneId>
			static void SetLocalBonePos(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetLocalBonePosition(boneId,pos);
		}
		template<typename TBoneId>
			static void SetLocalBoneRot(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Quat &rot) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetLocalBoneRotation(boneId,rot);
		}

		template<typename TBoneId>
			static void SetGlobalBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos,const Quat &rot,const Vector3 &scale) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetGlobalBonePosition(boneId,pos,rot,scale);
		}
		template<typename TBoneId>
			static void SetGlobalBonePose(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const umath::ScaledTransform &pose) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetGlobalBonePosition(boneId,pose.GetOrigin(),pose.GetRotation(),pose.GetScale());
		}
		template<typename TBoneId>
			static void SetGlobalBonePos(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Vector3 &pos) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetGlobalBonePosition(boneId,pos);
		}
		template<typename TBoneId>
			static void SetGlobalBoneRot(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const Quat &rot) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			hAnim.SetGlobalBoneRotation(boneId,rot);
		}
		template<typename TBoneId>
			static void GetEffectiveBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto &transforms = hAnim.GetProcessedBones();
			if(boneId >= transforms.size())
				return;
			Lua::Push<umath::ScaledTransform*>(l,&transforms.at(boneId));
		}
		template<typename TBoneId>
			static void SetEffectiveBoneTransform(lua_State *l,pragma::BaseAnimatedComponent &hAnim,const TBoneId &boneIdentifier,const umath::ScaledTransform &t) {
			auto boneId = get_bone_id(l,hAnim,boneIdentifier);
			auto &transforms = hAnim.GetProcessedBones();
			if(boneId >= transforms.size())
				return;
			transforms.at(boneId) = t;
		}
	};
};
#include "pragma/model/modelmesh.h"
template<typename TBoneId>
	static void register_base_animated_component_bone_methods(Lua::ComponentClass<pragma::BaseAnimatedComponent> &def)
{
	def.def("GetBoneMatrix",&Lua::Animated::GetBoneMatrix<TBoneId>);
	def.def("GetBoneTransform",&Lua::Animated::GetBoneTransform<TBoneId>);
	def.def("GetBonePose",&Lua::Animated::GetBonePose<TBoneId>);
	def.def("GetBoneBindPose",&Lua::Animated::GetBoneBindPose<TBoneId>);
	def.def("GetBonePos",&Lua::Animated::GetBonePos<TBoneId>);
	def.def("GetBoneRot",&Lua::Animated::GetBoneRot<TBoneId>);
	def.def("GetLocalBoneTransform",&Lua::Animated::GetLocalBoneTransform<TBoneId>);
	def.def("GetLocalBonePose",&Lua::Animated::GetLocalBonePose<TBoneId>);
	def.def("GetGlobalBoneTransform",&Lua::Animated::GetGlobalBoneTransform<TBoneId>);
	def.def("GetGlobalBonePose",&Lua::Animated::GetGlobalBonePose<TBoneId>);
	def.def("GetBoneRotation",&Lua::Animated::GetBoneRotation<TBoneId>);
	def.def("GetBoneAngles",&Lua::Animated::GetBoneAngles<TBoneId>);
	def.def("SetBoneTransform",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const TBoneId&,const Vector3&,const Quat&,const Vector3&)>(&Lua::Animated::SetBoneTransform<TBoneId>));
	def.def("SetBoneTransform",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const TBoneId&,const Vector3&,const Quat&)>(&Lua::Animated::SetBoneTransform<TBoneId>));
	def.def("SetBoneTransform",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const TBoneId&,const Vector3&,const EulerAngles&,const Vector3&)>(&Lua::Animated::SetBoneTransform<TBoneId>));
	def.def("SetBoneTransform",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const TBoneId&,const Vector3&,const EulerAngles&)>(&Lua::Animated::SetBoneTransform<TBoneId>));

	def.def("SetBonePose",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const TBoneId&,const umath::ScaledTransform&)>(&Lua::Animated::SetBonePose<TBoneId>));
	def.def("SetBonePose",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const TBoneId&,const umath::Transform&)>(&Lua::Animated::SetBonePose<TBoneId>));

	def.def("SetBonePos",&Lua::Animated::SetBonePos<TBoneId>);
	def.def("SetBoneRot",&Lua::Animated::SetBoneRot<TBoneId>);
	def.def("SetBoneAngles",&Lua::Animated::SetBoneAngles<TBoneId>);
	def.def("SetBoneScale",&Lua::Animated::SetBoneScale<TBoneId>);
	def.def("GetBoneScale",&Lua::Animated::GetBoneScale<TBoneId>);

	def.def("SetLocalBoneTransform",&Lua::Animated::SetLocalBoneTransform<TBoneId>);
	def.def("SetLocalBonePose",&Lua::Animated::SetLocalBonePose<TBoneId>);
	def.def("SetLocalBonePos",&Lua::Animated::SetLocalBonePos<TBoneId>);
	def.def("SetLocalBoneRot",&Lua::Animated::SetLocalBoneRot<TBoneId>);

	def.def("SetGlobalBoneTransform",&Lua::Animated::SetGlobalBoneTransform<TBoneId>);
	def.def("SetGlobalBonePose",&Lua::Animated::SetGlobalBonePose<TBoneId>);
	def.def("SetGlobalBonePos",&Lua::Animated::SetGlobalBonePos<TBoneId>);
	def.def("SetGlobalBoneRot",&Lua::Animated::SetGlobalBoneRot<TBoneId>);
		
	def.def("GetEffectiveBoneTransform",&Lua::Animated::GetEffectiveBoneTransform<TBoneId>);
	def.def("SetEffectiveBoneTransform",&Lua::Animated::SetEffectiveBoneTransform<TBoneId>);
}
void pragma::lua::base_animated_component::register_class(luabind::module_ &mod)
{
		Lua::ComponentClass<pragma::BaseAnimatedComponent> def {"BaseAnimatedComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	def.def("PlayAnimation",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int anim,uint32_t flags) {
		
		hAnim.PlayAnimation(anim,static_cast<pragma::FPlayAnim>(flags));
	}));
	def.def("PlayAnimation",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,std::string,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,std::string anim,uint32_t flags) {
		
		Lua::PushBool(l,hAnim.PlayAnimation(anim,static_cast<pragma::FPlayAnim>(flags)));
	}));
	def.def("PlayAnimation",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int anim) {
		
		hAnim.PlayAnimation(anim,pragma::FPlayAnim::Default);
	}));
	def.def("PlayAnimation",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,std::string)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,std::string anim) {
		
		Lua::PushBool(l,hAnim.PlayAnimation(anim,pragma::FPlayAnim::Default));
	}));
	def.def("GetAnimation",&pragma::BaseAnimatedComponent::GetAnimation);
	def.def("GetAnimationObject",&pragma::BaseAnimatedComponent::GetAnimationObject,luabind::shared_from_this_policy<0>{});
	def.def("PlayActivity",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int activity,uint32_t flags) {
		
		hAnim.PlayActivity(static_cast<Activity>(activity),static_cast<pragma::FPlayAnim>(flags));
	}));
	def.def("PlayActivity",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int activity) {
		
		hAnim.PlayActivity(static_cast<Activity>(activity),pragma::FPlayAnim::Default);
	}));
	def.def("GetActivity",&pragma::BaseAnimatedComponent::GetActivity);
	def.def("PlayLayeredAnimation",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int,int)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int slot,int anim) {
		
		hAnim.PlayLayeredAnimation(slot,anim);
	}));
	def.def("PlayLayeredAnimation",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int,std::string)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int slot,std::string anim) {
		
		hAnim.PlayLayeredAnimation(slot,anim);
	}));
	def.def("PlayLayeredActivity",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,int,int)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim,int slot,int activity) {
		
		hAnim.PlayLayeredActivity(slot,static_cast<Activity>(activity));
	}));
	def.def("StopLayeredAnimation",&pragma::BaseAnimatedComponent::StopLayeredAnimation);
	def.def("GetLayeredAnimation",&pragma::BaseAnimatedComponent::GetLayeredAnimation);
	def.def("GetLayeredActivity",&pragma::BaseAnimatedComponent::GetLayeredActivity);
	def.def("GetLayeredAnimations",static_cast<luabind::object(*)(lua_State*,pragma::BaseAnimatedComponent&)>([](lua_State *l,pragma::BaseAnimatedComponent &hAnim) -> luabind::object {
		
		auto t = luabind::newtable(l);
		for(auto &pair : hAnim.GetAnimationSlotInfos())
			t[pair.first] = pair.second.animation;
		return t;
	}));
	def.def("ApplyLayeredAnimations",&pragma::BaseAnimatedComponent::MaintainGestures);
	def.def("SetPlaybackRate",&pragma::BaseAnimatedComponent::SetPlaybackRate);
	def.def("GetPlaybackRate",&pragma::BaseAnimatedComponent::GetPlaybackRate);
	def.def("GetPlaybackRateProperty",&pragma::BaseAnimatedComponent::GetPlaybackRateProperty,luabind::property_policy<0>{});
	register_base_animated_component_bone_methods<BoneId>(def);
	register_base_animated_component_bone_methods<std::string>(def);
	def.def("UpdateEffectiveBoneTransforms",&pragma::BaseAnimatedComponent::UpdateSkeleton);
	def.def("GetBindPose",&pragma::BaseAnimatedComponent::GetBindPose,luabind::shared_from_this_policy<0>{});
	def.def("SetBindPose",&pragma::BaseAnimatedComponent::SetBindPose);
	def.def("SetCycle",&pragma::BaseAnimatedComponent::SetCycle);
	def.def("GetCycle",&pragma::BaseAnimatedComponent::GetCycle);
	def.def("AddAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,uint32_t,uint32_t,const luabind::object&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t animId,uint32_t frameId,uint32_t eventId,const luabind::object &args) {
		auto ev = Lua::get_animation_event(l,5,eventId);
		hEnt.AddAnimationEvent(animId,frameId,ev);
	}));
	def.def("AddAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,uint32_t,const luabind::object&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t animId,uint32_t frameId,const luabind::object &f) {
		
		if(Lua::IsFunction(l,4))
		{
			auto hCb = hEnt.AddAnimationEvent(animId,frameId,CallbackHandle{std::shared_ptr<TCallback>(new LuaCallback(f))});
			Lua::Push<CallbackHandle>(l,hCb);
		}
		else
		{
			AnimationEvent ev {};
			ev.eventID = static_cast<AnimationEvent::Type>(Lua::CheckInt(l,4));
			hEnt.AddAnimationEvent(animId,frameId,ev);
		}
	}));
	def.def("AddAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const std::string&,uint32_t,uint32_t,const luabind::object&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,const std::string &anim,uint32_t frameId,uint32_t eventId,const luabind::object &args) {
		
		auto ev = Lua::get_animation_event(l,5,eventId);
		hEnt.AddAnimationEvent(anim,frameId,ev);
	}));
	def.def("AddAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const std::string&,uint32_t,const luabind::object&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,const std::string &anim,uint32_t frameId,const luabind::object &f) {
		
		if(Lua::IsFunction(l,4))
		{
			auto hCb = hEnt.AddAnimationEvent(anim,frameId,CallbackHandle{std::shared_ptr<TCallback>(new LuaCallback(f))});
			Lua::Push<CallbackHandle>(l,hCb);
		}
		else
		{
			AnimationEvent ev {};
			ev.eventID = static_cast<AnimationEvent::Type>(Lua::CheckInt(l,4));
			hEnt.AddAnimationEvent(anim,frameId,ev);
		}
	}));
	def.def("ClearAnimationEvents",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt) {
		
		hEnt.ClearAnimationEvents();
	}));
	def.def("ClearAnimationEvents",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t animId) {
		
		hEnt.ClearAnimationEvents(animId);
	}));
	def.def("ClearAnimationEvents",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t animId,uint32_t frameId) {
		
		hEnt.ClearAnimationEvents(animId,frameId);
	}));
	def.def("ClearAnimationEvents",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const std::string&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,const std::string &anim) {
		
		hEnt.ClearAnimationEvents(anim);
	}));
	def.def("ClearAnimationEvents",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,const std::string&,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,const std::string &anim,uint32_t frameId) {
		
		hEnt.ClearAnimationEvents(anim,frameId);
	}));

	def.def("InjectAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t eventId) {
		
		AnimationEvent ev {};
		ev.eventID = static_cast<AnimationEvent::Type>(eventId);
		hEnt.InjectAnimationEvent(ev);
	}));
	def.def("InjectAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,const luabind::object&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t eventId,const luabind::object &args) {
		
		auto ev = Lua::get_animation_event(l,3,eventId);
		hEnt.InjectAnimationEvent(ev);
	}));
	def.def("BindAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,luabind::object)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t eventId,luabind::object function) {
		
		Lua::CheckFunction(l,3);
		hEnt.BindAnimationEvent(static_cast<AnimationEvent::Type>(eventId),[l,function](std::reference_wrapper<const AnimationEvent> ev) {
			Lua::CallFunction(l,[&function,&ev](lua_State *l) -> Lua::StatusCode {
				function.push(l);
				pragma::CEHandleAnimationEvent evData{ev};
				evData.PushArgumentVariadic(l);
				return Lua::StatusCode::Ok;
			});
		});
	}));
	def.def("BindAnimationEvent",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,pragma::BaseEntityComponent&,const std::string&)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t eventId,pragma::BaseEntityComponent &component,const std::string &methodName) {
		
		auto hComponent = component.GetHandle();
		hEnt.BindAnimationEvent(static_cast<AnimationEvent::Type>(eventId),[hComponent,methodName](std::reference_wrapper<const AnimationEvent> ev) {
			if(hComponent.expired())
				return;
			auto o = hComponent->GetLuaObject();
			auto r = o[methodName];
			if(r)
			{
				auto *l = o.interpreter();
				auto c = Lua::CallFunction(l,[o,&methodName,&ev](lua_State *l) -> Lua::StatusCode {
					o.push(l);
					Lua::PushString(l,methodName);
					Lua::GetTableValue(l,-2);
					Lua::RemoveValue(l,-2);

					o.push(l);
					pragma::CEHandleAnimationEvent evData{ev};
					evData.PushArgumentVariadic(l);
					return Lua::StatusCode::Ok;
				},0);
			}
		});
	}));

	def.def("GetVertexPosition",static_cast<std::optional<Vector3>(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t,uint32_t,uint32_t,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t meshGroupId,uint32_t meshId,uint32_t subMeshId,uint32_t vertexId) -> std::optional<Vector3> {
		auto pos = Vector3{};
		if(hEnt.GetVertexPosition(meshGroupId,meshId,subMeshId,vertexId,pos) == false)
			return {};
		return pos;
	}),luabind::optional_policy<0,Vector3>{});
	def.def("GetVertexPosition",static_cast<std::optional<Vector3>(*)(lua_State*,pragma::BaseAnimatedComponent&,const std::shared_ptr<ModelSubMesh>&,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,const std::shared_ptr<ModelSubMesh> &subMesh,uint32_t vertexId) -> std::optional<Vector3> {
		auto pos = Vector3{};
		if(hEnt.GetVertexPosition(*subMesh,vertexId,pos) == false)
			return {};
		return pos;
	}),luabind::optional_policy<0,Vector3>{});
	def.def("SetBlendController",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,unsigned int,float)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,unsigned int controller,float val) {
		
		hEnt.SetBlendController(controller,val);
	}));
	def.def("SetBlendController",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,std::string,float)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,std::string controller,float val) {
		
		hEnt.SetBlendController(controller,val);
	}));
	def.def("GetBlendController",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,std::string)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,std::string controller) {
		
		Lua::PushNumber(l,hEnt.GetBlendController(controller));
	}));
	def.def("GetBlendController",static_cast<void(*)(lua_State*,pragma::BaseAnimatedComponent&,unsigned int)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,unsigned int controller) {
		
		Lua::PushNumber(l,hEnt.GetBlendController(controller));
	}));
	def.def("GetBoneCount",&pragma::BaseAnimatedComponent::GetBoneCount);
	def.def("SetRootPoseBoneId",&pragma::BaseAnimatedComponent::SetRootPoseBoneId);
	def.def("GetRootPoseBoneId",&pragma::BaseAnimatedComponent::GetRootPoseBoneId);
	def.def("SetAnimatedRootPoseTransformEnabled",&pragma::BaseAnimatedComponent::SetAnimatedRootPoseTransformEnabled);
	def.def("IsAnimatedRootPoseTransformEnabled",&pragma::BaseAnimatedComponent::IsAnimatedRootPoseTransformEnabled);
	def.def("AddRootPoseBone",&pragma::BaseAnimatedComponent::AddRootPoseBone);
	def.def("GetBaseAnimationFlags",&pragma::BaseAnimatedComponent::GetBaseAnimationFlags);
	def.def("SetBaseAnimationFlags",&pragma::BaseAnimatedComponent::SetBaseAnimationFlags);
	def.def("GetLayeredAnimationFlags",static_cast<luabind::object(*)(lua_State*,pragma::BaseAnimatedComponent&,uint32_t)>([](lua_State *l,pragma::BaseAnimatedComponent &hEnt,uint32_t layerIdx) -> luabind::object {
		auto flags = hEnt.GetLayeredAnimationFlags(layerIdx);
		if(flags.has_value() == false)
			return {};
		return luabind::object{l,*flags};
	}));
	def.def("SetLayeredAnimationFlags",&pragma::BaseAnimatedComponent::SetLayeredAnimationFlags);

	def.add_static_constant("EVENT_HANDLE_ANIMATION_EVENT",pragma::BaseAnimatedComponent::EVENT_HANDLE_ANIMATION_EVENT);
	def.add_static_constant("EVENT_ON_PLAY_ANIMATION",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_ANIMATION);
	def.add_static_constant("EVENT_ON_PLAY_LAYERED_ANIMATION",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_LAYERED_ANIMATION);
	def.add_static_constant("EVENT_ON_PLAY_LAYERED_ACTIVITY",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_LAYERED_ACTIVITY);
	def.add_static_constant("EVENT_ON_ANIMATION_COMPLETE",pragma::BaseAnimatedComponent::EVENT_ON_ANIMATION_COMPLETE);
	def.add_static_constant("EVENT_ON_LAYERED_ANIMATION_START",pragma::BaseAnimatedComponent::EVENT_ON_LAYERED_ANIMATION_START);
	def.add_static_constant("EVENT_ON_LAYERED_ANIMATION_COMPLETE",pragma::BaseAnimatedComponent::EVENT_ON_LAYERED_ANIMATION_COMPLETE);
	def.add_static_constant("EVENT_ON_ANIMATION_START",pragma::BaseAnimatedComponent::EVENT_ON_ANIMATION_START);
	def.add_static_constant("EVENT_TRANSLATE_LAYERED_ANIMATION",pragma::BaseAnimatedComponent::EVENT_TRANSLATE_LAYERED_ANIMATION);
	def.add_static_constant("EVENT_TRANSLATE_ANIMATION",pragma::BaseAnimatedComponent::EVENT_TRANSLATE_ANIMATION);
	def.add_static_constant("EVENT_TRANSLATE_ACTIVITY",pragma::BaseAnimatedComponent::EVENT_TRANSLATE_ACTIVITY);

	def.add_static_constant("EVENT_HANDLE_ANIMATION_EVENT",pragma::BaseAnimatedComponent::EVENT_HANDLE_ANIMATION_EVENT);
	def.add_static_constant("EVENT_ON_PLAY_ANIMATION",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_ANIMATION);
	def.add_static_constant("EVENT_ON_PLAY_LAYERED_ANIMATION",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_LAYERED_ANIMATION);
	def.add_static_constant("EVENT_ON_PLAY_LAYERED_ACTIVITY",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_LAYERED_ACTIVITY);
	def.add_static_constant("EVENT_ON_ANIMATION_COMPLETE",pragma::BaseAnimatedComponent::EVENT_ON_ANIMATION_COMPLETE);
	def.add_static_constant("EVENT_ON_LAYERED_ANIMATION_START",pragma::BaseAnimatedComponent::EVENT_ON_LAYERED_ANIMATION_START);
	def.add_static_constant("EVENT_ON_LAYERED_ANIMATION_COMPLETE",pragma::BaseAnimatedComponent::EVENT_ON_LAYERED_ANIMATION_COMPLETE);
	def.add_static_constant("EVENT_ON_ANIMATION_START",pragma::BaseAnimatedComponent::EVENT_ON_ANIMATION_START);
	def.add_static_constant("EVENT_TRANSLATE_LAYERED_ANIMATION",pragma::BaseAnimatedComponent::EVENT_TRANSLATE_LAYERED_ANIMATION);
	def.add_static_constant("EVENT_TRANSLATE_ANIMATION",pragma::BaseAnimatedComponent::EVENT_TRANSLATE_ANIMATION);
	def.add_static_constant("EVENT_TRANSLATE_ACTIVITY",pragma::BaseAnimatedComponent::EVENT_TRANSLATE_ACTIVITY);
	def.add_static_constant("EVENT_MAINTAIN_ANIMATIONS",pragma::BaseAnimatedComponent::EVENT_MAINTAIN_ANIMATIONS);
	def.add_static_constant("EVENT_MAINTAIN_ANIMATION",pragma::BaseAnimatedComponent::EVENT_MAINTAIN_ANIMATION);
	def.add_static_constant("EVENT_MAINTAIN_ANIMATION_MOVEMENT",pragma::BaseAnimatedComponent::EVENT_MAINTAIN_ANIMATION_MOVEMENT);
	def.add_static_constant("EVENT_SHOULD_UPDATE_BONES",pragma::BaseAnimatedComponent::EVENT_SHOULD_UPDATE_BONES);

	def.add_static_constant("EVENT_ON_PLAY_ACTIVITY",pragma::BaseAnimatedComponent::EVENT_ON_PLAY_ACTIVITY);
	def.add_static_constant("EVENT_ON_STOP_LAYERED_ANIMATION",pragma::BaseAnimatedComponent::EVENT_ON_STOP_LAYERED_ANIMATION);
	def.add_static_constant("EVENT_ON_BONE_TRANSFORM_CHANGED",pragma::BaseAnimatedComponent::EVENT_ON_BONE_TRANSFORM_CHANGED);
	def.add_static_constant("EVENT_ON_ANIMATIONS_UPDATED",pragma::BaseAnimatedComponent::EVENT_ON_ANIMATIONS_UPDATED);
	def.add_static_constant("EVENT_UPDATE_BONE_POSES",pragma::BaseAnimatedComponent::EVENT_UPDATE_BONE_POSES);
	def.add_static_constant("EVENT_ON_BONE_POSES_FINALIZED",pragma::BaseAnimatedComponent::EVENT_ON_BONE_POSES_FINALIZED);
	def.add_static_constant("EVENT_ON_BLEND_ANIMATION",pragma::BaseAnimatedComponent::EVENT_ON_BLEND_ANIMATION);
	def.add_static_constant("EVENT_PLAY_ANIMATION",pragma::BaseAnimatedComponent::EVENT_PLAY_ANIMATION);
	def.add_static_constant("EVENT_ON_ANIMATION_RESET",pragma::BaseAnimatedComponent::EVENT_ON_ANIMATION_RESET);

	def.add_static_constant("FPLAYANIM_NONE",umath::to_integral(pragma::FPlayAnim::None));
	def.add_static_constant("FPLAYANIM_RESET",umath::to_integral(pragma::FPlayAnim::Reset));
	def.add_static_constant("FPLAYANIM_TRANSMIT",umath::to_integral(pragma::FPlayAnim::Transmit));
	def.add_static_constant("FPLAYANIM_SNAP_TO",umath::to_integral(pragma::FPlayAnim::SnapTo));
	def.add_static_constant("FPLAYANIM_DEFAULT",umath::to_integral(pragma::FPlayAnim::Default));
	def.add_static_constant("FPLAYANIM_LOOP",umath::to_integral(pragma::FPlayAnim::Loop));
}

#include "pragma/entities/func/basefuncwater.h"
	namespace Lua::FuncWater
	{
		void GetWaterPlane(lua_State *l,pragma::BaseFuncWaterComponent &hEnt,bool bLocalSpace)
		{
			Vector3 n;
			double d;
			if(bLocalSpace == false)
				hEnt.GetWaterPlaneWs(n,d);
			else
				hEnt.GetWaterPlane(n,d);
			Lua::Push<Vector3>(l,n);
			Lua::PushNumber(l,d);
		}

		
		void CalcLineSurfaceIntersection(lua_State *l,pragma::BaseFuncWaterComponent &hEnt,const Vector3 &lineOrigin,const Vector3 &lineDir,bool bCull)
		{
			double t,u,v;
			auto r = hEnt.CalcLineSurfaceIntersection(lineOrigin,lineDir,&t,&u,&v,bCull);
			Lua::PushBool(l,r);
			Lua::PushNumber(l,t);
			Lua::PushNumber(l,u);
			Lua::PushNumber(l,v);
		}
	};
	void pragma::lua::base_func_water_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncWaterComponent> def {"BaseFuncWaterComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("CreateSplash",&pragma::BaseFuncWaterComponent::CreateSplash);
		def.def("GetStiffness",&pragma::BaseFuncWaterComponent::GetStiffness);
		def.def("SetStiffness",&pragma::BaseFuncWaterComponent::SetStiffness);
		def.def("GetPropagation",&pragma::BaseFuncWaterComponent::GetPropagation);
		def.def("SetPropagation",&pragma::BaseFuncWaterComponent::SetPropagation);
		def.def("GetWaterVelocity",&pragma::BaseFuncWaterComponent::GetWaterVelocity);
		def.def("SetWaterVelocity",&pragma::BaseFuncWaterComponent::SetWaterVelocity);
		def.def("GetDensity",&pragma::BaseFuncWaterComponent::GetDensity);
		def.def("SetDensity",&pragma::BaseFuncWaterComponent::SetDensity);
		def.def("GetLinearDragCoefficient",&pragma::BaseFuncWaterComponent::GetLinearDragCoefficient);
		def.def("SetLinearDragCoefficient",&pragma::BaseFuncWaterComponent::SetLinearDragCoefficient);
		def.def("GetTorqueDragCoefficient",&pragma::BaseFuncWaterComponent::GetTorqueDragCoefficient);
		def.def("SetTorqueDragCoefficient",&pragma::BaseFuncWaterComponent::SetTorqueDragCoefficient);
		def.def("CalcLineSurfaceIntersection",static_cast<void(*)(lua_State*,pragma::BaseFuncWaterComponent&,const Vector3&,const Vector3&)>([](lua_State *l,pragma::BaseFuncWaterComponent &hEnt,const Vector3 &lineOrigin,const Vector3 &lineDir) {
			Lua::FuncWater::CalcLineSurfaceIntersection(l,hEnt,lineOrigin,lineDir,false);
		}));
		def.def("CalcLineSurfaceIntersection",&pragma::BaseFuncWaterComponent::CalcLineSurfaceIntersection);
		def.def("GetWaterPlane",static_cast<void(*)(lua_State*,pragma::BaseFuncWaterComponent&,bool)>([](lua_State *l,pragma::BaseFuncWaterComponent &hEnt,bool localSpace) {
			Lua::FuncWater::GetWaterPlane(l,hEnt,localSpace);
		}));
		def.def("GetWaterPlane",static_cast<void(*)(lua_State*,pragma::BaseFuncWaterComponent&)>([](lua_State *l,pragma::BaseFuncWaterComponent &hEnt) {
			Lua::FuncWater::GetWaterPlane(l,hEnt,false);
		}));
		def.def("ProjectToSurface",&pragma::BaseFuncWaterComponent::ProjectToSurface);
		def.add_static_constant("EVENT_ON_WATER_SURFACE_SIMULATOR_CHANGED",pragma::BaseFuncWaterComponent::EVENT_ON_WATER_SURFACE_SIMULATOR_CHANGED);
	}
	#include "pragma/entities/components/basetoggle.h"
	void pragma::lua::base_toggle_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseToggleComponent> def {"BaseToggleComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("TurnOn",&pragma::BaseToggleComponent::TurnOn);
		def.def("TurnOff",&pragma::BaseToggleComponent::TurnOff);
		def.def("Toggle",&pragma::BaseToggleComponent::Toggle);
		def.def("IsTurnedOn",&pragma::BaseToggleComponent::IsTurnedOn);
		def.def("IsTurnedOff",static_cast<bool(*)(lua_State*,pragma::BaseToggleComponent&)>([](lua_State *l,pragma::BaseToggleComponent &hEnt) {return !hEnt.IsTurnedOn();}));
		def.def("SetTurnedOn",&pragma::BaseToggleComponent::SetTurnedOn);
		def.def("GetTurnedOnProperty",&pragma::BaseToggleComponent::GetTurnedOnProperty,luabind::property_policy<0>{});
		def.add_static_constant("EVENT_ON_TURN_ON",pragma::BaseToggleComponent::EVENT_ON_TURN_ON);
		def.add_static_constant("EVENT_ON_TURN_OFF",pragma::BaseToggleComponent::EVENT_ON_TURN_OFF);
	}
	#include "pragma/entities/components/base_wheel_component.hpp"
	void pragma::lua::base_wheel_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseWheelComponent> def {"BaseWheelComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		// TODO
	}
	#include "pragma/entities/environment/env_decal.h"
	void pragma::lua::base_decal_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvDecalComponent> def {"BaseEnvDecalComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}
	#include "pragma/entities/environment/lights/env_light.h"
	void pragma::lua::base_env_light_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvLightComponent> def {"BaseEnvLightComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetFalloffExponent",&pragma::BaseEnvLightComponent::GetFalloffExponent);
		def.def("SetFalloffExponent",&pragma::BaseEnvLightComponent::SetFalloffExponent);
		def.def("SetLightIntensityType",&pragma::BaseEnvLightComponent::SetLightIntensityType);
		def.def("GetLightIntensityType",&pragma::BaseEnvLightComponent::GetLightIntensityType);
		def.def("SetLightIntensity",static_cast<void(pragma::BaseEnvLightComponent::*)(float)>(&pragma::BaseEnvLightComponent::SetLightIntensity));
		def.def("SetLightIntensity",static_cast<void(pragma::BaseEnvLightComponent::*)(float,pragma::BaseEnvLightComponent::LightIntensityType)>(&pragma::BaseEnvLightComponent::SetLightIntensity));
		def.def("GetLightIntensity",&pragma::BaseEnvLightComponent::GetLightIntensity);
		def.def("GetLightIntensityCandela",static_cast<Candela(pragma::BaseEnvLightComponent::*)() const>(&pragma::BaseEnvLightComponent::GetLightIntensityCandela));
		def.add_static_constant("INTENSITY_TYPE_CANDELA",umath::to_integral(pragma::BaseEnvLightComponent::LightIntensityType::Candela));
		def.add_static_constant("INTENSITY_TYPE_LUMEN",umath::to_integral(pragma::BaseEnvLightComponent::LightIntensityType::Lumen));
		def.add_static_constant("INTENSITY_TYPE_LUX",umath::to_integral(pragma::BaseEnvLightComponent::LightIntensityType::Lux));
	}
#include "pragma/entities/environment/lights/env_light_spot.h"
	void pragma::lua::base_env_light_spot_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvLightSpotComponent> def {"BaseEnvLightSpotComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetOuterCutoffAngle",&pragma::BaseEnvLightSpotComponent::SetOuterCutoffAngle);
		def.def("GetOuterCutoffAngle",&pragma::BaseEnvLightSpotComponent::GetOuterCutoffAngle);
		def.def("SetInnerCutoffAngle",&pragma::BaseEnvLightSpotComponent::SetInnerCutoffAngle);
		def.def("GetInnerCutoffAngle",&pragma::BaseEnvLightSpotComponent::GetInnerCutoffAngle);
	}
#include "pragma/entities/environment/lights/env_light_point.h"
	void pragma::lua::base_env_light_point_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvLightPointComponent> def {"BaseEnvLightPointComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}
#include "pragma/entities/environment/lights/env_light_directional.h"
	void pragma::lua::base_env_light_directional_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvLightDirectionalComponent> def {"BaseEnvLightDirectionalComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetAmbientColor",&pragma::BaseEnvLightDirectionalComponent::GetAmbientColor);
		def.def("GetAmbientColorProperty",&pragma::BaseEnvLightDirectionalComponent::GetAmbientColorProperty,luabind::property_policy<0>{});
		def.def("SetAmbientColor",&pragma::BaseEnvLightDirectionalComponent::SetAmbientColor);
	}
#include "pragma/entities/environment/effects/env_particle_system.h"
	void pragma::lua::base_env_particle_system_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvParticleSystemComponent> def {"BaseEnvParticleSystemComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}
#include "pragma/entities/components/base_flammable_component.hpp"
	void pragma::lua::base_flammable_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFlammableComponent> def {"BaseFlammableComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("Ignite",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&,float,BaseEntity&,BaseEntity&)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt,float duration,BaseEntity &attacker,BaseEntity &inflictor) {
			
			hEnt.Ignite(duration,&attacker,&inflictor);
		}));
		def.def("Ignite",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&,float,BaseEntity&)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt,float duration,BaseEntity &attacker) {
			
			hEnt.Ignite(duration,&attacker);
		}));
		def.def("Ignite",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&,float)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt,float duration) {
			
			hEnt.Ignite(duration);
		}));
		def.def("Ignite",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt) {
			
			hEnt.Ignite(0.f);
		}));
		def.def("IsOnFire",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.IsOnFire());
		}));
		def.def("IsIgnitable",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.IsIgnitable());
		}));
		def.def("Extinguish",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt) {
			
			hEnt.Extinguish();
		}));
		def.def("SetIgnitable",static_cast<void(*)(lua_State*,pragma::BaseFlammableComponent&,bool)>([](lua_State *l,pragma::BaseFlammableComponent &hEnt,bool b) {
			
			hEnt.SetIgnitable(b);
		}));
		def.def("GetOnFireProperty",&pragma::BaseFlammableComponent::GetOnFireProperty,luabind::property_policy<0>{});
		def.def("GetIgnitableProperty",&pragma::BaseFlammableComponent::GetIgnitableProperty,luabind::property_policy<0>{});
		def.add_static_constant("EVENT_ON_IGNITED",pragma::BaseFlammableComponent::EVENT_ON_IGNITED);
		def.add_static_constant("EVENT_ON_EXTINGUISHED",pragma::BaseFlammableComponent::EVENT_ON_EXTINGUISHED);
	}

		#include "pragma/entities/components/base_health_component.hpp"
		void pragma::lua::base_health_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseHealthComponent> def {"BaseHealthComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetHealth",static_cast<void(*)(lua_State*,pragma::BaseHealthComponent&)>([](lua_State *l,pragma::BaseHealthComponent &hEnt) {
			
			unsigned short health = hEnt.GetHealth();
			Lua::PushInt(l,health);
		}));
		def.def("SetHealth",static_cast<void(*)(lua_State*,pragma::BaseHealthComponent&,unsigned short)>([](lua_State *l,pragma::BaseHealthComponent &hEnt,unsigned short health) {
			
			hEnt.SetHealth(health);
		}));
		def.def("SetMaxHealth",static_cast<void(*)(lua_State*,pragma::BaseHealthComponent&,uint16_t)>([](lua_State *l,pragma::BaseHealthComponent &hEnt,uint16_t maxHealth) {
			
			hEnt.SetMaxHealth(maxHealth);
		}));
		def.def("GetMaxHealth",static_cast<void(*)(lua_State*,pragma::BaseHealthComponent&)>([](lua_State *l,pragma::BaseHealthComponent &hEnt) {
			
			Lua::PushInt(l,hEnt.GetMaxHealth());
		}));
		def.def("GetHealthProperty",&pragma::BaseHealthComponent::GetHealthProperty,luabind::property_policy<0>{});
		def.def("GetMaxHealthProperty",&pragma::BaseHealthComponent::GetMaxHealthProperty,luabind::property_policy<0>{});
		def.add_static_constant("EVENT_ON_TAKEN_DAMAGE",pragma::BaseHealthComponent::EVENT_ON_TAKEN_DAMAGE);
		def.add_static_constant("EVENT_ON_HEALTH_CHANGED",pragma::BaseHealthComponent::EVENT_ON_HEALTH_CHANGED);
	}

	#include "pragma/entities/components/base_name_component.hpp"
		void pragma::lua::base_name_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseNameComponent> def {"BaseNameComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetName",static_cast<void(*)(lua_State*,pragma::BaseNameComponent&,std::string)>([](lua_State *l,pragma::BaseNameComponent &hEnt,std::string name) {
			
			hEnt.SetName(name);
		}));
		def.def("GetName",static_cast<void(*)(lua_State*,pragma::BaseNameComponent&)>([](lua_State *l,pragma::BaseNameComponent &hEnt) {
			
			Lua::PushString(l,hEnt.GetName());
		}));
		def.def("GetNameProperty",&pragma::BaseNameComponent::GetNameProperty,luabind::property_policy<0>{});
	}

	#include "pragma/entities/components/base_networked_component.hpp"
		void pragma::lua::base_networked_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseNetworkedComponent> def {"BaseNetworkedComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
#if NETWORKED_VARS_ENABLED != 0
		def.def("GetNetVarProperty",static_cast<void(*)(lua_State*,THandle&,uint32_t)>([](lua_State *l,THandle &hEnt,uint32_t id) {
			
			auto &prop = hEnt.GetNetworkedVariableProperty(id);
			if(prop == nullptr)
				return;
			Lua::Property::push(l,*prop);
		}));
		def.def("CreateNetVar",static_cast<void(*)(lua_State*,THandle&,const std::string&,uint32_t)>([](lua_State *l,THandle &hEnt,const std::string &name,uint32_t type) {
			
			auto id = hEnt.CreateNetworkedVariable(name,static_cast<pragma::BaseNetworkedComponent::NetworkedVariable::Type>(type));
			Lua::PushInt(l,id);
		}));
		def.def("SetNetVarValue",static_cast<void(*)(lua_State*,THandle&,uint32_t,luabind::object)>([](lua_State *l,THandle &hEnt,uint32_t id,luabind::object value) {
			
			auto type = hEnt.GetNetworkedVariableType(id);
			if(type == pragma::BaseNetworkedComponent::NetworkedVariable::Type::Invalid)
				return;
			switch(type)
			{
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Bool:
				{
					auto v = Lua::CheckBool(l,3);
					hEnt.SetNetworkedVariable<bool>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Double:
				{
					auto v = Lua::CheckNumber(l,3);
					hEnt.SetNetworkedVariable<double>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Float:
				{
					auto v = Lua::CheckNumber(l,3);
					hEnt.SetNetworkedVariable<float>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int8:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<int8_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int16:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<int16_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int32:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<int32_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int64:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<int64_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::LongDouble:
				{
					auto v = Lua::CheckNumber(l,3);
					hEnt.SetNetworkedVariable<long double>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::String:
				{
					std::string v = Lua::CheckString(l,3);
					hEnt.SetNetworkedVariable<std::string>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt8:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<uint8_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt16:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<uint16_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt32:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<uint32_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt64:
				{
					auto v = Lua::CheckInt(l,3);
					hEnt.SetNetworkedVariable<uint64_t>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::EulerAngles:
				{
					auto &v = *Lua::CheckEulerAngles(l,3);
					hEnt.SetNetworkedVariable<EulerAngles>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Color:
				{
					auto &v = *Lua::CheckColor(l,3);
					hEnt.SetNetworkedVariable<Color>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector:
				{
					auto &v = *Lua::CheckVector(l,3);
					hEnt.SetNetworkedVariable<Vector3>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector2:
				{
					auto &v = *Lua::CheckVector2(l,3);
					hEnt.SetNetworkedVariable<Vector2>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector4:
				{
					auto &v = *Lua::CheckVector4(l,3);
					hEnt.SetNetworkedVariable<Vector4>(id,v);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Entity:
				{
					auto *v = Lua::CheckEntity(l,3);
					auto h = (v != nullptr) ? v->GetHandle() : EntityHandle{};
					hEnt.SetNetworkedVariable<EntityHandle>(id,h);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Quaternion:
				{
					auto &v = *Lua::CheckQuaternion(l,3);
					hEnt.SetNetworkedVariable<Quat>(id,v);
					return;
				}
			}
		}));
		def.def("GetNetVarValue",static_cast<void(*)(lua_State*,THandle&,uint32_t)>([](lua_State *l,THandle &hEnt,uint32_t id) {
			
			auto type = hEnt.GetNetworkedVariableType(id);
			auto &prop = hEnt.GetNetworkedVariableProperty(id);
			if(type == pragma::BaseNetworkedComponent::NetworkedVariable::Type::Invalid || prop == nullptr)
				return;
			switch(type)
			{
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Bool:
					Lua::PushBool(l,static_cast<::util::BoolProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Double:
					Lua::PushNumber(l,static_cast<::util::DoubleProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Float:
					Lua::PushNumber(l,static_cast<::util::FloatProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int8:
					Lua::PushInt(l,static_cast<::util::Int8Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int16:
					Lua::PushInt(l,static_cast<::util::Int16Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int32:
					Lua::PushInt(l,static_cast<::util::Int32Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int64:
					Lua::PushInt(l,static_cast<::util::Int64Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::LongDouble:
					Lua::PushNumber(l,static_cast<::util::LongDoubleProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::String:
					Lua::PushString(l,static_cast<::util::StringProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt8:
					Lua::PushInt(l,static_cast<::util::UInt8Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt16:
					Lua::PushInt(l,static_cast<::util::UInt16Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt32:
					Lua::PushInt(l,static_cast<::util::UInt32Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt64:
					Lua::PushInt(l,static_cast<::util::UInt64Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::EulerAngles:
					Lua::Push<EulerAngles>(l,static_cast<::util::EulerAnglesProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Color:
					Lua::Push<Color>(l,static_cast<::util::ColorProperty&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector:
					Lua::Push<Vector3>(l,static_cast<::util::Vector3Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector2:
					Lua::Push<Vector2>(l,static_cast<::util::Vector2Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector4:
					Lua::Push<Vector4>(l,static_cast<::util::Vector4Property&>(*prop).GetValue());
					return;
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Entity:
				{
					auto &hEnt = static_cast<::pragma::EntityProperty&>(*prop).GetValue();
					if(hEnt.IsValid())
						return;
					hEnt.GetLuaObject()->push(l);
					return;
				}
				case pragma::BaseNetworkedComponent::NetworkedVariable::Type::Quaternion:
					Lua::Push<Quat>(l,static_cast<::util::QuatProperty&>(*prop).GetValue());
					return;
			}
		}));
		def.add_static_constant("NET_VAR_TYPE_BOOL",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Bool));
		def.add_static_constant("NET_VAR_TYPE_DOUBLE",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Double));
		def.add_static_constant("NET_VAR_TYPE_FLOAT",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Float));
		def.add_static_constant("NET_VAR_TYPE_INT8",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int8));
		def.add_static_constant("NET_VAR_TYPE_INT16",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int16));
		def.add_static_constant("NET_VAR_TYPE_INT32",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int32));
		def.add_static_constant("NET_VAR_TYPE_INT64",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Int64));
		def.add_static_constant("NET_VAR_TYPE_LONG_DOUBLE",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::LongDouble));
		def.add_static_constant("NET_VAR_TYPE_STRING",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::String));
		def.add_static_constant("NET_VAR_TYPE_UINT8",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt8));
		def.add_static_constant("NET_VAR_TYPE_UINT16",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt16));
		def.add_static_constant("NET_VAR_TYPE_UINT32",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt32));
		def.add_static_constant("NET_VAR_TYPE_UINT64",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::UInt64));
		def.add_static_constant("NET_VAR_TYPE_EULER_ANGLES",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::EulerAngles));
		def.add_static_constant("NET_VAR_TYPE_COLOR",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Color));
		def.add_static_constant("NET_VAR_TYPE_VECTOR",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector));
		def.add_static_constant("NET_VAR_TYPE_VECTOR2",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector2));
		def.add_static_constant("NET_VAR_TYPE_VECTOR4",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Vector4));
		def.add_static_constant("NET_VAR_TYPE_ENTITY",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Entity));
		def.add_static_constant("NET_VAR_TYPE_QUATERNION",umath::to_integral(pragma::BaseNetworkedComponent::NetworkedVariable::Type::Quaternion));
#endif
	}

	#include "pragma/entities/components/base_observable_component.hpp"
	void pragma::lua::base_observable_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseObservableComponent> def {"BaseObservableComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetLocalCameraOrigin",static_cast<void(*)(lua_State*,pragma::BaseObservableComponent&,uint32_t,const Vector3&)>([](lua_State *l,pragma::BaseObservableComponent &hEnt,uint32_t camType,const Vector3 &origin) {
			
			hEnt.SetLocalCameraOrigin(static_cast<pragma::BaseObservableComponent::CameraType>(camType),origin);
		}));
		def.def("GetLocalCameraOrigin",static_cast<void(*)(lua_State*,pragma::BaseObservableComponent&,uint32_t)>([](lua_State *l,pragma::BaseObservableComponent &hEnt,uint32_t camType) {
			
			Lua::Push<Vector3>(l,hEnt.GetLocalCameraOrigin(static_cast<pragma::BaseObservableComponent::CameraType>(camType)));
		}));
		def.def("SetLocalCameraOffset",static_cast<void(*)(lua_State*,pragma::BaseObservableComponent&,uint32_t,const Vector3&)>([](lua_State *l,pragma::BaseObservableComponent &hEnt,uint32_t camType,const Vector3 &offset) {
			
			hEnt.SetLocalCameraOffset(static_cast<pragma::BaseObservableComponent::CameraType>(camType),offset);
			}));
		def.def("GetLocalCameraOffset",static_cast<void(*)(lua_State*,pragma::BaseObservableComponent&,uint32_t)>([](lua_State *l,pragma::BaseObservableComponent &hEnt,uint32_t camType) {
			
			Lua::Push<Vector3>(l,hEnt.GetLocalCameraOffset(static_cast<pragma::BaseObservableComponent::CameraType>(camType)));
		}));
		def.def("GetCameraData",static_cast<void(*)(lua_State*,pragma::BaseObservableComponent&,uint32_t)>([](lua_State *l,pragma::BaseObservableComponent &hEnt,uint32_t camType) {
			
			Lua::Push<pragma::ObserverCameraData*>(l,&hEnt.GetCameraData(static_cast<pragma::BaseObservableComponent::CameraType>(camType)));
		}));
		def.def("SetCameraEnabled",static_cast<void(*)(lua_State*,pragma::BaseObservableComponent&,uint32_t,bool)>([](lua_State *l,pragma::BaseObservableComponent &hEnt,uint32_t camType,bool enabled) {
			
			hEnt.SetCameraEnabled(static_cast<pragma::BaseObservableComponent::CameraType>(camType),enabled);
		}));
		def.def("GetCameraEnabledProperty",&pragma::BaseObservableComponent::GetCameraEnabledProperty,luabind::property_policy<0>{});
		def.def("GetCameraOffsetProperty",&pragma::BaseObservableComponent::GetCameraOffsetProperty,luabind::property_policy<0>{});
		def.add_static_constant("CAMERA_TYPE_FIRST_PERSON",umath::to_integral(pragma::BaseObservableComponent::CameraType::FirstPerson));
		def.add_static_constant("CAMERA_TYPE_THIRD_PERSON",umath::to_integral(pragma::BaseObservableComponent::CameraType::ThirdPerson));

		auto defObsCamData = luabind::class_<pragma::ObserverCameraData>("CameraData");
		defObsCamData.def_readwrite("rotateWithObservee",&pragma::ObserverCameraData::rotateWithObservee);
		defObsCamData.def("SetAngleLimits",static_cast<void(*)(lua_State*,pragma::ObserverCameraData&,const EulerAngles&,const EulerAngles&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData,const EulerAngles &min,const EulerAngles &max) {
			obsCamData.angleLimits = {min,max};
		}));
		defObsCamData.def("GetAngleLimits",static_cast<void(*)(lua_State*,pragma::ObserverCameraData&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData) {
			if(obsCamData.angleLimits.has_value() == false)
				return;
			Lua::Push<EulerAngles>(l,obsCamData.angleLimits->first);
			Lua::Push<EulerAngles>(l,obsCamData.angleLimits->second);
		}));
		defObsCamData.def("ClearAngleLimits",static_cast<void(*)(lua_State*,pragma::ObserverCameraData&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData) {
			obsCamData.angleLimits = {};
		}));
		defObsCamData.property("enabled",static_cast<void(*)(lua_State*,pragma::ObserverCameraData&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData) {
			Lua::PushBool(l,*obsCamData.enabled);
		}),static_cast<void(*)(lua_State*,pragma::ObserverCameraData&,bool)>([](lua_State *l,pragma::ObserverCameraData &obsCamData,bool enabled) {
			*obsCamData.enabled = enabled;
		}));
		defObsCamData.property("localOrigin",static_cast<void(*)(lua_State*,pragma::ObserverCameraData&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData) {
			if(obsCamData.localOrigin.has_value() == false)
				return;
			Lua::Push<Vector3>(l,*obsCamData.localOrigin);
		}),static_cast<void(*)(lua_State*,pragma::ObserverCameraData&,const Vector3&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData,const Vector3 &origin) {
			obsCamData.localOrigin = origin;
		}));
		defObsCamData.property("offset",static_cast<void(*)(lua_State*,pragma::ObserverCameraData&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData) {
			Lua::Push<Vector3>(l,*obsCamData.offset);
		}),static_cast<void(*)(lua_State*,pragma::ObserverCameraData&,const Vector3&)>([](lua_State *l,pragma::ObserverCameraData &obsCamData,const Vector3 &offset) {
			*obsCamData.offset = offset;
		}));
		def.scope[defObsCamData];
	}

	#include "pragma/entities/components/base_shooter_component.hpp"
#include "pragma/util/bulletinfo.h"
namespace Lua::TraceData {void FillTraceResultTable(lua_State *l,TraceResult &res);};
	namespace Lua::Shooter
	{
		void FireBullets(lua_State *l,pragma::BaseShooterComponent &hEnt,const luabind::object&,bool bHitReport,bool bMaster)
		{
			auto *bulletInfo = Lua::CheckBulletInfo(l,2);

			std::vector<TraceResult> results;
			hEnt.FireBullets(*bulletInfo,results,bMaster);
			if(bHitReport == false)
				return;
			auto t = Lua::CreateTable(l);
			for(auto i=decltype(results.size()){0};i<results.size();++i)
			{
				auto &r = results[i];
				Lua::PushInt(l,i +1);
				Lua::TraceData::FillTraceResultTable(l,r);

				Lua::SetTableValue(l,t);
			}
		}
	};
		void pragma::lua::base_shooter_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseShooterComponent> def {"BaseShooterComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("FireBullets",static_cast<void(*)(lua_State*,pragma::BaseShooterComponent&,const luabind::object&,bool,bool)>([](lua_State *l,pragma::BaseShooterComponent &hEnt,const luabind::object &o,bool bHitReport,bool bMaster) {
			Lua::Shooter::FireBullets(l,hEnt,o,bHitReport,bMaster);
		}));
		def.def("FireBullets",static_cast<void(*)(lua_State*,pragma::BaseShooterComponent&,const luabind::object&,bool)>([](lua_State *l,pragma::BaseShooterComponent &hEnt,const luabind::object &o,bool bHitReport) {
			Lua::Shooter::FireBullets(l,hEnt,o,bHitReport,Lua::get_bullet_master(hEnt.GetEntity()));
		}));
		def.def("FireBullets",static_cast<void(*)(lua_State*,pragma::BaseShooterComponent&,const luabind::object&)>([](lua_State *l,pragma::BaseShooterComponent &hEnt,const luabind::object &o) {
			Lua::Shooter::FireBullets(l,hEnt,o,false,Lua::get_bullet_master(hEnt.GetEntity()));
		}));
		def.add_static_constant("EVENT_ON_FIRE_BULLETS",pragma::BaseShooterComponent::EVENT_ON_FIRE_BULLETS);
	}

	#include "pragma/entities/components/base_physics_component.hpp"
#include "pragma/physics/constraint.hpp"
#include "pragma/physics/movetypes.h"
	namespace Lua::Physics
	{
		void InitializePhysics(lua_State *l,pragma::BasePhysicsComponent &hEnt,::util::TSharedHandle<pragma::physics::IConvexShape> &shape,uint32_t flags)
		{
			auto *phys = hEnt.InitializePhysics(*shape,static_cast<pragma::BasePhysicsComponent::PhysFlags>(flags));
			if(phys != NULL)
				luabind::object(l,phys->GetHandle()).push(l);
		}
		void InitializePhysics(lua_State *l,pragma::BasePhysicsComponent &hEnt,::util::TSharedHandle<pragma::physics::IConvexShape> &shape)
			{
				InitializePhysics(l,hEnt,shape,umath::to_integral(pragma::BasePhysicsComponent::PhysFlags::None));
			}
	};
		void pragma::lua::base_physics_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePhysicsComponent> def {"BasePhysicsComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetCollisionBounds",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,Vector3,Vector3)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,Vector3 min,Vector3 max) {
			
			hEnt.SetCollisionBounds(min,max);
		}));
		def.def("GetCollisionBounds",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Vector3 min,max;
			hEnt.GetCollisionBounds(&min,&max);
			luabind::object(l,min).push(l);
			luabind::object(l,max).push(l);
		}));
		def.def("GetCollisionExtents",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			luabind::object(l,hEnt.GetCollisionExtents()).push(l);
		}));
		def.def("GetCollisionCenter",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			luabind::object(l,hEnt.GetCollisionCenter()).push(l);
		}));
		def.def("GetMoveType",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			MOVETYPE mt = hEnt.GetMoveType();
			Lua::PushInt(l,int(mt));
		}));
		def.def("SetMoveType",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,int)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,int moveType) {
			
			hEnt.SetMoveType(MOVETYPE(moveType));
		}));
		def.def("GetPhysicsObject",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			PhysObj *phys = hEnt.GetPhysicsObject();
			if(phys == NULL)
				return;
			luabind::object(l,phys->GetHandle()).push(l);
		}));
		def.def("InitializePhysics",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,uint32_t,uint32_t)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,uint32_t type,uint32_t physFlags) {
			

			PhysObj *phys = hEnt.InitializePhysics(PHYSICSTYPE(type),static_cast<pragma::BasePhysicsComponent::PhysFlags>(physFlags));
			if(phys != NULL)
				luabind::object(l,phys->GetHandle()).push(l);
		}));
		def.def("InitializePhysics",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,uint32_t)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,uint32_t type) {
			
			
			PhysObj *phys = hEnt.InitializePhysics(PHYSICSTYPE(type));
			if(phys != NULL)
				luabind::object(l,phys->GetHandle()).push(l);
		}));
		def.def("InitializePhysics",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,::util::TSharedHandle<pragma::physics::IConvexShape>&,uint32_t)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,::util::TSharedHandle<pragma::physics::IConvexShape> &shape,uint32_t physFlags) {
			Lua::Physics::InitializePhysics(l,hEnt,shape,physFlags);
		}));
		def.def("InitializePhysics",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,::util::TSharedHandle<pragma::physics::IConvexShape>&,uint32_t)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,::util::TSharedHandle<pragma::physics::IConvexShape> &shape,uint32_t physFlags) {
			Lua::Physics::InitializePhysics(l,hEnt,shape,physFlags);
		}));
		def.def("InitializePhysics",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,::util::TSharedHandle<pragma::physics::IConvexShape>&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,::util::TSharedHandle<pragma::physics::IConvexShape> &shape) {
			Lua::Physics::InitializePhysics(l,hEnt,shape,0);
		}));
		def.def("DestroyPhysicsObject",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			hEnt.DestroyPhysicsObject();
		}));
		def.def("DropToFloor",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			hEnt.DropToFloor();
		}));
		def.def("IsTrigger",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.IsTrigger());
		}));
		def.def("SetKinematic",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,bool)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,bool b) {
			
			hEnt.SetKinematic(b);
		}));
		def.def("IsKinematic",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.IsKinematic());
		}));

		def.def("GetCollisionCallbacksEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.GetCollisionCallbacksEnabled());
		}));
		def.def("SetCollisionCallbacksEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,bool)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,bool) {
			
			hEnt.SetCollisionCallbacksEnabled(true);
		}));
		def.def("GetCollisionContactReportEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.GetCollisionContactReportEnabled());
		}));
		def.def("SetCollisionContactReportEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,bool)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,bool) {
			
			hEnt.SetCollisionContactReportEnabled(true);
		}));
		def.def("SetCollisionFilterMask",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,int)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,int mask) {
			
			hEnt.SetCollisionFilterMask(static_cast<CollisionMask>(mask));
		}));
		def.def("GetCollisionFilterMask",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushInt(l,hEnt.GetCollisionFilterMask());
		}));
		def.def("SetCollisionFilterGroup",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,int)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,int group) {
			
			hEnt.SetCollisionFilterGroup(static_cast<CollisionMask>(group));
		}));
		def.def("GetCollisionFilterGroup",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushInt(l,hEnt.GetCollisionFilter());
		}));
		def.def("SetCollisionFilter",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,int,int)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,int group,int mask) {
			
			hEnt.SetCollisionFilter(static_cast<CollisionMask>(group),static_cast<CollisionMask>(mask));
		}));
		def.def("EnableCollisions",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,pragma::BasePhysicsComponent &hEntOther) {
			
			
			hEnt.EnableCollisions(&hEntOther.GetEntity());
		}));
		def.def("DisableCollisions",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,pragma::BasePhysicsComponent &hEntOther) {
			
			
			hEnt.DisableCollisions(&hEntOther.GetEntity());
		}));
		def.def("SetCollisionsEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,pragma::BasePhysicsComponent&,bool)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,pragma::BasePhysicsComponent &hEntOther,bool b) {
			
			
			hEnt.SetCollisionsEnabled(&hEntOther.GetEntity(),b);
		}));
		def.def("EnableCollisions",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			hEnt.SetCollisionsEnabled(true);
		}));
		def.def("DisableCollisions",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			hEnt.SetCollisionsEnabled(false);
		}));
		def.def("SetCollisionsEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,bool)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,bool b) {
			
			hEnt.SetCollisionsEnabled(b);
		}));
		def.def("SetSimulationEnabled",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,bool)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,bool b) {
			
			hEnt.SetSimulationEnabled(b);
		}));
		def.def("IsSimulationEnabled",static_cast<bool(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) -> bool {
			
			return hEnt.GetSimulationEnabled();
		}));
		def.def("ResetCollisions",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,pragma::BasePhysicsComponent &hEntOther) {
			
			
			hEnt.ResetCollisions(&hEntOther.GetEntity());
		}));

		def.def("GetPhysJointConstraints",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			auto &joints = hEnt.GetPhysConstraints();
			auto table = Lua::CreateTable(l); /* 1 */
			auto n = 1;
			for(auto it=joints.begin();it!=joints.end();++it)
			{
				auto &joint = *it;
				if(joint.constraint.IsValid())
				{
					auto tConstraint = Lua::CreateTable(l); /* 2 */

					Lua::PushString(l,"source"); /* 3 */
					Lua::PushInt(l,joint.source); /* 4 */
					Lua::SetTableValue(l,tConstraint); /* 2 */

					Lua::PushString(l,"target"); /* 3 */
					Lua::PushInt(l,joint.target); /* 4 */
					Lua::SetTableValue(l,tConstraint); /* 2 */

					Lua::PushString(l,"constraint"); /* 3 */
					joint.constraint->Push(l); /* 4 */
					Lua::SetTableValue(l,tConstraint); /* 2 */

					Lua::PushInt(l,n); /* 3 */
					Lua::PushValue(l,tConstraint); /* 4 */
					Lua::SetTableValue(l,table); /* 2 */
					Lua::Pop(l,1); /* 1 */
					n++;
				}
			}
		}));
		def.def("GetRotatedCollisionBounds",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Vector3 min,max;
			hEnt.GetRotatedCollisionBounds(&min,&max);
			Lua::Push<Vector3>(l,min);
			Lua::Push<Vector3>(l,max);
		}));

		def.def("GetPhysicsType",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			auto type = hEnt.GetPhysicsType();
			Lua::Push<std::underlying_type_t<decltype(type)>>(l,umath::to_integral(type));
		}));
		def.def("GetCollisionRadius",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetCollisionRadius());
		}));
		def.def("IsPhysicsProp",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			auto physType = hEnt.GetPhysicsType();
			Lua::PushBool(l,(physType != PHYSICSTYPE::NONE && physType != PHYSICSTYPE::STATIC && physType != PHYSICSTYPE::BOXCONTROLLER && physType != PHYSICSTYPE::CAPSULECONTROLLER) ? true : false);
		}));

		def.def("GetAABBDistance",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &p) {
			
			Lua::PushNumber(l,hEnt.GetAABBDistance(p));
		}));
		def.def("GetAABBDistance",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,pragma::BasePhysicsComponent &hOther) {
			
			Lua::PushNumber(l,hEnt.GetAABBDistance(hOther.GetEntity()));
		}));
		def.def("GetAABBDistance",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,BaseEntity&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,BaseEntity &other) {
			
			Lua::PushNumber(l,hEnt.GetAABBDistance(other));
		}));

		def.def("IsRagdoll",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.IsRagdoll());
		}));

		def.def("ApplyForce",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &force) {
			
			hEnt.ApplyForce(force);
		}));
		def.def("ApplyForce",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &force,const Vector3 &relPos) {
			
			hEnt.ApplyForce(force,relPos);
		}));
		def.def("ApplyImpulse",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &impulse) {
			
			hEnt.ApplyImpulse(impulse);
		}));
		def.def("ApplyImpulse",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &impulse,const Vector3 &relPos) {
			
			hEnt.ApplyImpulse(impulse,relPos);
		}));
		def.def("ApplyTorque",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &torque) {
			
			hEnt.ApplyTorque(torque);
		}));
		def.def("ApplyTorqueImpulse",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&,const Vector3&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt,const Vector3 &torque) {
			
			hEnt.ApplyTorqueImpulse(torque);
		}));
		def.def("GetMass",static_cast<void(*)(lua_State*,pragma::BasePhysicsComponent&)>([](lua_State *l,pragma::BasePhysicsComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetMass());
		}));
		def.add_static_constant("EVENT_ON_PHYSICS_INITIALIZED",pragma::BasePhysicsComponent::EVENT_ON_PHYSICS_INITIALIZED);
		def.add_static_constant("EVENT_ON_PHYSICS_DESTROYED",pragma::BasePhysicsComponent::EVENT_ON_PHYSICS_DESTROYED);
		def.add_static_constant("EVENT_ON_PHYSICS_UPDATED",pragma::BasePhysicsComponent::EVENT_ON_PHYSICS_UPDATED);
		def.add_static_constant("EVENT_ON_DYNAMIC_PHYSICS_UPDATED",pragma::BasePhysicsComponent::EVENT_ON_DYNAMIC_PHYSICS_UPDATED);
		def.add_static_constant("EVENT_ON_PRE_PHYSICS_SIMULATE",pragma::BasePhysicsComponent::EVENT_ON_PRE_PHYSICS_SIMULATE);
		def.add_static_constant("EVENT_ON_POST_PHYSICS_SIMULATE",pragma::BasePhysicsComponent::EVENT_ON_POST_PHYSICS_SIMULATE);
		def.add_static_constant("EVENT_ON_WAKE",pragma::BasePhysicsComponent::EVENT_ON_WAKE);
		def.add_static_constant("EVENT_ON_SLEEP",pragma::BasePhysicsComponent::EVENT_ON_SLEEP);
		def.add_static_constant("EVENT_HANDLE_RAYCAST",pragma::BasePhysicsComponent::EVENT_HANDLE_RAYCAST);
		def.add_static_constant("EVENT_INITIALIZE_PHYSICS",pragma::BasePhysicsComponent::EVENT_INITIALIZE_PHYSICS);

		def.add_static_constant("MOVETYPE_NONE",umath::to_integral(MOVETYPE::NONE));
		def.add_static_constant("MOVETYPE_WALK",umath::to_integral(MOVETYPE::WALK));
		def.add_static_constant("MOVETYPE_NOCLIP",umath::to_integral(MOVETYPE::NOCLIP));
		def.add_static_constant("MOVETYPE_FLY",umath::to_integral(MOVETYPE::FLY));
		def.add_static_constant("MOVETYPE_FREE",umath::to_integral(MOVETYPE::FREE));
		def.add_static_constant("MOVETYPE_PHYSICS",umath::to_integral(MOVETYPE::PHYSICS));
	}

	#include "pragma/entities/components/base_render_component.hpp"
		void pragma::lua::base_render_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseRenderComponent> def {"BaseRenderComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetCastShadows",static_cast<void(*)(lua_State*,pragma::BaseRenderComponent&,bool)>([](lua_State *l,pragma::BaseRenderComponent &hEnt,bool b) {
			
			hEnt.SetCastShadows(b);
		}));
		def.def("GetCastShadows",static_cast<void(*)(lua_State*,pragma::BaseRenderComponent&)>([](lua_State *l,pragma::BaseRenderComponent &hEnt) {
			
			Lua::PushBool(l,hEnt.GetCastShadows());
		}));
	}

	#include "pragma/entities/components/base_softbody_component.hpp"
		void pragma::lua::base_soft_body_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseSoftBodyComponent> def {"BaseSoftBodyComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		
	}

	#include "pragma/entities/components/base_sound_emitter_component.hpp"
	namespace Lua::SoundEmitter
	{
		void EmitSound(lua_State *l,pragma::BaseSoundEmitterComponent &hEnt,std::string sndname,uint32_t soundType,float gain,float pitch)
		{
			std::shared_ptr<ALSound> snd = hEnt.EmitSound(sndname,static_cast<ALSoundType>(soundType),gain,pitch);
			if(snd == nullptr)
				return;
			luabind::object(l,snd).push(l);
		}
	};
		void pragma::lua::base_sound_emitter_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseSoundEmitterComponent> def {"BaseSoundEmitterComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("CreateSound",static_cast<void(*)(lua_State*,pragma::BaseSoundEmitterComponent&,std::string,uint32_t)>([](lua_State *l,pragma::BaseSoundEmitterComponent &hEnt,std::string sndname,uint32_t soundType) {
			
			std::shared_ptr<ALSound> snd = hEnt.CreateSound(sndname,static_cast<ALSoundType>(soundType));
			if(snd == nullptr)
				return;
			luabind::object(l,snd).push(l);
		}));
		def.def("EmitSound",static_cast<void(*)(lua_State*,pragma::BaseSoundEmitterComponent&,std::string,uint32_t,float,float)>([](lua_State *l,pragma::BaseSoundEmitterComponent &hEnt,std::string sndname,uint32_t soundType,float gain,float pitch) {
			Lua::SoundEmitter::EmitSound(l,hEnt,sndname,soundType,gain,pitch);
		}));
		def.def("EmitSound",static_cast<void(*)(lua_State*,pragma::BaseSoundEmitterComponent&,std::string,uint32_t,float)>([](lua_State *l,pragma::BaseSoundEmitterComponent &hEnt,std::string sndname,uint32_t soundType,float gain) {
			Lua::SoundEmitter::EmitSound(l,hEnt,sndname,soundType,gain,1.f);
		}));
		def.def("EmitSound",static_cast<void(*)(lua_State*,pragma::BaseSoundEmitterComponent&,std::string,uint32_t)>([](lua_State *l,pragma::BaseSoundEmitterComponent &hEnt,std::string sndname,uint32_t soundType) {
			Lua::SoundEmitter::EmitSound(l,hEnt,sndname,soundType,1.f,1.f);
		}));
		def.def("StopSounds",static_cast<void(*)(lua_State*,pragma::BaseSoundEmitterComponent&)>([](lua_State *l,pragma::BaseSoundEmitterComponent &hEnt) {
			
			hEnt.StopSounds();
		}));
		def.def("GetSounds",static_cast<void(*)(lua_State*,pragma::BaseSoundEmitterComponent&)>([](lua_State *l,pragma::BaseSoundEmitterComponent &hEnt) {
			
			std::vector<std::shared_ptr<ALSound>> *sounds;
			hEnt.GetSounds(&sounds);
			lua_newtable(l);
			int top = lua_gettop(l);
			for(int i=0;i<sounds->size();i++)
			{
				luabind::object(l,(*sounds)[i]).push(l);
				lua_rawseti(l,top,i +1);
			}
		}));
		def.add_static_constant("EVENT_ON_SOUND_CREATED",pragma::BaseSoundEmitterComponent::EVENT_ON_SOUND_CREATED);
	}

	#include "pragma/entities/components/base_transform_component.hpp"
	namespace Lua::Transform
	{
		
			void GetDirection(lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p,bool bIgnoreYAxis)
		{
			
			Lua::Push<Vector3>(l,hEnt.GetDirection(p,bIgnoreYAxis));
		}
		
			void GetDirection(lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther,bool bIgnoreYAxis)
		{
			
			Lua::Push<Vector3>(l,hEnt.GetDirection(hOther.GetEntity(),bIgnoreYAxis));
		}
		
			void GetDirection(lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &entOther,bool bIgnoreYAxis)
		{
			
			Lua::Push<Vector3>(l,hEnt.GetDirection(entOther,bIgnoreYAxis));
		}
		
			void GetAngles(lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p,bool bIgnoreYAxis)
		{
			
			Lua::Push<EulerAngles>(l,hEnt.GetAngles(p,bIgnoreYAxis));
		}
		
			void GetAngles(lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther,bool bIgnoreYAxis)
		{
			
			Lua::Push<EulerAngles>(l,hEnt.GetAngles(hOther.GetEntity(),bIgnoreYAxis));
		}
		
			void GetAngles(lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &entOther,bool bIgnoreYAxis)
		{
			
			Lua::Push<EulerAngles>(l,hEnt.GetAngles(entOther,bIgnoreYAxis));
		}
		
			void GetDotProduct(lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p,bool bIgnoreYAxis)
		{
			
			Lua::PushNumber(l,hEnt.GetDotProduct(p,bIgnoreYAxis));
		}
		
			void GetDotProduct(lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther,bool bIgnoreYAxis)
		{
			
			Lua::PushNumber(l,hEnt.GetDotProduct(hOther.GetEntity(),bIgnoreYAxis));
		}
		
			void GetDotProduct(lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other,bool bIgnoreYAxis)
		{
			
			Lua::PushNumber(l,hEnt.GetDotProduct(other,bIgnoreYAxis));
		}
	};
		void pragma::lua::base_transform_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTransformComponent> def {"BaseTransformComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetOrigin",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			luabind::object(l,hEnt.GetOrigin()).push(l);
		}));
		def.def("GetPos",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			luabind::object(l,hEnt.GetPosition()).push(l);
		}));
		def.def("SetPos",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Vector3)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Vector3 pos) {
			
			hEnt.SetPosition(pos);
		}));
		def.def("GetRotation",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			luabind::object(l,hEnt.GetRotation()).push(l);
		}));
		def.def("SetRotation",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Quat)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Quat q) {
			
			hEnt.SetRotation(q);
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			EulerAngles ang = hEnt.GetAngles();
			luabind::object(l,ang).push(l);
		}));
		def.def("SetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,EulerAngles)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,EulerAngles ang) {
			
			hEnt.SetAngles(ang);
		}));
		def.def("GetForward",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			luabind::object(l,hEnt.GetForward()).push(l);
		}));
		def.def("GetRight",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			luabind::object(l,hEnt.GetRight()).push(l);
		}));
		def.def("GetUp",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			luabind::object(l,hEnt.GetUp()).push(l);
		}));

		def.def("GetEyePos",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::Push<Vector3>(l,hEnt.GetEyePosition());
		}));
		def.def("GetEyeOffset",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::Push<Vector3>(l,hEnt.GetEyeOffset());
		}));
		def.def("SetEyeOffset",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Vector3&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Vector3 &offset) {
			
			hEnt.SetEyeOffset(offset);
		}));

		def.def("LocalToWorld",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Vector3)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Vector3 origin) {
			
			hEnt.LocalToWorld(&origin);
			Lua::Push<Vector3>(l,origin);
		}));
		def.def("LocalToWorld",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Quat)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Quat rot) {
			
			hEnt.LocalToWorld(&rot);
			Lua::Push<Quat>(l,rot);
		}));
		def.def("LocalToWorld",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Vector3,Quat)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Vector3 origin,Quat rot) {
			
			hEnt.LocalToWorld(&origin,&rot);
			Lua::Push<Vector3>(l,origin);
			Lua::Push<Quat>(l,rot);
		}));
		def.def("WorldToLocal",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Vector3)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Vector3 origin) {
			
			hEnt.WorldToLocal(&origin);
			Lua::Push<Vector3>(l,origin);
		}));
		def.def("WorldToLocal",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Quat)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Quat rot) {
			
			hEnt.WorldToLocal(&rot);
			Lua::Push<Quat>(l,rot);
		}));
		def.def("WorldToLocal",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,Vector3,Quat)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,Vector3 origin,Quat rot) {
			
			hEnt.WorldToLocal(&origin,&rot);
			Lua::Push<Vector3>(l,origin);
			Lua::Push<Quat>(l,rot);
		}));

		def.def("GetPitch",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetPitch());
		}));
		def.def("GetYaw",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetYaw());
		}));
		def.def("GetRoll",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetRoll());
		}));
		def.def("SetPitch",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,float)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,float pitch) {
			
			hEnt.SetPitch(pitch);
		}));
		def.def("SetYaw",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,float)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,float yaw) {
			
			hEnt.SetYaw(yaw);
		}));
		def.def("SetRoll",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,float)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,float roll) {
			
			hEnt.SetRoll(roll);
		}));

		def.def("GetLastMoveTime",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetLastMoveTime());
		}));
		def.def("GetScale",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::Push<Vector3>(l,hEnt.GetScale());
		}));
		def.def("GetMaxAxisScale",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetMaxAxisScale());
		}));
		def.def("GetAbsMaxAxisScale",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt) {
			
			Lua::PushNumber(l,hEnt.GetAbsMaxAxisScale());
		}));
		def.def("SetScale",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &scale) {
			
			hEnt.SetScale(scale);
		}));
		def.def("SetScale",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,float)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,float scale) {
			
			hEnt.SetScale(Vector3{scale,scale,scale});
		}));

		def.def("GetDistance",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p) {
			
			Lua::PushNumber(l,hEnt.GetDistance(p));
		}));
		def.def("GetDistance",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther) {
			
			Lua::PushNumber(l,hEnt.GetDistance(hOther.GetEntity()));
		}));
		def.def("GetDistance",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other) {
			
			Lua::PushNumber(l,hEnt.GetDistance(other));
		}));

		def.def("GetDirection",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p,bool bIgnoreYAxis) {
			
			Lua::Push<Vector3>(l,hEnt.GetDirection(p,bIgnoreYAxis));
		}));
		def.def("GetDirection",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther,bool bIgnoreYAxis) {
			
			Lua::Push<Vector3>(l,hEnt.GetDirection(hOther.GetEntity(),bIgnoreYAxis));
		}));
		def.def("GetDirection",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other,bool bIgnoreYAxis) {
			
			Lua::Push<Vector3>(l,hEnt.GetDirection(other,bIgnoreYAxis));
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p,bool bIgnoreYAxis) {
			
			Lua::Push<EulerAngles>(l,hEnt.GetAngles(p,bIgnoreYAxis));
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther,bool bIgnoreYAxis) {
			
			Lua::Push<EulerAngles>(l,hEnt.GetAngles(hOther.GetEntity(),bIgnoreYAxis));
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other,bool bIgnoreYAxis) {
			
			Lua::Push<EulerAngles>(l,hEnt.GetAngles(other,bIgnoreYAxis));
		}));
		def.def("GetDotProduct",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p,bool bIgnoreYAxis) {
			
			Lua::PushNumber(l,hEnt.GetDotProduct(p,bIgnoreYAxis));
		}));
		def.def("GetDotProduct",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther,bool bIgnoreYAxis) {
			
			Lua::PushNumber(l,hEnt.GetDotProduct(hOther.GetEntity(),bIgnoreYAxis));
		}));
		def.def("GetDotProduct",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&,bool)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other,bool bIgnoreYAxis) {
			
			Lua::PushNumber(l,hEnt.GetDotProduct(other,bIgnoreYAxis));
		}));

		def.def("GetDirection",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p) {
			Lua::Transform::GetDirection(l,hEnt,p,false);
		}));
		def.def("GetDirection",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther) {
			Lua::Transform::GetDirection(l,hEnt,hOther,false);
		}));
		def.def("GetDirection",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other) {
			Lua::Transform::GetDirection(l,hEnt,other,false);
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p) {
			Lua::Transform::GetAngles(l,hEnt,p,false);
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther) {
			Lua::Transform::GetAngles(l,hEnt,hOther,false);
		}));
		def.def("GetAngles",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other) {
			Lua::Transform::GetAngles(l,hEnt,other,false);
		}));
		def.def("GetDotProduct",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,const Vector3&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,const Vector3 &p) {
			Lua::Transform::GetDotProduct(l,hEnt,p,false);
		}));
		def.def("GetDotProduct",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,pragma::BaseTransformComponent&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,pragma::BaseTransformComponent &hOther) {
			Lua::Transform::GetDotProduct(l,hEnt,hOther,false);
		}));
		def.def("GetDotProduct",static_cast<void(*)(lua_State*,pragma::BaseTransformComponent&,BaseEntity&)>([](lua_State *l,pragma::BaseTransformComponent &hEnt,BaseEntity &other) {
			Lua::Transform::GetDotProduct(l,hEnt,other,false);
		}));
	}

	#include "pragma/entities/components/base_color_component.hpp"
	void pragma::lua::base_color_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseColorComponent> def {"BaseColorComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetColorProperty",&pragma::BaseColorComponent::GetColorProperty,luabind::property_policy<0>{});

		def.def("GetColor",&pragma::BaseColorComponent::GetColor);
		def.def("SetColor",static_cast<void(pragma::BaseColorComponent::*)(const Color&)>(&pragma::BaseColorComponent::SetColor));
		def.def("SetColor",static_cast<void(pragma::BaseColorComponent::*)(const Vector3&)>(&pragma::BaseColorComponent::SetColor));
		def.def("SetColor",static_cast<void(pragma::BaseColorComponent::*)(const Vector4&)>(&pragma::BaseColorComponent::SetColor));
		def.add_static_constant("EVENT_ON_COLOR_CHANGED",pragma::BaseColorComponent::EVENT_ON_COLOR_CHANGED);
	}

	#include "pragma/entities/components/base_score_component.hpp"
		void pragma::lua::base_score_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseScoreComponent> def {"BaseScoreComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
			def.def("GetScoreProperty",&pragma::BaseScoreComponent::GetScoreProperty,luabind::property_policy<0>{});
			def.def("GetScore",&pragma::BaseScoreComponent::GetScore);
			def.def("SetScore",&pragma::BaseScoreComponent::SetScore);
			def.def("AddScore",&pragma::BaseScoreComponent::AddScore);
			def.def("SubtractScore",&pragma::BaseScoreComponent::SubtractScore);
			def.add_static_constant("EVENT_ON_SCORE_CHANGED",pragma::BaseScoreComponent::EVENT_ON_SCORE_CHANGED);
		}

	#include "pragma/entities/components/base_radius_component.hpp"
		void pragma::lua::base_radius_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseRadiusComponent> def {"BaseRadiusComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetRadiusProperty",&pragma::BaseRadiusComponent::GetRadiusProperty,luabind::property_policy<0>{});
		def.def("GetRadius",&pragma::BaseRadiusComponent::GetRadius);
		def.def("SetRadius",&pragma::BaseRadiusComponent::SetRadius);
		def.add_static_constant("EVENT_ON_RADIUS_CHANGED",pragma::BaseRadiusComponent::EVENT_ON_RADIUS_CHANGED);
	}

	#include "pragma/entities/environment/audio/env_sound_dsp.h"
		void pragma::lua::base_env_sound_dsp_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvSoundDspComponent> def {"BaseEnvSoundDspComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_camera.h"
		void pragma::lua::base_env_camera_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvCameraComponent> def {"BaseEnvCameraComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.add_static_constant("DEFAULT_NEAR_Z",pragma::BaseEnvCameraComponent::DEFAULT_NEAR_Z);
		def.add_static_constant("DEFAULT_FAR_Z",pragma::BaseEnvCameraComponent::DEFAULT_FAR_Z);
		def.add_static_constant("DEFAULT_FOV",pragma::BaseEnvCameraComponent::DEFAULT_FOV);
		def.add_static_constant("DEFAULT_VIEWMODEL_FOV",pragma::BaseEnvCameraComponent::DEFAULT_VIEWMODEL_FOV);
		def.def("GetProjectionMatrix",&pragma::BaseEnvCameraComponent::GetProjectionMatrix);
		def.def("GetViewMatrix",&pragma::BaseEnvCameraComponent::GetViewMatrix);
		def.def("LookAt",static_cast<void(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector3&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector3 &lookAtPos) {
			auto *trComponent = hComponent.GetEntity().GetTransformComponent();
			if(!trComponent)
				return;
			auto &camPos = trComponent->GetPosition();
			auto dir = lookAtPos -camPos;
			uvec::normalize(&dir);
			trComponent->SetRotation(uquat::create_look_rotation(dir,trComponent->GetUp()));
		}));
		def.def("UpdateMatrices",&pragma::BaseEnvCameraComponent::UpdateMatrices);
		def.def("UpdateViewMatrix",&pragma::BaseEnvCameraComponent::UpdateViewMatrix);
		def.def("UpdateProjectionMatrix",&pragma::BaseEnvCameraComponent::UpdateProjectionMatrix);
		def.def("SetFOV",&pragma::BaseEnvCameraComponent::SetFOV);
		def.def("GetProjectionMatrixProperty",&pragma::BaseEnvCameraComponent::GetProjectionMatrixProperty,luabind::property_policy<0>{});
		def.def("GetViewMatrixProperty",&pragma::BaseEnvCameraComponent::GetViewMatrixProperty,luabind::property_policy<0>{});
		def.def("GetNearZProperty",&pragma::BaseEnvCameraComponent::GetNearZProperty,luabind::property_policy<0>{});
		def.def("GetFarZProperty",&pragma::BaseEnvCameraComponent::GetFarZProperty,luabind::property_policy<0>{});
		def.def("GetFOVProperty",&pragma::BaseEnvCameraComponent::GetFOVProperty,luabind::property_policy<0>{});
		def.def("GetAspectRatioProperty",&pragma::BaseEnvCameraComponent::GetAspectRatioProperty,luabind::property_policy<0>{});
		def.def("SetAspectRatio",&pragma::BaseEnvCameraComponent::SetAspectRatio);
		def.def("SetNearZ",&pragma::BaseEnvCameraComponent::SetNearZ);
		def.def("SetFarZ",&pragma::BaseEnvCameraComponent::SetFarZ);
		def.def("GetFOV",&pragma::BaseEnvCameraComponent::GetFOV);
		def.def("GetFOVRad",&pragma::BaseEnvCameraComponent::GetFOVRad);
		def.def("GetAspectRatio",&pragma::BaseEnvCameraComponent::GetAspectRatio);
		def.def("GetNearZ",&pragma::BaseEnvCameraComponent::GetNearZ);
		def.def("GetFarZ",&pragma::BaseEnvCameraComponent::GetFarZ);
		def.def("GetFrustumPlanes",static_cast<std::vector<umath::Plane>(*)(lua_State*,pragma::BaseEnvCameraComponent&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent) {
			std::vector<umath::Plane> planes;
			hComponent.GetFrustumPlanes(planes);
			return planes;
		}),luabind::vector_policy<0,Vector3>{});
		def.def("GetFarPlaneCenter",&pragma::BaseEnvCameraComponent::GetFarPlaneCenter);
		def.def("GetNearPlaneCenter",&pragma::BaseEnvCameraComponent::GetNearPlaneCenter);
		def.def("GetPlaneCenter",&pragma::BaseEnvCameraComponent::GetPlaneCenter);
		def.def("GetFarPlaneBoundaries",static_cast<std::array<Vector3,4>(*)(lua_State*,pragma::BaseEnvCameraComponent&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent) -> std::array<Vector3,4> {
			std::array<Vector3,4> farBounds;
			hComponent.GetFarPlaneBoundaries(farBounds);
			return farBounds;
		}),luabind::array_policy<0,Vector3,4>{});
		def.def("GetNearPlaneBoundaries",static_cast<std::array<Vector3,4>(*)(lua_State*,pragma::BaseEnvCameraComponent&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent) {
			std::array<Vector3,4> nearBounds;
			hComponent.GetNearPlaneBoundaries(nearBounds);
			return nearBounds;
		}),luabind::array_policy<0,Vector3,4>{});
		def.def("GetPlaneBoundaries",static_cast<std::array<Vector3,4>(*)(lua_State*,pragma::BaseEnvCameraComponent&,float)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,float z) {
			std::array<Vector3,4> bounds;
			hComponent.GetPlaneBoundaries(z,bounds);
			return bounds;
		}),luabind::array_policy<0,Vector3,4>{});
		def.def("GetPlaneBoundaries",static_cast<Lua::mult<luabind::tableT<Vector3>,luabind::tableT<Vector3>>(*)(lua_State*,pragma::BaseEnvCameraComponent&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent) -> Lua::mult<luabind::tableT<Vector3>,luabind::tableT<Vector3>> {
			std::array<Vector3,8> bounds;
			hComponent.GetPlaneBoundaries(bounds);

			auto t0 = luabind::newtable(l);
			for(unsigned int i=0;i<4;i++)
				t0[i +1] = bounds[i];

			auto t1 = luabind::newtable(l);
			for(unsigned int i=4;i<8;i++)
				t1[i +1] = bounds[i];
			return {l,t0,t1};
		}));
		def.def("SetProjectionMatrix",&pragma::BaseEnvCameraComponent::SetProjectionMatrix);
		def.def("SetViewMatrix",&pragma::BaseEnvCameraComponent::SetViewMatrix);
		def.def("GetNearPlaneBounds",&pragma::BaseEnvCameraComponent::GetNearPlaneBounds,luabind::meta::join<luabind::out_value<2>,luabind::out_value<3>>::type{});
		def.def("GetFarPlaneBounds",&pragma::BaseEnvCameraComponent::GetFarPlaneBounds,luabind::meta::join<luabind::out_value<2>,luabind::out_value<3>>::type{});
		def.def("GetFarPlaneBounds",&pragma::BaseEnvCameraComponent::GetPlaneBounds,luabind::meta::join<luabind::out_value<3>,luabind::out_value<4>>::type{});
		def.def("GetFrustumPoints",static_cast<void(pragma::BaseEnvCameraComponent::*)(std::vector<Vector3>&) const>(&pragma::BaseEnvCameraComponent::GetFrustumPoints),luabind::out_value<2,luabind::vector_policy<1,Vector3>>{});
		def.def("GetNearPlanePoint",&pragma::BaseEnvCameraComponent::GetNearPlanePoint);
		def.def("GetFarPlanePoint",&pragma::BaseEnvCameraComponent::GetFarPlanePoint);
		def.def("GetPlanePoint",&pragma::BaseEnvCameraComponent::GetPlanePoint);
		def.def("GetFrustumNeighbors",static_cast<void(*)(lua_State*,pragma::BaseEnvCameraComponent&,int)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,int planeID) {
			if(planeID < 0 || planeID > 5)
				return;
			FrustumPlane neighborIDs[4];
			hComponent.GetFrustumNeighbors(FrustumPlane(planeID),&neighborIDs[0]);
			int table = Lua::CreateTable(l);
			for(unsigned int i=0;i<4;i++)
			{
				Lua::PushInt(l,i +1);
				Lua::PushInt(l,static_cast<int>(neighborIDs[i]));
				Lua::SetTableValue(l,table);
			}
		}));
		def.def("GetFrustumPlaneCornerPoints",static_cast<void(*)(lua_State*,pragma::BaseEnvCameraComponent&,int,int)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,int planeA,int planeB) {
			if(planeA < 0 || planeB < 0 || planeA > 5 || planeB > 5)
				return;

			FrustumPoint cornerPoints[2];
			hComponent.GetFrustumPlaneCornerPoints(FrustumPlane(planeA),FrustumPlane(planeB),&cornerPoints[0]);

			Lua::PushInt(l,static_cast<int>(cornerPoints[0]));
			Lua::PushInt(l,static_cast<int>(cornerPoints[1]));
		}));
		def.def("CreateFrustumKDop",static_cast<void(pragma::BaseEnvCameraComponent::*)(const Vector2&,const Vector2&,std::vector<umath::Plane>&) const>(&pragma::BaseEnvCameraComponent::CreateFrustumKDop),luabind::out_value<4,luabind::vector_policy<1,umath::Plane>>{});
		def.def("CreateFrustumMesh",static_cast<void(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector2&,const Vector2&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector2 &uvStart,const Vector2 &uvEnd) {
			std::vector<Vector3> verts;
			std::vector<uint16_t> indices;
			hComponent.CreateFrustumMesh(uvStart,uvEnd,verts,indices);
			auto t = Lua::CreateTable(l);
			auto vertIdx = 1u;
			for(auto &v : verts)
			{
				Lua::PushInt(l,vertIdx++);
				Lua::Push<Vector3>(l,v);
				Lua::SetTableValue(l,t);
			}

			t = Lua::CreateTable(l);
			auto idx = 1u;
			for(auto i : indices)
			{
				Lua::PushInt(l,idx++);
				Lua::PushInt(l,i);
				Lua::SetTableValue(l,t);
			}
		}));
		def.def("ScreenSpaceToWorldSpace",static_cast<Vector3(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector2&,float,float)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector2 &uv,float width,float height) -> Vector3 {
			auto &ent = hComponent.GetEntity();
			return uvec::calc_world_direction_from_2d_coordinates(ent.GetForward(),ent.GetRight(),ent.GetUp(),hComponent.GetFOVRad(),hComponent.GetNearZ(),hComponent.GetFarZ(),hComponent.GetAspectRatio(),width,height,uv);
		}));
		def.def("WorldSpaceToScreenSpace",static_cast<std::pair<Vector2,float>(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector3&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector3 &point) -> std::pair<Vector2,float> {
			float dist;
			auto uv = uvec::calc_screenspace_uv_from_worldspace_position(point,hComponent.GetProjectionMatrix() *hComponent.GetViewMatrix(),hComponent.GetNearZ(),hComponent.GetFarZ(),dist);
			return {uv,dist};
			}),luabind::pair_policy<0>{});
		def.def("WorldSpaceToScreenSpaceDirection",static_cast<Vector2(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector3&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector3 &dir) -> Vector2 {
			return uvec::calc_screenspace_direction_from_worldspace_direction(dir,hComponent.GetProjectionMatrix() *hComponent.GetViewMatrix());
		}));
		def.def("CalcScreenSpaceDistance",static_cast<float(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector3&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector3 &point) -> float {
			return uvec::calc_screenspace_distance_to_worldspace_position(point,hComponent.GetProjectionMatrix() *hComponent.GetViewMatrix(),hComponent.GetNearZ(),hComponent.GetFarZ());
		}));
		def.def("DepthToDistance",static_cast<float(*)(lua_State*,pragma::BaseEnvCameraComponent&,double,float,float)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,double depth,float nearZ,float farZ) -> float {
			return uvec::depth_to_distance(depth,nearZ,farZ);
		}));
		def.def("CalcRayDirection",static_cast<Vector3(*)(lua_State*,pragma::BaseEnvCameraComponent&,const Vector2&)>([](lua_State *l,pragma::BaseEnvCameraComponent &hComponent,const Vector2 &uv) -> Vector3 {
			auto &ent = hComponent.GetEntity();
			return uvec::calc_world_direction_from_2d_coordinates(ent.GetForward(),ent.GetRight(),ent.GetUp(),hComponent.GetFOVRad(),hComponent.GetNearZ(),hComponent.GetFarZ(),hComponent.GetAspectRatio(),0.f,0.f,uv);
		}));
	}

	#include "pragma/entities/environment/effects/env_explosion.h"
	void pragma::lua::base_env_explosion_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvExplosionComponent> def {"BaseEnvExplosionComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/effects/env_fire.h"
	void pragma::lua::base_env_fire_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvFireComponent> def {"BaseEnvFireComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_fog_controller.h"
	void pragma::lua::base_env_fog_controller_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvFogControllerComponent> def {"BaseEnvFogControllerComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/lights/env_light_spot_vol.h"
	void pragma::lua::base_env_light_spot_vol_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvLightSpotVolComponent> def {"BaseEnvLightSpotVolComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_microphone_base.h"
	void pragma::lua::base_env_microphone_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvMicrophoneComponent> def {"BaseEnvMicrophoneComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_quake.h"
	void pragma::lua::base_env_quake_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvQuakeComponent> def {"BaseEnvQuakeComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/effects/env_smoke_trail.h"
	void pragma::lua::base_env_smoke_trail_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvSmokeTrailComponent> def {"BaseEnvSmokeTrailComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/audio/env_sound.h"
	void pragma::lua::base_env_sound_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvSoundComponent> def {"BaseEnvSoundComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetSoundSource",&pragma::BaseEnvSoundComponent::SetSoundSource);
		def.def("SetPitch",&pragma::BaseEnvSoundComponent::SetPitch);
		def.def("SetGain",&pragma::BaseEnvSoundComponent::SetGain);
		def.def("SetRolloffFactor",&pragma::BaseEnvSoundComponent::SetRolloffFactor);
		def.def("SetMinGain",&pragma::BaseEnvSoundComponent::SetMinGain);
		def.def("SetMaxGain",&pragma::BaseEnvSoundComponent::SetMaxGain);
		def.def("SetInnerConeAngle",&pragma::BaseEnvSoundComponent::SetInnerConeAngle);
		def.def("SetOuterConeAngle",&pragma::BaseEnvSoundComponent::SetOuterConeAngle);
		def.def("SetOffset",&pragma::BaseEnvSoundComponent::SetOffset);
		def.def("GetOffset",&pragma::BaseEnvSoundComponent::GetOffset);
		def.def("SetTimeOffset",&pragma::BaseEnvSoundComponent::SetTimeOffset);
		def.def("GetTimeOffset",&pragma::BaseEnvSoundComponent::GetTimeOffset);
		def.def("SetReferenceDistance",&pragma::BaseEnvSoundComponent::SetReferenceDistance);
		def.def("SetMaxDistance",&pragma::BaseEnvSoundComponent::SetMaxDistance);
		def.def("SetRelativeToListener",&pragma::BaseEnvSoundComponent::SetRelativeToListener);
		def.def("SetPlayOnSpawn",&pragma::BaseEnvSoundComponent::SetPlayOnSpawn);
		def.def("SetLooping",&pragma::BaseEnvSoundComponent::SetLooping);
		def.def("SetSoundTypes",&pragma::BaseEnvSoundComponent::SetSoundType);
		def.def("Play",&pragma::BaseEnvSoundComponent::Play);
		def.def("Stop",&pragma::BaseEnvSoundComponent::Stop);
		def.def("Pause",&pragma::BaseEnvSoundComponent::Pause);
		def.def("GetSound",&pragma::BaseEnvSoundComponent::GetSound);
		def.def("IsPlaying",&pragma::BaseEnvSoundComponent::IsPlaying);
		def.def("IsPaused",&pragma::BaseEnvSoundComponent::IsPaused);
	}

	#include "pragma/entities/environment/audio/env_soundscape.h"
	void pragma::lua::base_env_soundscape_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvSoundScapeComponent> def {"BaseEnvSoundScapeComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/effects/env_sprite.h"
	void pragma::lua::base_env_sprite_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvSpriteComponent> def {"BaseEnvSpriteComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_timescale.h"
	void pragma::lua::base_env_timescale_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvTimescaleComponent> def {"BaseEnvTimescaleComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_weather.h"
	void pragma::lua::base_env_weather_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvWeatherComponent> def {"BaseEnvWeatherComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/environment/env_wind.hpp"
	void pragma::lua::base_env_wind_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEnvWindComponent> def {"BaseEnvWindComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/basefilterentity.h"
	void pragma::lua::base_env_filter_name_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFilterNameComponent> def {"BaseFilterNameComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("ShouldPass",&pragma::BaseFilterNameComponent::ShouldPass);
		def.add_static_constant("EVENT_ON_NAME_CHANGED",pragma::BaseNameComponent::EVENT_ON_NAME_CHANGED);
	}

	void pragma::lua::base_env_filter_class_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFilterClassComponent> def {"BaseFilterClassComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("ShouldPass",&pragma::BaseFilterClassComponent::ShouldPass);
	}

	#include "pragma/entities/func/basefuncbrush.h"
	void pragma::lua::base_func_brush_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncBrushComponent> def {"BaseFuncBrushComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/func/basefuncbutton.h"
	void pragma::lua::base_func_button_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncButtonComponent> def {"BaseFuncButtonComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/func/basefunckinematic.hpp"
	void pragma::lua::base_func_kinematic_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncKinematicComponent> def {"BaseFuncKinematicComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/func/basefuncphysics.h"
	void pragma::lua::base_func_physics_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncPhysicsComponent> def {"BaseFuncPhysicsComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/func/basefuncportal.h"
	void pragma::lua::base_func_portal_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncPortalComponent> def {"BaseFuncPortalComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/func/basefuncsoftphysics.hpp"
	void pragma::lua::base_func_soft_physics_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncSoftPhysicsComponent> def {"BaseFuncSoftPhysicsComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/func/basefuncsurfacematerial.hpp"
	void pragma::lua::base_func_surface_material_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFuncSurfaceMaterialComponent> def {"BaseFuncSurfaceMaterialComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/logic/logic_relay.h"
	void pragma::lua::base_logic_relay_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseLogicRelayComponent> def {"BaseLogicRelayComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/basebot.h"
	void pragma::lua::base_bot_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseBotComponent> def {"BaseBotComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/components/basepointpathnode.h"
	void pragma::lua::base_point_path_node_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointPathNodeComponent> def {"BasePointPathNodeComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/constraints/point_constraint_ballsocket.h"
	void pragma::lua::base_point_constraint_ball_socket_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointConstraintBallSocketComponent> def {"BasePointConstraintBallSocketComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/constraints/point_constraint_conetwist.h"
	void pragma::lua::base_point_constraint_cone_twist_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointConstraintConeTwistComponent> def {"BasePointConstraintConeTwistComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/constraints/point_constraint_dof.h"
	void pragma::lua::base_point_constraint_dof_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointConstraintDoFComponent> def {"BasePointConstraintDoFComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/constraints/point_constraint_fixed.h"
	void pragma::lua::base_point_constraint_fixed_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointConstraintFixedComponent> def {"BasePointConstraintFixedComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/constraints/point_constraint_hinge.h"
	void pragma::lua::base_point_constraint_hinge_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointConstraintHingeComponent> def {"BasePointConstraintHingeComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/constraints/point_constraint_slider.h"
	void pragma::lua::base_point_constraint_slider_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointConstraintSliderComponent> def {"BasePointConstraintSliderComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/point_rendertarget.h"
	void pragma::lua::base_point_render_target_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointRenderTargetComponent> def {"BasePointRenderTargetComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/point/point_target.h"
	void pragma::lua::base_point_target_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointTargetComponent> def {"BasePointTargetComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/prop/prop_base.h"
	void pragma::lua::base_prop_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePropComponent> def {"BasePropComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/prop/prop_dynamic.hpp"
	void pragma::lua::base_prop_dynamic_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePropDynamicComponent> def {"BasePropDynamicComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/prop/prop_physics.hpp"
	void pragma::lua::base_prop_physics_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePropPhysicsComponent> def {"BasePropPhysicsComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/trigger/base_trigger_hurt.hpp"
	void pragma::lua::base_trigger_hurt_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTriggerHurtComponent> def {"BaseTriggerHurtComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/trigger/base_trigger_push.hpp"
	void pragma::lua::base_trigger_push_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTriggerPushComponent> def {"BaseTriggerPushComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/trigger/base_trigger_remove.h"
	void pragma::lua::base_trigger_remove_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTriggerRemoveComponent> def {"BaseTriggerRemoveComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/trigger/base_trigger_teleport.hpp"
	void pragma::lua::base_trigger_teleport_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTriggerTeleportComponent> def {"BaseTriggerTeleportComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/trigger/base_trigger_touch.hpp"
	void pragma::lua::base_touch_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTouchComponent> def {"BaseTouchComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetTriggerFlags",&pragma::BaseTouchComponent::SetTriggerFlags);
		def.def("GetTriggerFlags",&pragma::BaseTouchComponent::GetTriggerFlags);
		def.def("GetTouchingEntities",static_cast<luabind::object(*)(lua_State*,pragma::BaseTouchComponent&)>([](lua_State *l,pragma::BaseTouchComponent &hComponent) -> luabind::object {
			auto t = luabind::newtable(l);
			int32_t idx = 1;
			for(auto &touchInfo : hComponent.GetTouchingInfo())
			{
				if(touchInfo.touch.entity.valid() == false || touchInfo.triggered == false)
					continue;
				t[idx++] = touchInfo.touch.entity.get()->GetLuaObject();
			}
			return t;
		}));
		def.def("GetTouchingEntityCount",static_cast<uint32_t(*)(lua_State*,pragma::BaseTouchComponent&)>([](lua_State *l,pragma::BaseTouchComponent &hComponent) -> uint32_t {
			auto &touchingInfo = hComponent.GetTouchingInfo();
			return std::count_if(touchingInfo.begin(),touchingInfo.end(),[](const pragma::BaseTouchComponent::TouchInfo &touchInfo) -> bool {
				return touchInfo.triggered && touchInfo.touch.entity.valid();
			});
		}));

		def.add_static_constant("EVENT_CAN_TRIGGER",pragma::BaseTouchComponent::EVENT_CAN_TRIGGER);
		def.add_static_constant("EVENT_ON_START_TOUCH",pragma::BaseTouchComponent::EVENT_ON_START_TOUCH);
		def.add_static_constant("EVENT_ON_END_TOUCH",pragma::BaseTouchComponent::EVENT_ON_END_TOUCH);
		def.add_static_constant("EVENT_ON_TRIGGER",pragma::BaseTouchComponent::EVENT_ON_TRIGGER);
		def.add_static_constant("EVENT_ON_TRIGGER_INITIALIZED",pragma::BaseTouchComponent::EVENT_ON_TRIGGER_INITIALIZED);
		
		def.add_static_constant("TRIGGER_FLAG_NONE",umath::to_integral(pragma::BaseTouchComponent::TriggerFlags::None));
		def.add_static_constant("TRIGGER_FLAG_BIT_PLAYERS",umath::to_integral(pragma::BaseTouchComponent::TriggerFlags::Players));
		def.add_static_constant("TRIGGER_FLAG_BIT_NPCS",umath::to_integral(pragma::BaseTouchComponent::TriggerFlags::NPCs));
		def.add_static_constant("TRIGGER_FLAG_BIT_PHYSICS",umath::to_integral(pragma::BaseTouchComponent::TriggerFlags::Physics));
		def.add_static_constant("TRIGGER_FLAG_EVERYTHING",umath::to_integral(pragma::BaseTouchComponent::TriggerFlags::Everything));
	}

	#include "pragma/entities/components/basetriggergravity.hpp"
	void pragma::lua::base_trigger_gravity_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseEntityTriggerGravityComponent> def {"BaseEntityTriggerGravityComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/baseflashlight.h"
	void pragma::lua::base_flashlight_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFlashlightComponent> def {"BaseFlashlightComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/components/base_flex_component.hpp"
	void pragma::lua::base_flex_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseFlexComponent> def {"BaseFlexComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/baseskybox.h"
	void pragma::lua::base_skybox_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseSkyboxComponent> def {"BaseSkyboxComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetSkyAngles",&pragma::BaseSkyboxComponent::SetSkyAngles);
		def.def("GetSkyAngles",&pragma::BaseSkyboxComponent::GetSkyAngles);
	}

	#include "pragma/entities/baseworld.h"
	void pragma::lua::base_world_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseWorldComponent> def {"BaseWorldComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/components/base_ai_component.hpp"
	namespace Lua::AI
	{
		void GetMoveSpeed(lua_State *l,pragma::BaseAIComponent &hNPC,uint32_t animId)
		{
			Lua::PushNumber(l,hNPC.GetMoveSpeed(animId));
		}
		
		void SetLookTarget(lua_State *l,pragma::BaseAIComponent &hNPC,const Vector3 &tgt,float t)
		{
			hNPC.SetLookTarget(tgt,t);
		}
		
		void SetLookTarget(lua_State *l,pragma::BaseAIComponent &hNPC,BaseEntity &ent,float t)
		{
			hNPC.SetLookTarget(ent,t);
		}
	};
	void pragma::lua::base_ai_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseAIComponent> def {"BaseAIComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetMoveSpeed",static_cast<void(pragma::BaseAIComponent::*)(int32_t,float)>(&pragma::BaseAIComponent::SetMoveSpeed));
		def.def("SetMoveSpeed",static_cast<void(pragma::BaseAIComponent::*)(const std::string&,float)>(&pragma::BaseAIComponent::SetMoveSpeed));
		def.def("GetMoveSpeed",static_cast<void(*)(lua_State*,pragma::BaseAIComponent&,const std::string&)>([](lua_State *l,pragma::BaseAIComponent &hNPC,const std::string &anim) {
			auto &mdl = hNPC.GetEntity().GetModel();
			if(mdl == nullptr)
				return;
			auto animId = mdl->LookupAnimation(anim);
			if(animId < 0)
				return;
			Lua::AI::GetMoveSpeed(l,hNPC,animId);
		}));
		def.def("GetMoveSpeed",static_cast<void(*)(lua_State*,pragma::BaseAIComponent&,uint32_t)>([](lua_State *l,pragma::BaseAIComponent &hNPC,uint32_t animId) {
			Lua::AI::GetMoveSpeed(l,hNPC,animId);
		}));
		def.def("ClearMoveSpeed",static_cast<void(pragma::BaseAIComponent::*)(int32_t)>(&pragma::BaseAIComponent::ClearMoveSpeed));
		def.def("ClearMoveSpeed",static_cast<void(pragma::BaseAIComponent::*)(const std::string&)>(&pragma::BaseAIComponent::ClearMoveSpeed));
		def.def("ClearLookTarget",&pragma::BaseAIComponent::ClearLookTarget);
		def.def("SetLookTarget",static_cast<void(*)(lua_State*,pragma::BaseAIComponent&,const Vector3&,float)>([](lua_State *l,pragma::BaseAIComponent &hNPC,const Vector3 &tgt,float t) {
			Lua::AI::SetLookTarget(l,hNPC,tgt,t);
		}));
		def.def("SetLookTarget",static_cast<void(*)(lua_State*,pragma::BaseAIComponent&,const Vector3&)>([](lua_State *l,pragma::BaseAIComponent &hNPC,const Vector3 &tgt) {
			Lua::AI::SetLookTarget(l,hNPC,tgt,std::numeric_limits<float>::max());
		}));
		def.def("SetLookTarget",static_cast<void(*)(lua_State*,pragma::BaseAIComponent&,BaseEntity&,float)>([](lua_State *l,pragma::BaseAIComponent &hNPC,BaseEntity &ent,float t) {
			Lua::AI::SetLookTarget(l,hNPC,ent,t);
		}));
		def.def("SetLookTarget",static_cast<void(*)(lua_State*,pragma::BaseAIComponent&,BaseEntity&)>([](lua_State *l,pragma::BaseAIComponent &hNPC,BaseEntity &ent) {
			Lua::AI::SetLookTarget(l,hNPC,ent,std::numeric_limits<float>::max());
		}));
		def.def("GetLookTarget",&pragma::BaseAIComponent::GetLookTarget);
	}

	#include "pragma/entities/components/base_character_component.hpp"
	#include "pragma/physics/raytraces.h"
		void pragma::lua::base_character_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseCharacterComponent> def {"BaseCharacterComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		// Actor
		def.def("GetFrozenProperty",&pragma::BaseCharacterComponent::GetFrozenProperty,luabind::property_policy<0>{});
		def.add_static_constant("EVENT_ON_KILLED",pragma::BaseActorComponent::EVENT_ON_KILLED);
		def.add_static_constant("EVENT_ON_RESPAWN",pragma::BaseActorComponent::EVENT_ON_RESPAWN);

		// Character
		def.def("IsAlive",&pragma::BaseCharacterComponent::IsAlive);
		def.def("IsDead",&pragma::BaseCharacterComponent::IsDead);
		def.def("IsFrozen",&pragma::BaseCharacterComponent::IsFrozen);
		def.def("SetFrozen",&pragma::BaseCharacterComponent::SetFrozen);
		def.def("Kill",&pragma::BaseCharacterComponent::Kill);
		def.def("GetOrientationAxes",static_cast<void(*)(lua_State*,pragma::BaseCharacterComponent&)>([](lua_State *l,pragma::BaseCharacterComponent &hEntity) {
			Vector3 *forward,*right,*up;
			hEntity.GetOrientationAxes(&forward,&right,&up);
			Lua::Push<Vector3>(l,*forward);
			Lua::Push<Vector3>(l,*right);
			Lua::Push<Vector3>(l,*up);
		}));
		def.def("GetOrientationAxesRotation",&pragma::BaseCharacterComponent::GetOrientationAxesRotation);
		def.def("GetShootPos",&pragma::BaseCharacterComponent::GetShootPosition);
		def.def("GetSlopeLimit",&pragma::BaseCharacterComponent::GetSlopeLimit);
		def.def("GetStepOffset",&pragma::BaseCharacterComponent::GetStepOffset);
		def.def("GetTurnSpeed",&pragma::BaseCharacterComponent::GetTurnSpeed);
		def.def("GetUpDirection",&pragma::BaseCharacterComponent::GetUpDirection);
		def.def("GetViewAngles",&pragma::BaseCharacterComponent::GetViewAngles);
		def.def("GetViewForward",&pragma::BaseCharacterComponent::GetViewForward);
		def.def("GetViewRotation",static_cast<const Quat&(pragma::BaseCharacterComponent::*)() const>(&pragma::BaseCharacterComponent::GetViewOrientation),luabind::copy_policy<0>{});
		def.def("GetViewRight",&pragma::BaseCharacterComponent::GetViewRight);
		def.def("GetViewUp",&pragma::BaseCharacterComponent::GetViewUp);
		def.def("Ragdolize",&pragma::BaseCharacterComponent::Ragdolize);
		def.def("SetSlopeLimit",static_cast<void(*)(lua_State*,pragma::BaseCharacterComponent&,float)>([](lua_State *l,pragma::BaseCharacterComponent &hEntity,float slopeLimit) {
			hEntity.SetSlopeLimit(umath::deg_to_rad(slopeLimit));
		}));
		def.def("SetStepOffset",&pragma::BaseCharacterComponent::SetStepOffset);
		def.def("SetTurnSpeed",&pragma::BaseCharacterComponent::SetTurnSpeed);
		def.def("SetUpDirection",&pragma::BaseCharacterComponent::SetUpDirection);
		def.def("SetViewAngles",&pragma::BaseCharacterComponent::SetViewAngles);
		def.def("SetViewRotation",&pragma::BaseCharacterComponent::SetViewOrientation);
		def.def("NormalizeViewRotation",static_cast<void(pragma::BaseCharacterComponent::*)(Quat&)>(&pragma::BaseCharacterComponent::NormalizeViewOrientation));
		def.def("NormalizeViewRotation",static_cast<const Quat&(pragma::BaseCharacterComponent::*)()>(&pragma::BaseCharacterComponent::NormalizeViewOrientation),luabind::copy_policy<0>{});
		def.def("GetHitboxPhysicsObject",&pragma::BaseCharacterComponent::GetHitboxPhysicsObject,luabind::game_object_policy<0>{});
		def.def("GetWeapons",static_cast<void(*)(lua_State*,pragma::BaseCharacterComponent&)>([](lua_State *l,pragma::BaseCharacterComponent &hEnt) {
			auto &weapons = hEnt.GetWeapons();
			auto t = Lua::CreateTable(l);
			auto idx = 1;
			for(auto it=weapons.begin();it!=weapons.end();++it)
			{
				if(it->valid())
				{
					Lua::PushInt(l,idx++);
					(*it)->GetLuaObject().push(l);
					Lua::SetTableValue(l,t);
				}
			}
		}));
		def.def("GetWeapons",static_cast<void(*)(lua_State*,pragma::BaseCharacterComponent&,const std::string&)>([](lua_State *l,pragma::BaseCharacterComponent &hEnt,const std::string &className) {
			auto weapons = hEnt.GetWeapons(className);
			auto t = Lua::CreateTable(l);
			auto idx = 1;
			for(auto it=weapons.begin();it!=weapons.end();++it)
			{
				Lua::PushInt(l,idx++);
				(*it)->GetLuaObject().push(l);
				Lua::SetTableValue(l,t);
			}
		}));
		def.def("GetWeaponCount",static_cast<size_t(*)(lua_State*,pragma::BaseCharacterComponent&)>([](lua_State *l,pragma::BaseCharacterComponent &hEnt) -> size_t {
			return hEnt.GetWeapons().size();
		}));
		def.def("GetActiveWeapon",&pragma::BaseCharacterComponent::GetActiveWeapon,luabind::game_object_policy<0>{});
		def.def("HasWeapon",&pragma::BaseCharacterComponent::HasWeapon);
		def.def("GetAimRayData",static_cast<void(*)(lua_State*,pragma::BaseCharacterComponent&)>([](lua_State *l,pragma::BaseCharacterComponent &hEnt) {
			Lua::Push<::TraceData>(l,hEnt.GetAimTraceData());
		}));
		def.def("GetAimRayData",static_cast<void(*)(lua_State*,pragma::BaseCharacterComponent&,float)>([](lua_State *l,pragma::BaseCharacterComponent &hEnt,float maxDist) {
			Lua::Push<::TraceData>(l,hEnt.GetAimTraceData(maxDist));
		}));
		def.def("FootStep",&pragma::BaseCharacterComponent::FootStep);
		def.def("IsMoving",&pragma::BaseCharacterComponent::IsMoving);
		def.def("SetNeckControllers",&pragma::BaseCharacterComponent::SetNeckControllers);
		def.def("GetNeckYawController",&pragma::BaseCharacterComponent::GetNeckYawBlendController);
		def.def("GetNeckPitchController",&pragma::BaseCharacterComponent::GetNeckPitchBlendController);
		def.def("SetMoveController",static_cast<void(pragma::BaseCharacterComponent::*)(const std::string&)>(&pragma::BaseCharacterComponent::SetMoveController));
		def.def("SetMoveController",static_cast<void(pragma::BaseCharacterComponent::*)(const std::string&,const std::string&)>(&pragma::BaseCharacterComponent::SetMoveController));
		def.def("GetMoveController",static_cast<luabind::mult<int32_t,int32_t>(*)(lua_State*,pragma::BaseCharacterComponent&)>([](lua_State *l,pragma::BaseCharacterComponent &hEnt) -> luabind::mult<int32_t,int32_t> {
			return {l,hEnt.GetMoveController(),hEnt.GetMoveControllerY()};
		}));
		def.def("GetMoveVelocity",&pragma::BaseCharacterComponent::GetMoveVelocity);
		def.def("GetRelativeVelocity",&pragma::BaseCharacterComponent::GetLocalVelocity);

		def.def("SetOrientation",&pragma::BaseCharacterComponent::SetCharacterOrientation);
		def.def("GetLocalOrientationAngles",&pragma::BaseCharacterComponent::GetLocalOrientationAngles);
		def.def("GetLocalOrientationRotation",&pragma::BaseCharacterComponent::GetLocalOrientationRotation);
		def.def("GetLocalOrientationViewAngles",&pragma::BaseCharacterComponent::GetLocalOrientationViewAngles);
		def.def("GetLocalOrientationViewRotation",&pragma::BaseCharacterComponent::GetLocalOrientationViewRotation);
		
		def.def("WorldToLocalOrientation",static_cast<Quat(pragma::BaseCharacterComponent::*)(const Quat&)>(&pragma::BaseCharacterComponent::WorldToLocalOrientation));
		def.def("WorldToLocalOrientation",static_cast<EulerAngles(pragma::BaseCharacterComponent::*)(const EulerAngles&)>(&pragma::BaseCharacterComponent::WorldToLocalOrientation));
		def.def("LocalOrientationToWorld",static_cast<Quat(pragma::BaseCharacterComponent::*)(const Quat&)>(&pragma::BaseCharacterComponent::LocalOrientationToWorld));
		def.def("LocalOrientationToWorld",static_cast<EulerAngles(pragma::BaseCharacterComponent::*)(const EulerAngles&)>(&pragma::BaseCharacterComponent::LocalOrientationToWorld));

		def.def("GetAmmoCount",static_cast<uint16_t(pragma::BaseCharacterComponent::*)(const std::string&) const>(&pragma::BaseCharacterComponent::GetAmmoCount));
		def.def("GetAmmoCount",static_cast<uint16_t(pragma::BaseCharacterComponent::*)(uint32_t) const>(&pragma::BaseCharacterComponent::GetAmmoCount));
		def.def("SetAmmoCount",static_cast<void(pragma::BaseCharacterComponent::*)(const std::string&,uint16_t)>(&pragma::BaseCharacterComponent::SetAmmoCount));
		def.def("SetAmmoCount",static_cast<void(pragma::BaseCharacterComponent::*)(uint32_t,uint16_t)>(&pragma::BaseCharacterComponent::SetAmmoCount));

		def.def("AddAmmo",static_cast<void(pragma::BaseCharacterComponent::*)(const std::string&,int16_t)>(&pragma::BaseCharacterComponent::AddAmmo));
		def.def("AddAmmo",static_cast<void(pragma::BaseCharacterComponent::*)(uint32_t,int16_t)>(&pragma::BaseCharacterComponent::AddAmmo));
		def.def("RemoveAmmo",static_cast<void(pragma::BaseCharacterComponent::*)(const std::string&,int16_t)>(&pragma::BaseCharacterComponent::RemoveAmmo));
		def.def("RemoveAmmo",static_cast<void(pragma::BaseCharacterComponent::*)(uint32_t,int16_t)>(&pragma::BaseCharacterComponent::RemoveAmmo));
		def.def("GetUpDirectionProperty",&pragma::BaseCharacterComponent::GetUpDirectionProperty,luabind::property_policy<0>{});
		def.def("GetSlopeLimitProperty",&pragma::BaseCharacterComponent::GetSlopeLimitProperty,luabind::property_policy<0>{});
		def.def("GetStepOffsetProperty",&pragma::BaseCharacterComponent::GetStepOffsetProperty,luabind::property_policy<0>{});
		def.def("GetJumpPower",&pragma::BaseCharacterComponent::GetJumpPower);
		def.def("SetJumpPower",&pragma::BaseCharacterComponent::SetJumpPower);
		def.def("Jump",static_cast<bool(pragma::BaseCharacterComponent::*)()>(&pragma::BaseCharacterComponent::Jump));
		def.def("Jump",static_cast<bool(pragma::BaseCharacterComponent::*)(const Vector3&)>(&pragma::BaseCharacterComponent::Jump));
		def.def("GetJumpPowerProperty",&pragma::BaseCharacterComponent::GetJumpPowerProperty,luabind::property_policy<0>{});

		def.add_static_constant("EVENT_ON_FOOT_STEP",pragma::BaseCharacterComponent::EVENT_ON_FOOT_STEP);
		def.add_static_constant("EVENT_ON_CHARACTER_ORIENTATION_CHANGED",pragma::BaseCharacterComponent::EVENT_ON_CHARACTER_ORIENTATION_CHANGED);
		def.add_static_constant("EVENT_ON_DEPLOY_WEAPON",pragma::BaseCharacterComponent::EVENT_ON_DEPLOY_WEAPON);
		def.add_static_constant("EVENT_ON_SET_ACTIVE_WEAPON",pragma::BaseCharacterComponent::EVENT_ON_SET_ACTIVE_WEAPON);
		def.add_static_constant("EVENT_PLAY_FOOTSTEP_SOUND",pragma::BaseCharacterComponent::EVENT_PLAY_FOOTSTEP_SOUND);
		def.add_static_constant("EVENT_ON_DEATH",pragma::BaseCharacterComponent::EVENT_ON_DEATH);
		def.add_static_constant("EVENT_CALC_MOVEMENT_SPEED",pragma::BaseCharacterComponent::EVENT_CALC_MOVEMENT_SPEED);
		def.add_static_constant("EVENT_CALC_AIR_MOVEMENT_MODIFIER",pragma::BaseCharacterComponent::EVENT_CALC_AIR_MOVEMENT_MODIFIER);
		def.add_static_constant("EVENT_CALC_MOVEMENT_ACCELERATION",pragma::BaseCharacterComponent::EVENT_CALC_MOVEMENT_ACCELERATION);
		def.add_static_constant("EVENT_CALC_MOVEMENT_DIRECTION",pragma::BaseCharacterComponent::EVENT_CALC_MOVEMENT_DIRECTION);
		def.add_static_constant("EVENT_IS_MOVING",pragma::BaseCharacterComponent::EVENT_IS_MOVING);
		def.add_static_constant("EVENT_HANDLE_VIEW_ROTATION",pragma::BaseCharacterComponent::EVENT_HANDLE_VIEW_ROTATION);
		def.add_static_constant("EVENT_ON_JUMP",pragma::BaseCharacterComponent::EVENT_ON_JUMP);

		def.add_static_constant("FOOT_LEFT",umath::to_integral(pragma::BaseCharacterComponent::FootType::Left));
		def.add_static_constant("FOOT_RIGHT",umath::to_integral(pragma::BaseCharacterComponent::FootType::Right));
	}

	#include "pragma/entities/components/base_vehicle_component.hpp"
	void pragma::lua::base_vehicle_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseVehicleComponent> def {"BaseVehicleComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetSpeedKmh",&pragma::BaseVehicleComponent::GetSpeedKmh);
		def.def("GetSteeringFactor",&pragma::BaseVehicleComponent::GetSteeringFactor);
		def.def("GetSteeringWheel",&pragma::BaseVehicleComponent::GetSteeringWheel,luabind::game_object_policy<0>{});
		def.def("HasDriver",&pragma::BaseVehicleComponent::HasDriver);
		def.def("GetDriver",&pragma::BaseVehicleComponent::GetDriver,luabind::game_object_policy<0>{});
		def.def("SetDriver",&pragma::BaseVehicleComponent::SetDriver);
		def.def("ClearDriver",&pragma::BaseVehicleComponent::ClearDriver);
		def.def("SetupSteeringWheel",&pragma::BaseVehicleComponent::SetupSteeringWheel);
		def.def("GetPhysicsVehicle",static_cast<physics::IVehicle*(pragma::BaseVehicleComponent::*)()>(&pragma::BaseVehicleComponent::GetPhysicsVehicle),luabind::game_object_policy<0>{});
		def.def("SetupPhysics",&pragma::BaseVehicleComponent::SetupVehicle);
		def.add_static_constant("EVENT_ON_DRIVER_ENTERED",pragma::BaseVehicleComponent::EVENT_ON_DRIVER_ENTERED);
		def.add_static_constant("EVENT_ON_DRIVER_EXITED",pragma::BaseVehicleComponent::EVENT_ON_DRIVER_EXITED);
	}

	#include "pragma/entities/components/base_weapon_component.hpp"
	namespace Lua::Weapon
	{
		void PrimaryAttack(lua_State *l,pragma::BaseWeaponComponent &hEnt,bool bOnce)
		{
			auto &wep = hEnt;
			wep.PrimaryAttack();
			if(bOnce == true)
				wep.EndPrimaryAttack();
		}
		
		void SecondaryAttack(lua_State *l,pragma::BaseWeaponComponent &hEnt,bool bOnce)
		{
			auto &wep = hEnt;
			wep.SecondaryAttack();
			if(bOnce == true)
				wep.EndSecondaryAttack();
		}
	};
		void pragma::lua::base_weapon_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseWeaponComponent> def {"BaseWeaponComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetNextPrimaryAttack",&pragma::BaseWeaponComponent::SetNextPrimaryAttack);
		def.def("SetNextSecondaryAttack",&pragma::BaseWeaponComponent::SetNextSecondaryAttack);
		def.def("SetNextAttack",&pragma::BaseWeaponComponent::SetNextAttack);
		def.def("SetAutomaticPrimary",&pragma::BaseWeaponComponent::SetAutomaticPrimary);
		def.def("SetAutomaticSecondary",&pragma::BaseWeaponComponent::SetAutomaticSecondary);
		def.def("IsAutomaticPrimary",&pragma::BaseWeaponComponent::IsAutomaticPrimary);
		def.def("IsAutomaticSecondary",&pragma::BaseWeaponComponent::IsAutomaticSecondary);
		def.def("IsDeployed",&pragma::BaseWeaponComponent::IsDeployed);
		def.def("GetPrimaryAmmoType",&pragma::BaseWeaponComponent::GetPrimaryAmmoType);
		def.def("GetPrimaryAmmoTypeProperty",&pragma::BaseWeaponComponent::GetPrimaryAmmoTypeProperty,luabind::property_policy<0>{});
		def.def("GetSecondaryAmmoType",&pragma::BaseWeaponComponent::GetSecondaryAmmoType);
		def.def("GetSecondaryAmmoTypeProperty",&pragma::BaseWeaponComponent::GetSecondaryAmmoTypeProperty,luabind::property_policy<0>{});
		def.def("HasPrimaryAmmo",&pragma::BaseWeaponComponent::HasPrimaryAmmo);
		def.def("HasSecondaryAmmo",&pragma::BaseWeaponComponent::HasSecondaryAmmo);
		def.def("IsPrimaryClipEmpty",&pragma::BaseWeaponComponent::IsPrimaryClipEmpty);
		def.def("IsSecondaryClipEmpty",&pragma::BaseWeaponComponent::IsSecondaryClipEmpty);
		def.def("HasAmmo",&pragma::BaseWeaponComponent::HasAmmo);
		def.def("GetPrimaryClipSize",&pragma::BaseWeaponComponent::GetPrimaryClipSize);
		def.def("GetPrimaryClipSizeProperty",&pragma::BaseWeaponComponent::GetPrimaryClipSizeProperty,luabind::property_policy<0>{});
		def.def("GetSecondaryClipSize",&pragma::BaseWeaponComponent::GetSecondaryClipSize);
		def.def("GetSecondaryClipSizeProperty",&pragma::BaseWeaponComponent::GetSecondaryClipSizeProperty,luabind::property_policy<0>{});
		def.def("GetMaxPrimaryClipSize",&pragma::BaseWeaponComponent::GetMaxPrimaryClipSize);
		def.def("GetMaxPrimaryClipSizeProperty",&pragma::BaseWeaponComponent::GetMaxPrimaryClipSizeProperty,luabind::property_policy<0>{});
		def.def("GetMaxSecondaryClipSize",&pragma::BaseWeaponComponent::GetMaxSecondaryClipSize);
		def.def("GetMaxSecondaryClipSizeProperty",&pragma::BaseWeaponComponent::GetMaxSecondaryClipSizeProperty,luabind::property_policy<0>{});
		def.def("PrimaryAttack",static_cast<void(*)(lua_State*,pragma::BaseWeaponComponent&,bool)>([](lua_State *l,pragma::BaseWeaponComponent &hEnt,bool bOnce) {
			Lua::Weapon::PrimaryAttack(l,hEnt,bOnce);
		}));
		def.def("PrimaryAttack",static_cast<void(*)(lua_State*,pragma::BaseWeaponComponent&)>([](lua_State *l,pragma::BaseWeaponComponent &hEnt) {
			Lua::Weapon::PrimaryAttack(l,hEnt,false);
		}));
		def.def("SecondaryAttack",static_cast<void(*)(lua_State*,pragma::BaseWeaponComponent&,bool)>([](lua_State *l,pragma::BaseWeaponComponent &hEnt,bool bOnce) {
			Lua::Weapon::SecondaryAttack(l,hEnt,bOnce);
		}));
		def.def("SecondaryAttack",static_cast<void(*)(lua_State*,pragma::BaseWeaponComponent&)>([](lua_State *l,pragma::BaseWeaponComponent &hEnt) {
			Lua::Weapon::SecondaryAttack(l,hEnt,false);
		}));
		def.def("TertiaryAttack",&pragma::BaseWeaponComponent::TertiaryAttack);
		def.def("Attack4",&pragma::BaseWeaponComponent::Attack4);
		def.def("Reload",&pragma::BaseWeaponComponent::Reload);
		def.def("Deploy",&pragma::BaseWeaponComponent::Deploy);
		def.def("Holster",&pragma::BaseWeaponComponent::Holster);
		def.def("EndAttack",&pragma::BaseWeaponComponent::EndAttack);
		def.def("EndPrimaryAttack",&pragma::BaseWeaponComponent::EndPrimaryAttack);
		def.def("EndSecondaryAttack",&pragma::BaseWeaponComponent::EndSecondaryAttack);

		def.add_static_constant("EVENT_ON_DEPLOY",pragma::BaseWeaponComponent::EVENT_ON_DEPLOY);
		def.add_static_constant("EVENT_ON_HOLSTER",pragma::BaseWeaponComponent::EVENT_ON_HOLSTER);
		def.add_static_constant("EVENT_ON_PRIMARY_ATTACK",pragma::BaseWeaponComponent::EVENT_ON_PRIMARY_ATTACK);
		def.add_static_constant("EVENT_ON_SECONDARY_ATTACK",pragma::BaseWeaponComponent::EVENT_ON_SECONDARY_ATTACK);
		def.add_static_constant("EVENT_ON_TERTIARY_ATTACK",pragma::BaseWeaponComponent::EVENT_ON_TERTIARY_ATTACK);
		def.add_static_constant("EVENT_ON_ATTACK4",pragma::BaseWeaponComponent::EVENT_ON_ATTACK4);
		def.add_static_constant("EVENT_ON_END_PRIMARY_ATTACK",pragma::BaseWeaponComponent::EVENT_ON_END_PRIMARY_ATTACK);
		def.add_static_constant("EVENT_ON_END_SECONDARY_ATTACK",pragma::BaseWeaponComponent::EVENT_ON_END_SECONDARY_ATTACK);
		def.add_static_constant("EVENT_ON_RELOAD",pragma::BaseWeaponComponent::EVENT_ON_RELOAD);
		def.add_static_constant("EVENT_ON_PRIMARY_CLIP_SIZE_CHANGED",pragma::BaseWeaponComponent::EVENT_ON_PRIMARY_CLIP_SIZE_CHANGED);
		def.add_static_constant("EVENT_ON_SECONDARY_CLIP_SIZE_CHANGED",pragma::BaseWeaponComponent::EVENT_ON_SECONDARY_CLIP_SIZE_CHANGED);
	}

	#include "pragma/entities/components/base_player_component.hpp"
		void pragma::lua::base_player_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePlayerComponent> def {"BasePlayerComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetTimeConnected",&pragma::BasePlayerComponent::TimeConnected);
		def.def("IsKeyDown",&pragma::BasePlayerComponent::IsKeyDown);
		def.def("GetWalkSpeed",&pragma::BasePlayerComponent::GetWalkSpeed);
		def.def("GetRunSpeed",&pragma::BasePlayerComponent::GetRunSpeed);
		def.def("GetSprintSpeed",&pragma::BasePlayerComponent::GetSprintSpeed);
		def.def("SetWalkSpeed",&pragma::BasePlayerComponent::SetWalkSpeed);
		def.def("SetRunSpeed",&pragma::BasePlayerComponent::SetRunSpeed);
		def.def("SetSprintSpeed",&pragma::BasePlayerComponent::SetSprintSpeed);
		def.def("GetCrouchedWalkSpeed",&pragma::BasePlayerComponent::GetCrouchedWalkSpeed);
		def.def("SetCrouchedWalkSpeed",&pragma::BasePlayerComponent::SetCrouchedWalkSpeed);
		def.def("IsLocalPlayer",&pragma::BasePlayerComponent::IsLocalPlayer);
		def.def("GetStandHeight",&pragma::BasePlayerComponent::GetStandHeight);
		def.def("SetStandHeight",&pragma::BasePlayerComponent::SetStandHeight);
		def.def("GetCrouchHeight",&pragma::BasePlayerComponent::GetCrouchHeight);
		def.def("SetCrouchHeight",&pragma::BasePlayerComponent::SetCrouchHeight);
		def.def("GetStandEyeLevel",&pragma::BasePlayerComponent::GetStandEyeLevel);
		def.def("SetStandEyeLevel",&pragma::BasePlayerComponent::SetStandEyeLevel);
		def.def("GetCrouchEyeLevel",&pragma::BasePlayerComponent::GetCrouchEyeLevel);
		def.def("SetCrouchEyeLevel",&pragma::BasePlayerComponent::SetCrouchEyeLevel);
		def.def("SetObserverMode",&pragma::BasePlayerComponent::SetObserverMode);
		def.def("GetObserverMode",&pragma::BasePlayerComponent::GetObserverMode);
		def.def("GetObserverModeProperty",&pragma::BasePlayerComponent::GetObserverModeProperty,luabind::property_policy<0>{});
		def.def("SetObserverTarget",&pragma::BasePlayerComponent::SetObserverTarget);
		def.def("GetObserverTarget",&pragma::BasePlayerComponent::GetObserverTarget,luabind::game_object_policy<0>{});
		def.def("SetFlashlightEnabled",&pragma::BasePlayerComponent::SetFlashlight);
		def.def("ToggleFlashlight",&pragma::BasePlayerComponent::ToggleFlashlight);
		def.def("IsFlashlightEnabled",&pragma::BasePlayerComponent::IsFlashlightOn);
		def.def("GetViewPos",&pragma::BasePlayerComponent::GetViewPos);

		def.def("ApplyViewRotationOffset",&pragma::BasePlayerComponent::ApplyViewRotationOffset);
		def.def("ApplyViewRotationOffset",static_cast<void(*)(lua_State*,pragma::BasePlayerComponent&,EulerAngles&)>([](lua_State *l,pragma::BasePlayerComponent &hPl,EulerAngles &ang) {
			hPl.ApplyViewRotationOffset(ang);
		}));
		def.def("PrintMessage",&pragma::BasePlayerComponent::PrintMessage);
		def.def("GetActionInput",&pragma::BasePlayerComponent::GetActionInput);
		def.def("GetActionInputs",&pragma::BasePlayerComponent::GetActionInputs);
		def.def("GetActionInputAxisMagnitude",&pragma::BasePlayerComponent::GetActionInputAxisMagnitude);
		def.def("SetActionInputAxisMagnitude",&pragma::BasePlayerComponent::SetActionInputAxisMagnitude);

		def.add_static_constant("EVENT_HANDLE_ACTION_INPUT",pragma::BasePlayerComponent::EVENT_HANDLE_ACTION_INPUT);
		def.add_static_constant("EVENT_ON_OBSERVATION_MODE_CHANGED",pragma::BasePlayerComponent::EVENT_ON_OBSERVATION_MODE_CHANGED);

		def.add_static_constant("MESSAGE_TYPE_CONSOLE",umath::to_integral(MESSAGE::PRINTCONSOLE));
		def.add_static_constant("MESSAGE_TYPE_CHAT",umath::to_integral(MESSAGE::PRINTCHAT));

		// Enums
		def.add_static_constant("OBSERVERMODE_NONE",umath::to_integral(OBSERVERMODE::NONE));
		def.add_static_constant("OBSERVERMODE_FIRSTPERSON",umath::to_integral(OBSERVERMODE::FIRSTPERSON));
		def.add_static_constant("OBSERVERMODE_THIRDPERSON",umath::to_integral(OBSERVERMODE::THIRDPERSON));
		def.add_static_constant("OBSERVERMODE_SHOULDER",umath::to_integral(OBSERVERMODE::SHOULDER));
		def.add_static_constant("OBSERVERMODE_ROAMING",umath::to_integral(OBSERVERMODE::ROAMING));
	}

	#include "pragma/entities/components/base_gamemode_component.hpp"
	void pragma::lua::base_gamemode_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseGamemodeComponent> def {"BaseGamemodeComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetName",&pragma::BaseGamemodeComponent::GetName);
		def.def("GetIdentifier",&pragma::BaseGamemodeComponent::GetIdentifier);
		def.def("GetComponentName",&pragma::BaseGamemodeComponent::GetComponentName);
		def.def("GetAuthor",&pragma::BaseGamemodeComponent::GetAuthor);
		def.def("GetGamemodeVersion",&pragma::BaseGamemodeComponent::GetGamemodeVersion);

		// Enums
		def.add_static_constant("EVENT_ON_PLAYER_DEATH",pragma::BaseGamemodeComponent::EVENT_ON_PLAYER_DEATH);
		def.add_static_constant("EVENT_ON_PLAYER_SPAWNED",pragma::BaseGamemodeComponent::EVENT_ON_PLAYER_SPAWNED);
		def.add_static_constant("EVENT_ON_PLAYER_DROPPED",pragma::BaseGamemodeComponent::EVENT_ON_PLAYER_DROPPED);
		def.add_static_constant("EVENT_ON_PLAYER_READY",pragma::BaseGamemodeComponent::EVENT_ON_PLAYER_READY);
		def.add_static_constant("EVENT_ON_PLAYER_JOINED",pragma::BaseGamemodeComponent::EVENT_ON_PLAYER_JOINED);
		def.add_static_constant("EVENT_ON_GAME_INITIALIZED",pragma::BaseGamemodeComponent::EVENT_ON_GAME_INITIALIZED);
		def.add_static_constant("EVENT_ON_MAP_INITIALIZED",pragma::BaseGamemodeComponent::EVENT_ON_MAP_INITIALIZED);
		def.add_static_constant("EVENT_ON_GAME_READY",pragma::BaseGamemodeComponent::EVENT_ON_GAME_READY);
	}

	#include "pragma/entities/components/base_generic_component.hpp"
	void pragma::lua::base_generic_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseGenericComponent> def {"BaseGenericComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}
		
	#include "pragma/entities/info/info_landmark.hpp"
	void pragma::lua::base_info_landmark_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseInfoLandmarkComponent> def {"BaseInfoLandmarkComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/components/base_io_component.hpp"
	void pragma::lua::base_io_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseIOComponent> def {"BaseIOComponent"};
	util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("Input",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,std::string,BaseEntity&,BaseEntity&,std::string)>([](lua_State *l,pragma::BaseIOComponent &hIo,std::string input,BaseEntity &activator,BaseEntity &caller,std::string data) {
			
			hIo.Input(input,&activator,&caller,data);
		}));
		def.def("Input",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,std::string,BaseEntity&,std::string)>([](lua_State *l,pragma::BaseIOComponent &hIo,std::string input,BaseEntity &activator,std::string data) {
			
			hIo.Input(input,&activator,NULL,data);
		}));
		def.def("Input",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,std::string,std::string)>([](lua_State *l,pragma::BaseIOComponent &hIo,std::string input,std::string data) {
			
			hIo.Input(input,NULL,NULL,data);
		}));
		def.def("Input",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,std::string)>([](lua_State *l,pragma::BaseIOComponent &hIo,std::string input) {
			
			hIo.Input(input,NULL,NULL,"");
		}));
		def.def("StoreOutput",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,const std::string&,const std::string&,const std::string&,const std::string&,float,int32_t)>([](lua_State *l,pragma::BaseIOComponent &hIo,const std::string &name,const std::string &entities,const std::string &input,const std::string &param,float delay,int32_t times) {
			
			hIo.StoreOutput(name,entities,input,param,delay,times);
		}));
		def.def("StoreOutput",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,const std::string&,const std::string&,const std::string&,const std::string&,float)>([](lua_State *l,pragma::BaseIOComponent &hIo,const std::string &name,const std::string &entities,const std::string &input,const std::string &param,float delay) {
			
			hIo.StoreOutput(name,entities,input,param,delay);
		}));
		def.def("StoreOutput",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,const std::string&,const std::string&,const std::string&,const std::string&)>([](lua_State *l,pragma::BaseIOComponent &hIo,const std::string &name,const std::string &entities,const std::string &input,const std::string &param) {
			
			hIo.StoreOutput(name,entities,input,param);
		}));
		def.def("StoreOutput",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,const std::string&,const std::string&)>([](lua_State *l,pragma::BaseIOComponent &hIo,const std::string &name,const std::string &info) {
			
			hIo.StoreOutput(name,info);
		}));
		def.def("FireOutput",static_cast<void(*)(lua_State*,pragma::BaseIOComponent&,const std::string&,BaseEntity&)>([](lua_State *l,pragma::BaseIOComponent &hIo,const std::string &name,BaseEntity &ent) {
			
			hIo.TriggerOutput(name,&ent);
		}));
		def.def("FireOutput",&pragma::BaseIOComponent::TriggerOutput);
		def.add_static_constant("EVENT_HANDLE_INPUT",pragma::BaseIOComponent::EVENT_HANDLE_INPUT);
		
		def.add_static_constant("IO_FLAG_NONE",umath::to_integral(pragma::BaseIOComponent::IoFlags::None));
		def.add_static_constant("IO_FLAG_BIT_FORCE_DELAYED_FIRE",umath::to_integral(pragma::BaseIOComponent::IoFlags::ForceDelayedFire));
	}

	#include "pragma/entities/components/base_model_component.hpp"
	#include "pragma/lua/policies/vector_policy.hpp"
	void pragma::lua::base_model_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseModelComponent> def {"BaseModelComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetModel",static_cast<void(*)(lua_State*,pragma::BaseModelComponent&)>([](lua_State *l,pragma::BaseModelComponent &hModel) {
			hModel.SetModel(std::shared_ptr<Model>{nullptr});
		}));
		def.def("SetModel",static_cast<void(pragma::BaseModelComponent::*)(const std::string&)>(&pragma::BaseModelComponent::SetModel));
		def.def("SetModel",static_cast<void(pragma::BaseModelComponent::*)(const std::shared_ptr<Model>&)>(&pragma::BaseModelComponent::SetModel));
		def.def("SetSkin",&pragma::BaseModelComponent::SetSkin);
		def.def("GetSkin",&pragma::BaseModelComponent::GetSkin);
		def.def("GetSkinProperty",&pragma::BaseModelComponent::GetSkinProperty,luabind::property_policy<0>{});
		def.def("SetRandomSkin",static_cast<void(*)(lua_State*,pragma::BaseModelComponent&)>([](lua_State *l,pragma::BaseModelComponent &hModel) {
			auto &mdl = hModel.GetModel();
			if(mdl == nullptr)
				return;
			hModel.SetSkin(umath::random(0,umath::max(mdl->GetTextureGroups().size(),static_cast<size_t>(1)) -1));
		}));
		def.def("GetModel",static_cast<luabind::optional<::Model>(*)(lua_State*,pragma::BaseModelComponent&)>([](lua_State *l,pragma::BaseModelComponent &hModel) -> luabind::optional<::Model> {
			auto mdl = hModel.GetModel();
			if(mdl == nullptr)
				return Lua::nil;
			return luabind::object{l,mdl};
		}));
		def.def("GetBodyGroup",&pragma::BaseModelComponent::GetBodyGroup);
		def.def("GetBodyGroups",&pragma::BaseModelComponent::GetBodyGroups,luabind::vector_policy<0,uint32_t>{});
		def.def("SetBodyGroup",static_cast<bool(pragma::BaseModelComponent::*)(uint32_t,uint32_t)>(&pragma::BaseModelComponent::SetBodyGroup));
		def.def("SetBodyGroup",static_cast<void(pragma::BaseModelComponent::*)(const std::string&,uint32_t)>(&pragma::BaseModelComponent::SetBodyGroup));
		def.def("SetBodyGroups",static_cast<void(*)(lua_State*,pragma::BaseModelComponent&,luabind::table<>)>([](lua_State *l,pragma::BaseModelComponent &hModel,luabind::table<> t) {
			auto bodyGroups = Lua::table_to_vector<uint32_t>(l,t,2);
			for(auto i=decltype(bodyGroups.size()){0u};i<bodyGroups.size();++i)
				hModel.SetBodyGroup(i,bodyGroups[i]);
		}));
		def.def("LookupAnimation",&pragma::BaseModelComponent::LookupAnimation);

		def.def("GetModelName",&pragma::BaseModelComponent::GetModelName);
		def.def("LookupBlendController",&pragma::BaseModelComponent::LookupBlendController);
		def.def("LookupAttachment",&pragma::BaseModelComponent::LookupAttachment);
		def.def("GetHitboxCount",&pragma::BaseModelComponent::GetHitboxCount);
		def.def("GetHitboxBounds",static_cast<luabind::mult<Vector3,Vector3,Vector3,Quat>(*)(lua_State*,pragma::BaseModelComponent&,uint32_t)>([](lua_State *l,pragma::BaseModelComponent &hEnt,uint32_t boneId) -> luabind::mult<Vector3,Vector3,Vector3,Quat> {
			Vector3 min,max,origin;
			auto rot = uquat::identity();
			hEnt.GetHitboxBounds(boneId,min,max,origin,rot);
			return {l,min,max,origin,rot};
		}));
		def.def("LookupBone",&pragma::BaseModelComponent::LookupBone);
		def.def("GetAttachmentTransform",static_cast<luabind::optional<luabind::mult<Vector3,Quat>>(*)(lua_State*,pragma::BaseModelComponent&,std::string)>([](lua_State *l,pragma::BaseModelComponent &hEnt,std::string attachment) -> luabind::optional<luabind::mult<Vector3,Quat>> {
			Vector3 offset(0,0,0);
			auto rot = uquat::identity();
			if(hEnt.GetAttachment(attachment,&offset,&rot) == false)
				return Lua::nil;
			return luabind::mult<Vector3,Quat>{l,offset,rot};
		}));
		def.def("GetAttachmentTransform",static_cast<luabind::optional<luabind::mult<Vector3,Quat>>(*)(lua_State*,pragma::BaseModelComponent&,int)>([](lua_State *l,pragma::BaseModelComponent &hEnt,int attachment) -> luabind::optional<luabind::mult<Vector3,Quat>> {
			Vector3 offset(0,0,0);
			auto rot = uquat::identity();
			if(hEnt.GetAttachment(attachment,&offset,&rot) == false)
				return Lua::nil;
			return luabind::mult<Vector3,Quat>{l,offset,rot};
		}));

		def.add_static_constant("EVENT_ON_MODEL_CHANGED",pragma::BaseModelComponent::EVENT_ON_MODEL_CHANGED);
		def.add_static_constant("EVENT_ON_MODEL_MATERIALS_LOADED",pragma::BaseModelComponent::EVENT_ON_MODEL_MATERIALS_LOADED);
	}

	#include "pragma/entities/components/base_time_scale_component.hpp"
	void pragma::lua::base_time_scale_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseTimeScaleComponent> def {"BaseTimeScaleComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("GetTimeScale",&pragma::BaseTimeScaleComponent::GetTimeScale);
		def.def("SetTimeScale",&pragma::BaseTimeScaleComponent::GetTimeScale);
		def.def("GetEffectiveTimeScale",&pragma::BaseTimeScaleComponent::GetEffectiveTimeScale);
	}

	#include "pragma/entities/components/base_parent_component.hpp"
	void pragma::lua::base_parent_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseParentComponent> def {"BaseParentComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/components/base_ownable_component.hpp"
	void pragma::lua::base_ownable_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseOwnableComponent> def {"BaseOwnableComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetOwner",static_cast<void(*)(lua_State*,pragma::BaseOwnableComponent&,BaseEntity*)>([](lua_State *l,pragma::BaseOwnableComponent &hEnt,BaseEntity *owner) {
			auto &ownerComponent = hEnt;
			if(owner)
				ownerComponent.SetOwner(*owner);
			else
				ownerComponent.ClearOwner();
		}));
		def.def("SetOwner",&pragma::BaseOwnableComponent::ClearOwner);
		def.def("GetOwner",static_cast<BaseEntity*(pragma::BaseOwnableComponent::*)()>(&pragma::BaseOwnableComponent::GetOwner),luabind::game_object_policy<0>{});
		def.add_static_constant("EVENT_ON_OWNER_CHANGED",pragma::BaseOwnableComponent::EVENT_ON_OWNER_CHANGED);
	}

	#include "pragma/entities/components/base_debug_component.hpp"
	void pragma::lua::base_debug_text_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugTextComponent> def {"BaseDebugTextComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetText",&pragma::BaseDebugTextComponent::SetText);
	}

	void pragma::lua::base_debug_point_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugPointComponent> def {"BaseDebugPointComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	void pragma::lua::base_debug_line_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugLineComponent> def {"BaseDebugLineComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	void pragma::lua::base_debug_box_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugBoxComponent> def {"BaseDebugBoxComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	void pragma::lua::base_debug_sphere_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugSphereComponent> def {"BaseDebugSphereComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	void pragma::lua::base_debug_cone_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugConeComponent> def {"BaseDebugConeComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	void pragma::lua::base_debug_cylinder_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugCylinderComponent> def {"BaseDebugCylinderComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

		void pragma::lua::base_debug_plane_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BaseDebugPlaneComponent> def {"BaseDebugPlaneComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
	}

	#include "pragma/entities/components/base_point_at_target_component.hpp"
	void pragma::lua::base_point_at_target_component::register_class(luabind::module_ &mod)
	{
		Lua::ComponentClass<pragma::BasePointAtTargetComponent> def {"BasePointAtTargetComponent"};
		util::ScopeGuard sgReg {[&mod,&def]() {mod[def];}};
		def.def("SetPointAtTarget",static_cast<void(*)(lua_State*,pragma::BasePointAtTargetComponent&,BaseEntity*)>([](lua_State *l,pragma::BasePointAtTargetComponent &hEnt,BaseEntity *target) {
			if(target)
				hEnt.SetPointAtTarget(*target);
			else
				hEnt.ClearPointAtTarget();
		}));
		def.def("SetPointAtTarget",&pragma::BasePointAtTargetComponent::ClearPointAtTarget);
		def.def("GetPointAtTarget",&pragma::BasePointAtTargetComponent::GetPointAtTarget,luabind::game_object_policy<0>{});
	}
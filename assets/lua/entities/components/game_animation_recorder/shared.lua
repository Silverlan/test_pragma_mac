--[[
Copyright (C) 2021 Silverlan

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
]]

local Component = util.register_class("ents.GameAnimationRecorderComponent", BaseEntityComponent)

function Component:Initialize()
	BaseEntityComponent.Initialize(self)

	self.m_recordEntityList = {}
end

function Component:OnRemove()
	util.remove(self.m_cbThink)
end

function Component:RecordFrame(t)
	for name, animData in pairs(self.m_animations) do
		if animData.entity:IsValid() then
			self:RecordEntity(name, t, animData)
		end
	end
end

function Component:AddEntity(ent, properties)
	properties = properties or {
		["transform"] = { "position", "rotation" },
	}
	table.insert(self.m_recordEntityList, {
		entity = ent,
		properties = properties,
	})
	if self.m_recording == true then
		self:InitializeChannels(self.m_recordEntityList[#self.m_recordEntityList])
	end
end

function Component:EndRecording()
	if self.m_recording ~= true then
		return
	end
	self.m_recording = nil
	util.remove(self.m_cbThink)

	for name, animData in pairs(self.m_animations) do
		for componentName, channels in pairs(animData.channels) do
			for propName, channelInfo in pairs(channels) do
				channelInfo.channel:Resize(channelInfo.size) -- Clear reserved, unused space
			end
		end

		animData.animation:UpdateDuration()
	end
end

function Component:GetAnimation()
	return self.m_animation
end
function Component:IsRecording()
	return self.m_recording
end

function Component:RecordEntity(channelName, time, entityInfo)
	if self.m_animations[channelName] == nil then
		return
	end
	local animData = self.m_animations[channelName]

	for componentName, channels in pairs(entityInfo.channels) do
		for propName, channelInfo in pairs(channels) do
			if channelInfo.component:IsValid() then
				local value = channelInfo.component:GetMemberValue(channelInfo.memberIndex)
				if value ~= nil then
					if channelInfo.size == channelInfo.capacity then
						local newSize = channelInfo.size + 10000 -- Reserve some space
						channelInfo.channel:Resize(newSize)
						channelInfo.capacity = newSize
					end
					local i = channelInfo.size
					local addValue = true
					if i >= 2 then
						local v0 = channelInfo.channel:GetValue(i - 2)
						local v1 = channelInfo.channel:GetValue(i - 1)
						if value == v0 and value == v1 then
							-- Value hasn't changed, just update the time from the last entry
							channelInfo.channel:SetTime(i - 1, time)
							addValue = false
						end
					end
					if addValue then
						channelInfo.channel:SetTime(i, time)
						channelInfo.channel:SetValue(i, value)
						channelInfo.size = channelInfo.size + 1
					end
				end
			end
		end
	end
end

function Component:InitializeChannels(entityInfo)
	if entityInfo.entity:IsValid() == false then
		return
	end
	local anim = panima.Animation.create()
	local animData = {
		entity = entityInfo.entity,
		animation = anim,
		channels = {},
	}
	local channels = animData.channels

	for componentName, props in pairs(entityInfo.properties) do
		local c = entityInfo.entity:GetComponent(componentName)
		if c == nil then
			self:Log(
				"Unable to add animation channels for component '"
					.. componentName
					.. "' of entity "
					.. tostring(entityInfo.entity)
					.. ": Component does not exist!"
			)
		else
			for _, propName in ipairs(props) do
				local idx = c:GetMemberIndex(propName)
				if idx == nil then
					self:Log(
						"Unable to add animation channel for property '"
							.. propName
							.. "' of component '"
							.. componentName
							.. "' of entity "
							.. tostring(entityInfo.entity)
							.. ": Member does not exist!"
					)
				else
					local info = c:GetMemberInfo(idx)
					channels[componentName] = channels[componentName] or {}
					channels[componentName][propName] = {
						size = 0,
						capacity = 0,
						channel = anim:AddChannel("ec/" .. componentName .. "/" .. propName, info.type),
						component = c,
						memberIndex = idx,
					}
				end
			end
		end
	end

	self.m_animations[entityInfo.entity:GetUuid()] = animData
end

function Component:Save(fileName)
	fileName = file.remove_file_extension(fileName, { "pgma", "pgma_b" }) .. ".pgma_b"

	local udmData = udm.create("PGMA")
	local data = udmData:GetAssetData():GetData():Get("animations")
	for name, animData in pairs(self.m_animations) do
		animData.animation:Save(data:Get(name))
	end
	return udmData:Save(fileName)
end

function Component:SaveAscii(fileName, saveFlags)
	fileName = file.remove_file_extension(fileName, { "pgma", "pgma_b" }) .. ".pgma"

	local udmData = udm.create("PGMA")
	local data = udmData:GetAssetData():GetData():Get("animations")
	for name, animData in pairs(self.m_animations) do
		animData.animation:Save(data:Get(name))
	end
	return udmData:SaveAscii(fileName, saveFlags or udm.ASCII_SAVE_FLAG_BIT_DONT_COMPRESS_LZ4_ARRAYS)
end

function Component:StartRecording()
	if self.m_recording == true then
		return
	end

	self.m_recording = true
	self.m_animations = {}

	for _, entityInfo in ipairs(self.m_recordEntityList) do
		self:InitializeChannels(entityInfo)
	end

	self.m_startTime = time.real_time()
	self.m_cbThink = game.add_callback("Think", function()
		local t = time.real_time() - self.m_startTime
		self:RecordFrame(t)
	end)
end

ents.COMPONENT_GAME_ANIMATION_RECORDER =
	ents.register_component("game_animation_recorder", Component, ents.EntityComponent.FREGISTER_BIT_NETWORKED)

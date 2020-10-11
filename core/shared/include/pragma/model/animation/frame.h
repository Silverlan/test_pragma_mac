/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2020 Florian Weischer
 */

#ifndef __FRAME_H__
#define __FRAME_H__
#include "pragma/networkdefinitions.h"
#include "pragma/model/animation/skeleton.h"
#include <mathutil/eulerangles.h>
#include <pragma/util/orientedpoint.h>
#include <vector>
#include <unordered_map>

class Animation;
class Model;
namespace umath {class Transform; class ScaledTransform;};

struct DLLNETWORK FlexFrameData
{
	std::vector<float> flexControllerWeights;
	std::vector<uint32_t> flexControllerIds;
};

class DLLNETWORK Frame
	: public std::enable_shared_from_this<Frame>
{
public:
	static std::shared_ptr<Frame> Create(unsigned int numBones);
	static std::shared_ptr<Frame> Create(const Frame &other);

	void SetBonePosition(unsigned int boneID,const Vector3 &pos);
	void SetBoneOrientation(unsigned int boneID,const Quat &orientation);
	void SetBoneScale(uint32_t boneId,const Vector3 &scale);
	Vector3 *GetBonePosition(unsigned int boneID);
	Quat *GetBoneOrientation(unsigned int boneID);
	Vector3 *GetBoneScale(uint32_t boneId);
	const Vector3 *GetBonePosition(unsigned int boneID) const;
	const Quat *GetBoneOrientation(unsigned int boneID) const;
	const Vector3 *GetBoneScale(uint32_t boneId) const;
	bool GetBonePose(uint32_t boneId,umath::ScaledTransform &outTransform) const;
	void SetBonePose(uint32_t boneId,const umath::ScaledTransform &pose);
	void SetBonePose(uint32_t boneId,const umath::Transform &pose);
	bool GetBoneMatrix(unsigned int boneID,Mat4 *mat);
	Vector2 *GetMoveOffset();
	void GetMoveOffset(float *x,float *z);
	void SetMoveOffset(float x,float z=0);
	void SetMoveOffset(Vector2 move);
	void Localize(const Animation &anim,const Skeleton &skeleton);
	void Globalize(const Animation &anim,const Skeleton &skeleton);

	// These assume that the bones of the frame match the skeleton exactly
	void Localize(const Skeleton &skeleton);
	void Globalize(const Skeleton &skeleton);

	uint32_t GetBoneCount() const;
	void SetBoneCount(uint32_t numBones);
	std::pair<Vector3,Vector3> CalcRenderBounds(const Animation &anim,const Model &mdl) const;
	void Rotate(const Quat &rot);
	void Translate(const Vector3 &t);
	void Rotate(const Skeleton &skeleton,const Quat &rot);
	void Translate(const Skeleton &skeleton,const Vector3 &t);
	void Rotate(const Animation &anim,const Skeleton &skeleton,const Quat &rot);
	void Translate(const Animation &anim,const Skeleton &skeleton,const Vector3 &t);
	void Scale(const Vector3 &scale);

	const FlexFrameData &GetFlexFrameData() const;
	FlexFrameData &GetFlexFrameData();

	bool HasScaleTransforms() const;

	const std::vector<umath::Transform> &GetBoneTransforms() const;
	const std::vector<Vector3> &GetBoneScales() const;
	std::vector<umath::Transform> &GetBoneTransforms();
	std::vector<Vector3> &GetBoneScales();
	umath::Transform *GetBoneTransform(uint32_t idx);
	const umath::Transform *GetBoneTransform(uint32_t idx) const;
private:
	Frame(unsigned int numBones);
	Frame(const Frame &other);
	std::vector<umath::Transform> m_bones;
	std::vector<Vector3> m_scales;
	std::unique_ptr<Vector2> m_move;
	FlexFrameData m_flexFrameData {};
	std::vector<uint32_t> GetLocalRootBoneIds(const Animation &anim,const Skeleton &skeleton) const;

	void UpdateScales();
};
#endif
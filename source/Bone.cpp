#include "Bone.h"

#include "Engine.h"
#include "stdafx.h"

vec3 Bone::locToGlobVec() const
{
	return matrixToPosition(GetGlobalModel());
}

quat Bone::locToGlobQuat() const
{
	if (parent)
		return parent->rot * rot;

	return rot;
}

mat4 Bone::GetMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms)
{
	mat4 TRSLocalBase = GetLocalModel();

	mat4 TRSGlobalBase = GetGlobalModel();

	mat4 TRSLocalAnim = animTransforms[index]->GetLocalModel();

	TRSGlobalAnim = TRSLocalBase * TRSLocalAnim;
	
	if (parent)
		TRSGlobalAnim = parent->TRSGlobalAnim * TRSGlobalAnim;

	return TRSGlobalAnim * matInvert(TRSGlobalBase);
}

mat4 Bone::GetLocalModel() const
{
	mat4 T = translate(pos);
	mat4 R = quaternionToMatrix(rot);
	mat4 S = scale({ 1.f, 1.f, 1.f });

	return T * R * S;
}

mat4 Bone::GetGlobalModel() const
{
	mat4 local = GetLocalModel();

	if (parent)
		return parent->GetGlobalModel() * local;

	return local;
}
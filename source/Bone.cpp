#include "Bone.h"

#include "Engine.h"
#include "stdafx.h"

vec3 Bone::locToGlobVec(const vec3& myVec) const
{
	return matrixToPosition(GetGlobalModel());
}

quat Bone::locToGlobQuat(const quat& myQuat) const
{
	if (parent)
		return parent->rot * myQuat;

	return myQuat;
}

mat4 Bone::GetMatrix(const std::vector<std::shared_ptr<Bone>>& bones, const std::vector<std::shared_ptr<Bone>>& bones_base)
{
	mat4 TRSLocalBase = bones_base[index]->GetLocalModel();

	mat4 TRSGlobalBase = bones_base[index]->GetGlobalModel();

	mat4 TRSLocalAnim = bones[index]->GetLocalModel();

	mat4 TRSGlobalAnim = bones[index]->GetGlobalModel();

	mat4 TRSParentGlobalAnim = {};

	if (parent)
		TRSParentGlobalAnim = bones[parent->index]->GetGlobalModel();

	// Real Return = parent.globalanim * (TRSLocalBase * localAnim * matInvert(TRSGlobalBase));
	return TRSParentGlobalAnim * (TRSLocalBase * TRSLocalAnim * matInvert(TRSGlobalBase));
	//TRSGlobalAnim = TRSLocalBase * TRSLocalAnim;
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
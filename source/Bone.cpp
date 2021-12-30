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

mat4 Bone::GetMatrix(const std::vector<std::vector<std::shared_ptr<Bone>>>& animTransforms, const std::vector<std::shared_ptr<Bone>>& bones_base)
{
	mat4 TRSLocalBase = bones_base[index]->GetLocalModel();

	mat4 TRSGlobalBase = bones_base[index]->GetGlobalModel();

	// keyframe syst -> first []
	mat4 TRSLocalAnim = animTransforms[21][index]->GetLocalModel();

	globalAnimModel = TRSLocalBase * TRSLocalAnim;
	
	if (parent)
		globalAnimModel = parent->globalAnimModel * globalAnimModel;
	
	return globalAnimModel * matInvert(TRSGlobalBase);

	//apply calc to skel
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
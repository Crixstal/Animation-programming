#include "Bone.h"

#include "Engine.h"
#include "stdafx.h"

vec3 Bone::locToGlobVec() const
{
	return matrixToPosition(GetGlobalModel());
}

quat Bone::locToGlobQuat(const quat& myQuat) const
{
	if (parent)
		return parent->rot * myQuat;

	return myQuat;
}

mat4 Bone::GetMatrix(const std::vector<Bone>& bones, const std::vector<Bone>& bones_base)
{
	//vec3 rotDiff = quaternionToEuler(bones_base[index]->rot) - quaternionToEuler(bones[index]->rot);
	//vec3 posDiff = bones_base[index]->pos - bones[index]->pos;

	//mat4 TRSLocalBase = bones_base[index]->GetLocalModel();

	// global
	mat4 TRSGlobalBase = bones_base[index].GetGlobalModel();

	//if (parent)
	//	globalAnimModel = parent->globalAnimModel * globalAnimModel;

	//return bones[index].globalAnimModel * matInvert(TRSGlobalBase); // localAnim
	return TRSGlobalBase * matInvert(TRSGlobalBase);
	//return TRSLocalBase * matInvert(TRSGlobalBase);
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
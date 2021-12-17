#include "Bone.h"

#include "Engine.h"
#include "stdafx.h"

vec3 Bone::locToGlobVec(const vec3& myVec) const
{
	/*if (parent)
	{
		Referential refParent = { parent->pos, parent->rot };

		vec3 posRelativeToParent = refParent.locToGlobPos(myVec);

		return posRelativeToParent;
	}

	return myVec;*/
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
	const char* animName = "ThirdPersonWalk.anim";
	mat4 S = scale({ 1.f, 1.f, 1.f });

	vec3 rotDiff = quaternionToEuler(bones_base[index]->rot) - quaternionToEuler(bones[index]->rot);
	vec3 posDiff = bones_base[index]->pos - bones[index]->pos;

	mat4 TRSLocalBase = bones_base[index]->GetLocalModel();

	// global
	mat4 TRSGlobalBase = bones_base[index]->GetGlobalModel();

	if (parent)
		globalAnimModel = parent->globalAnimModel * globalAnimModel;

	return bones[index]->globalAnimModel * matInvert(TRSGlobalBase);
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
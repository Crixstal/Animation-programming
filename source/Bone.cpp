#include "Bone.h"

#include "Engine.h"
#include "stdafx.h"
#include <iostream>

vec3 Bone::locToGlobBone(const std::vector<Bone>& bones, const vec3& position, int deep)
{
	++deep;
	int parentID = index;
	for (int i = 0; i < deep; i++)
		parentID = bones[parentID].parentIndex;

	if (parentID != -1)
	{
		Referential refParent = { bones[parentID].getVec(), bones[parentID].getQuat() };

		vec3 posRelativeToParent = refParent.locToGlobPos(position);

		return locToGlobBone(bones, posRelativeToParent, deep);
	}

	return position;
}


float* Bone::GetMatrix(const std::vector<Bone>& bones, const std::vector<Bone>& bones_base)
{

	// Moved Bone
	mat4 T_moved = translate(locToGlobBone(bones, getVec(), 0));
	mat4 R_moved = rotateXYZ(quaternionToEuler(getQuat()));
	mat4 S_moved = scale({ 1.f, 1.f, 1.f });

	mat4 TRS_moved = T_moved * R_moved * S_moved;


	// Base Bone
	mat4 T = translate(locToGlobBone(bones_base, bones_base[index].getVec(), 0));
	mat4 R = rotateXYZ(quaternionToEuler(bones_base[index].getQuat()));
	mat4 S = scale({ 1.f, 1.f, 1.f });
	
	mat4 TRS_base = T * R * S;

	// Are TRS_base and TRS_moved the same?

	// the (strange) matrix to return
	//mat4 to_return = TRS_moved * matInvert(TRS_base);
	mat4 to_return = TRS_base * matInvert(TRS_moved);

	return to_return.e;
}
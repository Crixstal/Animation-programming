#pragma once

#include <vector>
#include <memory>

#include "Definitions.h"
#include "Quaternion.h" // include Mat4.h which include Vector3.h

class Bone
{
public:
	Bone() {}
	~Bone() {}

	const char* name = nullptr;
	int index = 0;
	Bone* parent = nullptr;
	vec3 pos = {};
	quat rot = quatIdentity();

	mat4 TRSGlobalAnim = matIdentity();

	vec3 locToGlobVec() const;
	quat locToGlobQuat() const;

	mat4 GetMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms);
	mat4 GetLocalModel() const;
	mat4 GetGlobalModel() const;
};
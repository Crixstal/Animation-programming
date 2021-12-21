#pragma once

#include <vector>
#include <memory>

#include "Definitions.h"

class Bone
{
public:
	Bone() {}
	~Bone() {}

	const char* name = nullptr;
	int index = 0;
	vec3 pos = {};
	quat rot = {};
	Bone* parent = nullptr;

	vec3 locToGlobVec() const;
	quat locToGlobQuat(const quat& myQuat) const;

	mat4 GetMatrix(const std::vector<Bone>& bones, const std::vector<Bone>& bones_base);
	mat4 GetLocalModel() const;
	mat4 GetGlobalModel() const;
};
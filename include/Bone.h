#pragma once

#include <vector>

#include "Definitions.h"

class Bone
{
public:
	Bone() {}
	~Bone() {}

	const char* name = nullptr;
	int index = 0;
	int parentIndex = 0;
	float pos[3] = {};
	float quater[4] = {};

	vec3 locToGlobBone(const std::vector<Bone>& bones, const vec3& position, int deep);

	vec3 getVec() const { return vec3(pos[0], pos[1], pos[2]); };
	quat getQuat() const { return quat(quater[0], quater[1], quater[2], quater[3]); };

	float* GetMatrix(const std::vector<Bone>& bones, const std::vector<Bone>& bones_base);
};
#pragma once

#include <vector>

#include "Bone.h"

class Skeleton
{
public:
	Skeleton() {}
	~Skeleton() {}

	void Set();
	void Draw();
	void MoveBone(const int indexBone, const quat& rotation, const float& speed);
	const float* GetBonesMatrix();

private:
	std::vector<Bone>* GetBones() { return &bones; };

	std::vector<Bone> bones;
	float offset = -100.f;
};
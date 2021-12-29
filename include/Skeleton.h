#pragma once

#include <vector>

#include "Bone.h"

class Skeleton
{
public:
	Skeleton() {}
	~Skeleton() {}

	void Init();
	void Draw();
	void MoveBone(const int indexBone, const quat& rotation, const float& speed);
	const float* GetBonesMatrix();
	const void animSkel(const float& frameTime, const char* animName);

	const int GetBonesNumber() { return bones.size(); };

	std::vector<std::shared_ptr<Bone>> bones;
	std::vector<std::shared_ptr<Bone>> bones_base;
	float offset = -100.f;
};
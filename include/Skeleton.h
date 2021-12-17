#pragma once

#include <vector>
#include <memory>

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
	const void animSkel(float& frameTime);

	const int GetBonesNumber() { return bones.size(); };

private:
	std::vector<std::shared_ptr<Bone>> bones;
	std::vector<std::shared_ptr<Bone>> bones_base;
	float offset = -100.f;
};
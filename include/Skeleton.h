#pragma once

#include <vector>

#include "Bone.h"

class Skeleton
{
public:
	Skeleton() {}
	~Skeleton() {}

	void Init();

	void MoveBone(const int indexBone, const quat& rotation, const float& translation, const float& speed);
	const float* GetBonesMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms);
	const void Draw(const float& alpha, const std::vector<std::shared_ptr<Bone>>& currAnim, const std::vector<std::shared_ptr<Bone>>& nextAnim);

	const int GetBonesNumber() { return skeleton.size(); };

private:
	std::vector<std::shared_ptr<Bone>> skeleton;
	float offset = -100.f;
};
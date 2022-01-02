#pragma once

#include <vector>

#include "Bone.h"

class Skeleton
{
public:
	Skeleton() {}
	~Skeleton() { delete matrix; }

	void Init();

	void MoveBone(const int indexBone, const quat& rotation, const float& translation, const float& speed);
	const float* GetBonesMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms);
	const void DrawWithAnim(const float& alpha, const std::vector<std::shared_ptr<Bone>>& currAnim, const std::vector<std::shared_ptr<Bone>>& nextAnim);
	const void Draw();

	const int GetBonesNumber() { return skeleton.size(); };

private:
	const void ResetSkeleton();

	std::vector<std::shared_ptr<Bone>> skeleton;

	std::vector<vec3> posBindPose;
	std::vector<quat> rotBindPose;

	float offset = -100.f;

	float* matrix;
};
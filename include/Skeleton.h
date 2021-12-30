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
	const float* GetBonesMatrix(const std::vector<std::shared_ptr<Bone>>& animTransforms);
	const void animSkel(const char* animName, const int currKeyFrame, const float& alpha, const std::vector<std::shared_ptr<Bone>>& currAnim, const std::vector<std::shared_ptr<Bone>>& nextAnim);

	const int GetBonesNumber() { return bones_base.size(); };

	std::vector<std::shared_ptr<Bone>> bones_base; // always in T-pose
	std::vector<std::shared_ptr<Bone>> bones_anim;
	float offset = -100.f;
};
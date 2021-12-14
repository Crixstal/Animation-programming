#pragma once

#include "Definitions.h"

struct Referential
{
    vec3 origin;
    vec3 i;
    vec3 j;
    vec3 k;
    float angle;

    Referential();
    Referential(const vec3& _origin, const quat& quat);
    Referential(const vec3& ptA, const vec3& ptB);
    Referential(const vec3& _origin, const vec3& _i, const vec3& _j, const vec3& _k)
        : origin(_origin), i(_i), j(_j), k(_k) {}

    void refNormalize();

    vec3 locToGlobPos(const vec3& pt);
    vec3 globToLocPos(const vec3& pt);

    vec3 locToGlobVect(const vec3& vect);
    vec3 globToLocVect(const vec3& vect);
};
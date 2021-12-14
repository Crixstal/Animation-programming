#include "Referential.h"
#include "Vector3.h"

Referential::Referential()
{
    origin = vec3(0.f, 0.f, 0.f);
    i = vec3(1.f, 0.f, 0.f);
    j = vec3(0.f, 1.f, 0.f);
    k = vec3(0.f, 0.f, 1.f);
}

Referential::Referential(const vec3& _origin, const quat& quat)
{
    origin = _origin;
    i = rotateByQuat(vec3(1.f, 0.f, 0.f), quat);
    j = rotateByQuat(vec3(0.f, 1.f, 0.f), quat);
    k = rotateByQuat(vec3( 0.f, 0.f, 1.f), quat);
    
    angle = quat.w;
}

Referential::Referential(const vec3& ptA, const vec3& ptB)
{
    vec3 axe = ptB - ptA;

    origin = ptA + (axe / 2.f);
    j = normalize(axe);
    vec3 notJ = { 1.f, 0.f, 0.f };
    if (j == notJ)
        notJ = { 0.f, 1.f, 0.f };
    k = normalize((j ^ notJ));
    i = normalize((k ^ j));
}

void Referential::refNormalize()
{
    normalize(i);
    normalize(j);
    normalize(k);
}


vec3 Referential::locToGlobPos(const vec3& pt)
{
    return origin + (i * pt.x) + (j * pt.y) + (k * pt.z);
}

vec3 Referential::globToLocPos(const vec3& pt)
{
    return {
        dotProduct(pt - origin, i),
        dotProduct(pt - origin, j),
        dotProduct(pt - origin, k)
    };
}

vec3 Referential::locToGlobVect(const vec3& vect)
{
    return (i * vect.x) + (j * vect.y) + (k * vect.z);
}

vec3 Referential::globToLocVect(const vec3& vect)
{
    return {
        dotProduct(vect, i),
        dotProduct(vect, j),
        dotProduct(vect, k)
    };
}
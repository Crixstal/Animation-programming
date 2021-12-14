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


void Referential::locToGlobPos(const Referential& local, vec3& pt)
{
    pt = local.origin + (local.i * pt.x) + (local.j * pt.y) + (local.k * pt.z);
}

void Referential::globToLocPos(const Referential& local, vec3& pt)
{
    vec3 OP = pt - local.origin;

    pt.x = dotProduct(OP, local.i);
    pt.y = dotProduct(OP, local.j);
    pt.z = dotProduct(OP, local.k);
}

void Referential::locToGlobVect(const Referential& local, vec3& vect)
{
    vec3 OP = (local.i * vect.x) + (local.j * vect.y) + (local.k * vect.z);
    vect = OP;
}

void Referential::globToLocVect(const Referential& local, vec3& vect)
{
    vec3 tmpVect = vect;

    vect = {
        dotProduct(tmpVect, local.i),
        dotProduct(tmpVect, local.j),
        dotProduct(tmpVect, local.k)
    };
}
#pragma once

#include "Definitions.h"

#include "Mat4.h" //  already include Vector3.h


inline quat operator+(const quat& q1, const quat& q2)
{
    return {
        q1.x + q2.x,
        q1.y + q2.y,
        q1.z + q2.z,
        q1.w + q2.w
    };
}
inline quat operator+(const quat& q, const float& k)
{
    return {
        q.x + k,
        q.y + k,
        q.z + k,
        q.w + k
    };
}

inline quat operator-(const quat& q1, const quat& q2)
{
    return {
        q1.x - q2.x,
        q1.y - q2.y,
        q1.z - q2.z,
        q1.w - q2.w
    };
}
inline quat operator-(const quat& q, const float& k)
{
    return {
        q.x - k,
        q.y - k,
        q.z - k,
        q.w - k
    };
}

inline quat operator*(const quat& quat1, const quat& quat2)
{
    quat result = quat(0.f, 0.f, 0.f, 0.f);

    float qax = quat1.x, qay = quat1.y, qaz = quat1.z, qaw = quat1.w;
    float qbx = quat2.x, qby = quat2.y, qbz = quat2.z, qbw = quat2.w;

    result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
    result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
    result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
    result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

    return result;
}
inline quat operator*(const quat& q, const float& k)
{
    quat result = { 0 };

    float qax = q.x, qay = q.y, qaz = q.z, qaw = q.w;

    return {
        qax * k + qaw * k + qay * k - qaz * k,
        qay * k + qaw * k + qaz * k - qax * k,
        qaz * k + qaw * k + qax * k - qay * k,
        qaw * k - qax * k - qay * k - qaz * k
    };
}

inline quat operator/(const quat& q1, const quat& q2)
{
    return {
        q1.x / q2.x,
        q1.y / q2.y,
        q1.z / q2.z,
        q1.w / q2.w
    };
}

inline quat operator*=(quat& quat1, const quat& quat2)
{
    quat1 = quat1 * quat2;
    return quat1;
}


inline quat quatIdentity()
{
    return { 0.f, 0.f, 0.f, 1.f };
}

inline float quatLength(const quat& q)
{
    return (float)sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

inline quat quatNormalize(const quat& q)
{
    float length, ilength;
    length = quatLength(q);

    if (length == 0.0f)
        length = 1.0f;

    ilength = 1.0f / length;

    return {
        q.x * ilength,
        q.y * ilength,
        q.z * ilength,
        q.w * ilength
    };
}

inline quat quaternionFromMatrix(const mat4& mat)
{
    quat result = quatIdentity();

    if ((mat.e[0] > mat.e[5]) && (mat.e[0] > mat.e[10]))
    {
        float s = sqrtf(1.0f + mat.e[0] - mat.e[5] - mat.e[10]) * 2;

        result.x = 0.25f * s;
        result.y = (mat.e[4] + mat.e[1]) / s;
        result.z = (mat.e[2] + mat.e[8]) / s;
        result.w = (mat.e[9] - mat.e[6]) / s;
    }
    else if (mat.e[5] > mat.e[10])
    {
        float s = sqrtf(1.0f + mat.e[5] - mat.e[0] - mat.e[10]) * 2;
        result.x = (mat.e[4] + mat.e[1]) / s;
        result.y = 0.25f * s;
        result.z = (mat.e[9] + mat.e[6]) / s;
        result.w = (mat.e[2] - mat.e[8]) / s;
    }
    else
    {
        float s = sqrtf(1.0f + mat.e[10] - mat.e[0] - mat.e[5]) * 2;
        result.x = (mat.e[2] + mat.e[8]) / s;
        result.y = (mat.e[9] + mat.e[6]) / s;
        result.z = 0.25f * s;
        result.w = (mat.e[4] - mat.e[1]) / s;
    }

    return result;
}

inline quat quaternionFromEuler(const float& roll, const float& pitch, const float& yaw)
{
    float x0 = cosf(roll * 0.5f);
    float x1 = sinf(roll * 0.5f);
    float y0 = cosf(pitch * 0.5f);
    float y1 = sinf(pitch * 0.5f);
    float z0 = cosf(yaw * 0.5f);
    float z1 = sinf(yaw * 0.5f);

    return {
        x1 * y0 * z0 - x0 * y1 * z1,
        x0 * y1 * z0 + x1 * y0 * z1,
        x0 * y0 * z1 - x1 * y1 * z0,
        x0 * y0 * z0 + x1 * y1 * z1
    };
}

inline quat quaternionFromEuler(const vec3& rotation)
{
    return quaternionFromEuler(rotation.x, rotation.y, rotation.z);
}

inline vec3 quaternionToEuler(const quat& q)
{
    vec3 result = { 0 };

    // roll (x-axis rotation)
    float x0 = 2.0f * (q.w * q.x + q.y * q.z);
    float x1 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    result.x = atan2f(x0, x1) * RAD2DEG;

    // pitch (y-axis rotation)
    float y0 = 2.0f * (q.w * q.y - q.z * q.x);
    y0 = y0 > 1.0f ? 1.0f : y0;
    y0 = y0 < -1.0f ? -1.0f : y0;
    result.y = asinf(y0) * RAD2DEG;

    // yaw (z-axis rotation)
    float z0 = 2.0f * (q.w * q.z + q.x * q.y);
    float z1 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    result.z = atan2f(z0, z1) * RAD2DEG;

    return result;
}

inline quat quatInvert(const quat& q)
{
    quat result = q;
    float length = quatLength(q);
    float lengthSq = length * length;

    if (lengthSq != 0.0)
    {
        float i = 1.0f / lengthSq;

        result.x *= -i;
        result.y *= -i;
        result.z *= -i;
        result.w *= i;
    }

    return result;
}

// Calculate linear interpolation between two quaternions
inline quat quatLerp(const quat& q1, const quat& q2, const float& amount)
{
    return {
        q1.x + amount * (q2.x - q1.x),
        q1.y + amount * (q2.y - q1.y),
        q1.z + amount * (q2.z - q1.z),
        q1.w + amount * (q2.w - q1.w)
    };
}

// Calculate slerp-optimized interpolation between two quaternions
inline quat quatNlerp(const quat& q1, const quat& q2, const float& amount)
{
    quat result = quatLerp(q1, q2, amount);

    return quatNormalize(result);
}

// Calculates spherical linear interpolation between two quaternions
inline quat quatSlerp(const quat& q1, const quat& q2, const float& amount)
{
    quat result = { 0 };

    float cosHalfTheta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

    if (fabs(cosHalfTheta) >= 1.0f) result = q1;
    else if (cosHalfTheta > 0.95f) result = quatNlerp(q1, q2, amount);
    else
    {
        float halfTheta = acosf(cosHalfTheta);
        float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

        if (fabs(sinHalfTheta) < 0.001f)
        {
            result.x = (q1.x * 0.5f + q2.x * 0.5f);
            result.y = (q1.y * 0.5f + q2.y * 0.5f);
            result.z = (q1.z * 0.5f + q2.z * 0.5f);
            result.w = (q1.w * 0.5f + q2.w * 0.5f);
        }
        else
        {
            float ratioA = sinf((1 - amount) * halfTheta) / sinHalfTheta;
            float ratioB = sinf(amount * halfTheta) / sinHalfTheta;

            result.x = (q1.x * ratioA + q2.x * ratioB);
            result.y = (q1.y * ratioA + q2.y * ratioB);
            result.z = (q1.z * ratioA + q2.z * ratioB);
            result.w = (q1.w * ratioA + q2.w * ratioB);
        }
    }

    return result;
}

inline quat quatFromVector3ToVector3(const vec3& from, const vec3& to)
{
    quat result = { 0 };

    float cos2Theta = dotProduct(from, to);
    vec3 cross = crossProduct(from, to);

    result.x = cross.x;
    result.y = cross.y;
    result.z = cross.z;
    result.w = 1.0f + cos2Theta;

    return quatNormalize(result);
}

inline quat quatFromAxisAngle(const vec3& axis, float angle)
{
    quat result = { 0.0f, 0.0f, 0.0f, 1.0f };

    if (vecMagnitude(axis) != 0.0f)
        angle *= 0.5f;

    vec3 newAxis = normalize(axis);

    float sinres = sinf(angle);
    float cosres = cosf(angle);

    result.x = newAxis.x * sinres;
    result.y = newAxis.y * sinres;
    result.z = newAxis.z * sinres;
    result.w = cosres;

    return quatNormalize(result);
}

inline void quatToAxisAngle(quat q, vec3* outAxis, float* outAngle)
{
    if (fabs(q.w) > 1.0f)
        q = quatNormalize(q);

    vec3 resAxis = { 0.0f, 0.0f, 0.0f };
    float resAngle = 2.0f * acosf(q.w);
    float den = sqrtf(1.0f - q.w * q.w);

    if (den > 0.0001f)
    {
        resAxis.x = q.x / den;
        resAxis.y = q.y / den;
        resAxis.z = q.z / den;
    }
    else
        resAxis.x = 1.0f;

    *outAxis = resAxis;
    *outAngle = resAngle;
}

inline quat quatTransform(const quat& q, const mat4& mat)
{
    return {
        mat.e[0] * q.x + mat.e[4] * q.y + mat.e[8] * q.z + mat.e[12] * q.w,
        mat.e[1] * q.x + mat.e[5] * q.y + mat.e[9] * q.z + mat.e[13] * q.w,
        mat.e[2] * q.x + mat.e[6] * q.y + mat.e[10] * q.z + mat.e[14] * q.w,
        mat.e[3] * q.x + mat.e[7] * q.y + mat.e[11] * q.z + mat.e[15] * q.w
    };
}

inline vec3 vec3Unproject(const vec3& source, const mat4& projection, const mat4& view)
{
    mat4 matViewProj = matMultiply(view, projection);
    matViewProj = matInvert(matViewProj);

    quat quat = { source.x, source.y, source.z, 1.0f };

    quat = quatTransform(quat, matViewProj);

    return {
        quat.x / quat.w,
        quat.y / quat.w,
        quat.z / quat.w
    };
}

inline vec3 modelMatrixToRotation(mat4 matrix)
{
    matrix.e[3] = 0.f;
    matrix.e[7] = 0.f;
    matrix.e[11] = 0.f;

    vec3 scale = modelMatrixToScale(matrix);

    matrix.e[0] /= scale.x;
    matrix.e[4] /= scale.x;
    matrix.e[8] /= scale.x;
    matrix.e[1] /= scale.y;
    matrix.e[5] /= scale.y;
    matrix.e[9] /= scale.y;
    matrix.e[2] /= scale.z;
    matrix.e[6] /= scale.z;
    matrix.e[10] /= scale.z;

    return rotateByQuat({ 1.f, 0.f, 0.f }, quaternionFromMatrix(matrix));
}
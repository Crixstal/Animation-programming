#pragma once

#include "Definitions.h"

#include "Vector3.h"


inline mat4 operator*(const mat4& a, const mat4& b)
{
    mat4 result = { 0.f };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0.f;
            for (int k = 0; k < 4; k++)
                sum += a.c[i].e[k] * b.c[k].e[j];

            result.c[i].e[j] = sum;
        }
    }

    return result;
}


inline mat4 matIdentity()
{
    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };
}

inline mat4 translate(const vec3& value)
{
    return {
        1.f, 0.f, 0.f, value.x,
        0.f, 1.f, 0.f, value.y,
        0.f, 0.f, 1.f, value.z,
        0.f, 0.f, 0.f, 1.f
    };
}

inline mat4 scale(const vec3& value)
{
    return {
        value.x, 0.f,     0.f,     0.f,
        0.f,     value.y, 0.f,     0.f,
        0.f,     0.f,     value.z, 0.f,
        0.f,     0.f,     0.f,     1.f
    };
}

inline mat4 rotateX(const float& angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        1.f, 0.f,  0.f, 0.f,
        0.f, cos, -sin, 0.f,
        0.f, sin,  cos, 0.f,
        0.f, 0.f,  0.f, 1.f
    };
}

inline mat4 rotateY(const float& angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        cos,  0.f, sin, 0.f,
        0.f,  1.f, 0.f, 0.f,
        -sin, 0.f, cos, 0.f,
        0.f,  0.f, 0.f, 1.f
    };
}

inline mat4 rotateZ(const float& angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        cos, -sin, 0.f, 0.f,
        sin, cos,  0.f, 0.f,
        0.f, 0.f,  1.f, 0.f,
        0.f, 0.f,  0.f, 1.f
    };
}

inline mat4 rotateXYZ(const vec3& angleRadians)
{
    return rotateX(angleRadians.x) * rotateY(angleRadians.y) * rotateZ(angleRadians.z);
}

inline mat4 frustum(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far)
{
    // Pre-compute divisions
    float OneOverTopMinusBottom = 1.f / (top - bottom);
    float OneOverNeasMinusFar = 1.f / (near - far);
    float OneOverRightMinusLeft = 1.f / (right - left);

    return {
        2.f * near * OneOverRightMinusLeft, 0.f,                                (right + left) * OneOverRightMinusLeft, 0.f,
        0.f,                                2.f * near * OneOverTopMinusBottom, (top + bottom) * OneOverTopMinusBottom, 0.f,
        0.f,                                0.f,                                (far + near) * OneOverNeasMinusFar,     2.f * far * near * OneOverNeasMinusFar,
        0.f,                                0.f,                                -1.f,                                   0.f
    };
}

inline mat4 orthographic(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far)
{
    // Pre-compute divisions
    float OneOverTopMinusBottom = 1.f / (top - bottom);
    float OneOverFarMinusNear = 1.f / (far - near);
    float OneOverRightMinusLeft = 1.f / (right - left);

    return {
        2.f * OneOverRightMinusLeft, 0.f,                         0.f,                        -(right + left) * OneOverRightMinusLeft,
        0.f,                         2.f * OneOverTopMinusBottom, 0.f,                        -(top + bottom) * OneOverTopMinusBottom,
        0.f,                         0.f,                         -2.f * OneOverFarMinusNear, -(far + near) * OneOverFarMinusNear,
        0.f,                         0.f,                         0.f,                        1.f
    };
}

inline mat4 perspective(const float& fovY, const float& aspect, const float& near, const float& far)
{
    float top = near * tanf(fovY * 0.5f);
    float right = top * aspect;

    return frustum(-right, right, -top, top, near, far);
}

inline mat4 mat3ToMat4(const mat3& mat)
{
    return {
        mat.e[0], mat.e[1], mat.e[2], 0.f,
        mat.e[3], mat.e[4], mat.e[5], 0.f,
        mat.e[6], mat.e[7], mat.e[8], 0.f,
        0.f,      0.f,      0.f,      1.f
    };
}

inline mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
    // Create new coordinate system
    vec3 newZ = normalize(eye - center);
    vec3 newX = normalize(up ^ newZ);
    vec3 newY = normalize(newZ ^ newX);

    return {
        newX.x, newX.y, newX.z, -dotProduct(newX, eye),
        newY.x, newY.y, newY.z, -dotProduct(newY, eye),
        newZ.x, newZ.y, newZ.z, -dotProduct(newZ, eye),
        0.f,    0.f,    0.f,    1.f
    };
}

inline mat4 quaternionToMatrix(const quat& q)
{
    mat4 result = matIdentity();

    float a2 = 2 * (q.x * q.x), b2 = 2 * (q.y * q.y), c2 = 2 * (q.z * q.z);

    float ab = 2 * (q.x * q.y), ac = 2 * (q.x * q.z), bc = 2 * (q.y * q.z);
    float ad = 2 * (q.x * q.w), bd = 2 * (q.y * q.w), cd = 2 * (q.z * q.w);

    result.e[0] = 1 - b2 - c2;
    result.e[1] = ab - cd;
    result.e[2] = ac + bd;

    result.e[4] = ab + cd;
    result.e[5] = 1 - a2 - c2;
    result.e[6] = bc - ad;

    result.e[8] = ac - bd;
    result.e[9] = bc + ad;
    result.e[10] = 1 - a2 - b2;

    return result;
}

inline mat3 mat4ToMat3(const mat4& mat)
{
    return {
        mat.e[0], mat.e[1], mat.e[2],
        mat.e[4], mat.e[5], mat.e[6],
        mat.e[8], mat.e[9], mat.e[10]
    };
}

inline mat4 matMultiply(const mat4& left, const mat4& right)
{
    return {
        left.e[0] * right.e[0] + left.e[1] * right.e[4] + left.e[2] * right.e[8] + left.e[3] * right.e[12],
        left.e[0] * right.e[1] + left.e[1] * right.e[5] + left.e[2] * right.e[9] + left.e[3] * right.e[13],
        left.e[0] * right.e[2] + left.e[1] * right.e[6] + left.e[2] * right.e[10] + left.e[3] * right.e[14],
        left.e[0] * right.e[3] + left.e[1] * right.e[7] + left.e[2] * right.e[11] + left.e[3] * right.e[15],
        left.e[4] * right.e[0] + left.e[5] * right.e[4] + left.e[6] * right.e[8] + left.e[7] * right.e[12],
        left.e[4] * right.e[1] + left.e[5] * right.e[5] + left.e[6] * right.e[9] + left.e[7] * right.e[13],
        left.e[4] * right.e[2] + left.e[5] * right.e[6] + left.e[6] * right.e[10] + left.e[7] * right.e[14],
        left.e[4] * right.e[3] + left.e[5] * right.e[7] + left.e[6] * right.e[11] + left.e[7] * right.e[15],
        left.e[8] * right.e[0] + left.e[9] * right.e[4] + left.e[10] * right.e[8] + left.e[11] * right.e[12],
        left.e[8] * right.e[1] + left.e[9] * right.e[5] + left.e[10] * right.e[9] + left.e[11] * right.e[13],
        left.e[8] * right.e[2] + left.e[9] * right.e[6] + left.e[10] * right.e[10] + left.e[11] * right.e[14],
        left.e[8] * right.e[3] + left.e[9] * right.e[7] + left.e[10] * right.e[11] + left.e[11] * right.e[15],
        left.e[12] * right.e[1] + left.e[13] * right.e[5] + left.e[14] * right.e[9] + left.e[15] * right.e[13],
        left.e[12] * right.e[0] + left.e[13] * right.e[4] + left.e[14] * right.e[8] + left.e[15] * right.e[12],
        left.e[12] * right.e[2] + left.e[13] * right.e[6] + left.e[14] * right.e[10] + left.e[15] * right.e[14],
        left.e[12] * right.e[3] + left.e[13] * right.e[7] + left.e[14] * right.e[11] + left.e[15] * right.e[15]
    };
}

inline mat4 matInvert(const mat4& mat)
{
    mat4 result = { 0 };

    // Cache the matrix values (speed optimization)
    float a00 = mat.e[0], a01 = mat.e[1], a02 = mat.e[2], a03 = mat.e[3];
    float a10 = mat.e[4], a11 = mat.e[5], a12 = mat.e[6], a13 = mat.e[7];
    float a20 = mat.e[8], a21 = mat.e[9], a22 = mat.e[10], a23 = mat.e[11];
    float a30 = mat.e[12], a31 = mat.e[13], a32 = mat.e[14], a33 = mat.e[15];

    float b00 = a00 * a11 - a01 * a10;
    float b01 = a00 * a12 - a02 * a10;
    float b02 = a00 * a13 - a03 * a10;
    float b03 = a01 * a12 - a02 * a11;
    float b04 = a01 * a13 - a03 * a11;
    float b05 = a02 * a13 - a03 * a12;
    float b06 = a20 * a31 - a21 * a30;
    float b07 = a20 * a32 - a22 * a30;
    float b08 = a20 * a33 - a23 * a30;
    float b09 = a21 * a32 - a22 * a31;
    float b10 = a21 * a33 - a23 * a31;
    float b11 = a22 * a33 - a23 * a32;

    // Calculate the invert determinant (inlined to avoid double-caching)
    float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

    return {
        (a11 * b11 - a12 * b10 + a13 * b09) * invDet,
        (-a01 * b11 + a02 * b10 - a03 * b09) * invDet,
        (a31 * b05 - a32 * b04 + a33 * b03) * invDet,
        (-a21 * b05 + a22 * b04 - a23 * b03) * invDet,
        (-a10 * b11 + a12 * b08 - a13 * b07) * invDet,
        (a00 * b11 - a02 * b08 + a03 * b07) * invDet,
        (-a30 * b05 + a32 * b02 - a33 * b01) * invDet,
        (a20 * b05 - a22 * b02 + a23 * b01) * invDet,
        (a10 * b10 - a11 * b08 + a13 * b06) * invDet,
        (-a00 * b10 + a01 * b08 - a03 * b06) * invDet,
         (a30 * b04 - a31 * b02 + a33 * b00) * invDet,
         (-a20 * b04 + a21 * b02 - a23 * b00) * invDet,
         (-a10 * b09 + a11 * b07 - a12 * b06) * invDet,
         (a00 * b09 - a01 * b07 + a02 * b06) * invDet,
         (-a30 * b03 + a31 * b01 - a32 * b00) * invDet,
         (a20 * b03 - a21 * b01 + a22 * b00) * invDet
    };
}

inline vec3 modelMatrixToPosition(const mat4& matrix)
{
    return vec3(matrix.e[3], matrix.e[7], matrix.e[11]);
}

inline vec3 modelMatrixToScale(const mat4& matrix)
{
    return (
        vecMagnitude({ matrix.e[0], matrix.e[4], matrix.e[8] }),
        vecMagnitude({ matrix.e[1], matrix.e[5], matrix.e[9] }),
        vecMagnitude({ matrix.e[2], matrix.e[6], matrix.e[10] })
        );
}
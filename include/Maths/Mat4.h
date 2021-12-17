#pragma once

#include "Definitions.h"

#include "Vector3.h"


inline vec4 operator*(const mat4& mat, const vec4& vec)
{
    vec4 result = { 0.f, 0.f, 0.f, 0.f };

    for (int column = 0; column < 4; column++)
    {
        for (int line = 0; line < 4; line++)
        {
            result.e[column] += *(&mat.l[line].x + column) * vec.e[line];
        }
    }

    return result;
}

inline mat4 operator*(const mat4& mat1, const mat4& mat2)
{
    mat4 result = {};

    for (int column = 0; column < 4; ++column)
    {
        for (int line = 0; line < 4; ++line)
        {
            for (int vect = 0; vect < 4; ++vect)
                result.l[line].e[column] += *(&mat1.l[vect].x + column) * mat2.l[line].e[vect];
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
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    value.x, value.y, value.z, 1.f
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
        0.f, cos, sin, 0.f,
        0.f, -sin,  cos, 0.f,
        0.f, 0.f,  0.f, 1.f
    };
}

inline mat4 rotateY(const float& angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        cos,  0.f, -sin, 0.f,
        0.f,  1.f, 0.f, 0.f,
        sin, 0.f, cos, 0.f,
        0.f,  0.f, 0.f, 1.f
    };
}

inline mat4 rotateZ(const float& angleRadians)
{
    float cos = cosf(angleRadians), sin = sinf(angleRadians);

    return {
        cos, sin, 0.f, 0.f,
        -sin, cos,  0.f, 0.f,
        0.f, 0.f,  1.f, 0.f,
        0.f, 0.f,  0.f, 1.f
    };
}

inline mat4 rotateXYZ(const vec3& angleRadians)
{
    return rotateY(angleRadians.y) * rotateX(angleRadians.x) * rotateZ(angleRadians.z);
}

inline mat4 frustum(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far)
{
    float rightMinusLeft = right - left;
    float topBMinusottom = top - bottom;
    float farMinusNear = far - near;

    return {
        (2.f * near) / rightMinusLeft,      0.f,                                0.f,                                    0.f,
        0.f,                                (2.f * near) / topBMinusottom,      0.f,                                    0.f,
        (right + left) / rightMinusLeft,    (top + bottom) / topBMinusottom,    -(far + near) / farMinusNear,           -1.f,
        0.f,                                0.f,                                -(far * near * 2.f) / farMinusNear,     0.f
    };
}

inline mat4 orthographic(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far)
{
    float rightMinusLeft = right - left;
    float topMinusBottom = top - bottom;
    float farMinusNear = far - near;

    return
    {
        2.f / rightMinusLeft,               0.f,                                0.f,                            0.f,
        0.f,                                2.f / topMinusBottom,               0.f,                            0.f,
        0.f,                                0.f,                                -2 / farMinusNear,              0.f,
       -(right + left) / rightMinusLeft,    -(top + bottom) / topMinusBottom,   -(near + far) / farMinusNear,   1.f
    };
}

inline mat4 perspective(const float& fovY, const float& aspect, const float& near, const float& far, const bool& ortho)
{
    float top;

    if (ortho)
        top = tanf(DEG2RAD * fovY * 0.5f);
    else 
        top = near * tanf(DEG2RAD * fovY * 0.5f);

    float right = top * aspect;
    float bottom = -top, left = -right;

    if (ortho)
        return orthographic(left, right, bottom, top, near, far);
    else
        return frustum(left, right, bottom, top, near, far);
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
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xz = q.x * q.z, xy = q.x * q.y, xw = q.x * q.w;
    float yz = q.y * q.z, yw = q.y * q.w, zw = q.z * q.w;

    return {
        1 - 2 * (yy + zz),    2 * (xy + zw),        2 * (xz - yw),        0.f,
        2 * (xy - zw),        1 - 2 * (xx + zz),    2 * (yz + xw),        0.f,
        2 * (xz + yw),        2 * (yz - xw),        1 - 2 * (xx + yy),    0.f,
        0.f,                  0.f,                  0.f,                  1.f
    };
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

inline vec3 matrixToPosition(const mat4& matrix)
{
    return vec3(matrix.e[12], matrix.e[13], matrix.e[14]);
}

inline vec3 matrixToScale(const mat4& matrix)
{
    return (
        vecMagnitude({ matrix.e[0], matrix.e[4], matrix.e[8] }),
        vecMagnitude({ matrix.e[1], matrix.e[5], matrix.e[9] }),
        vecMagnitude({ matrix.e[2], matrix.e[6], matrix.e[10] })
        );
}
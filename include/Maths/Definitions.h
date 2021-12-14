#pragma once

#include <cmath>

constexpr float TAU = 6.28318530717958647692f;
constexpr float PI = 3.14159265358979323846f;
constexpr float PIO4 = PI / 4.f;
constexpr float PIO2 = PI / 2.f;

constexpr float DEG2RAD = PI / 180.f;
constexpr float RAD2DEG = 180.f / PI;

union vec2
{
    vec2(float x = 0.f, float y = 0.f)
            : x(x), y(y)
        {}

    float e[2];

    struct { float x; float y; };
    struct { float s; float t; };
    struct { float u; float v; };
};

union vec3
{
    vec3(float x = 0.f, float y = 0.f, float z = 0.f)
            : x(x), y(y), z(z)
        {}
    vec3(vec2 xy, float z = 0.f)
            : x(xy.x), y(xy.y), z(z)
        {}

    float e[3];
    vec2  xy;
    vec2  rg;
    vec2  uv;

    struct { float x; float y; float z; };
    struct { float r; float g; float b; };
    struct { float c; float l; float q; };
    struct { float u; float v; float q; };
};

union vec4
{
    vec4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f)
            : x(x), y(y), z(z), w(w)
        {}

    vec4(vec3 xyz, float w = 0.f)
            : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
        {}

    vec4(vec2 xy, float z = 0.f, float w = 0.f)
            : x(xy.x), y(xy.y), z(z), w(w)
        {}

    float e[4];
    vec3  xyz;
    vec3  rgb;
    vec2  xy;
    vec2  rg;

    struct { float x; float y; float z; float w; };
    struct { float r; float g; float b; float a; };
};

union mat3
{
    mat3() = default;
    float e[9] = { 0.f };
    vec3  c[3];
};

union mat4
{
    mat4() = default;
    float e[16] = { 0.f };
    vec4  c[4];
};

union quat
{
    quat(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f)
        : x(x), y(y), z(z), w(w)
    {}

    float e[4];
    struct { float x; float y; float z; float w; };
};

struct Segment
{
    vec3 ptA;
    vec3 ptB;
};


template<typename T>
vec2 operator*(const vec2& vec, const T& scale)
{
    return { vec.x * scale, vec.y * scale };
}

template<typename T>
vec2 operator*(const T& scale, const vec2& vec)
{
    return vec * scale;
}

inline vec4 operator*(const mat4& m, const vec4& v)
{
    vec4 result;

    for (int i = 0; i < 4; i++)
    {
        float sum = 0.f;
        for (int j = 0; j < 4; j++)
            sum += m.c[i].e[j] * v.e[j];

        result.e[i] = sum;
    }

    return result;
}
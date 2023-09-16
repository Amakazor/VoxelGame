#pragma once
#include <bx/math.h>

#include "vector3.h"


struct vector4
{
    float x;
    float y;
    float z;
    float w;

    ~vector4() = default;
    
    vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    vector4(const float x, const float y, const float z) : x(x), y(y), z(z), w(1.0f) {}
    
    explicit vector4(const bx::Vec3& other) : x(other.x), y(other.y), z(other.z), w(1.0f) {}
    explicit vector4(const bx::Vec3* other) : x(other->x), y(other->y), z(other->z), w(1.0f) {}
    explicit vector4(const bx::Vec3& other, const float w) : x(other.x / w), y(other.y / w), z(other.z / w), w(1.0f) {}
    explicit vector4(const bx::Vec3* other, const float w) : x(other->x / w), y(other->y / w), z(other->z / w), w(1.0f) {}

    explicit vector4(const float other) : x(other), y(other), z(other), w(other) {}

    explicit vector4(const float* other) : x(other[0]), y(other[1]), z(other[2]), w(other[3]) {}
    explicit vector4(const float* other, const float w) : x(other[0] / w), y(other[1] / w), z(other[2] / w), w(other[3] / w) {}

    explicit vector4(const vector3& other) : x(other.x), y(other.y), z(other.z), w(1.0f) {}
    explicit vector4(const vector3* other) : x(other->x), y(other->y), z(other->z), w(1.0f) {}

    vector4(const vector4& other) = default;
    vector4(vector4&& other) = default;

    vector4& operator=(const vector4& other) = default;
    vector4& operator=(vector4&& other) = default;

    explicit operator bx::Vec3() const { return bx::Vec3{x, y, z}; }
    explicit operator bx::Vec3*() const { return new bx::Vec3{x, y, z}; }
    explicit operator bx::Vec3&() const { return *new bx::Vec3{x, y, z}; }

    explicit operator float*() const { return new float[4]{x, y, z, w}; }
    explicit operator float&() const { return *new float[4]{x, y, z, w}; }

    explicit operator vector3() const { return vector3{x, y, z}; }
    explicit operator vector3*() const { return new vector3{x, y, z}; }
    explicit operator vector3&() const { return *new vector3{x, y, z}; }

    vector4 operator+(const vector4& other) const { return vector4{x + other.x, y + other.y, z + other.z}; }
    vector4 operator-(const vector4& other) const { return vector4{x - other.x, y - other.y, z - other.z}; }
    vector4 operator*(const vector4& other) const { return vector4{x * other.x, y * other.y, z * other.z}; }
    vector4 operator/(const vector4& other) const { return vector4{x / other.x, y / other.y, z / other.z}; }

    vector4 operator+(const float other) const { return vector4{x + other, y + other, z + other}; }
    vector4 operator-(const float other) const { return vector4{x - other, y - other, z - other}; }
    vector4 operator*(const float other) const { return vector4{x * other, y * other, z * other}; }
    vector4 operator/(const float other) const { return vector4{x / other, y / other, z / other}; }
};

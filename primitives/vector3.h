#pragma once
#include <bx/math.h>

#include "vector3_i.h"

struct vector3
{
    float x;
    float y;
    float z;

    ~vector3() = default;
    bool operator==(const vector3& other) const
    {
        constexpr float epsilon = std::numeric_limits<float>::epsilon() * 10;
        
        if (std::fabs(x - other.x) > epsilon) return false;
        if (std::fabs(y - other.y) > epsilon) return false;
        if (std::fabs(z - other.z) > epsilon) return false;

        return true;
    }

    vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    
    explicit vector3(const bx::Vec3& other) : x(other.x), y(other.y), z(other.z) {}
    explicit vector3(const bx::Vec3* other) : x(other->x), y(other->y), z(other->z) {}
    explicit vector3(const bx::Vec3& other, const float w) : x(other.x / w), y(other.y / w), z(other.z / w) {}
    explicit vector3(const bx::Vec3* other, const float w) : x(other->x / w), y(other->y / w), z(other->z / w) {}

    explicit vector3(const float other) : x(other), y(other), z(other) {}

    explicit vector3(const float* other) : x(other[0]), y(other[1]), z(other[2]) {}
    explicit vector3(const float* other, const float w) : x(other[0] / w), y(other[1] / w), z(other[2] / w) {}

    explicit vector3(const vector3_i other) : x(static_cast<float>(other.x)), y(static_cast<float>(other.y)), z(static_cast<float>(other.z)) {}
    explicit vector3(const vector3_i* other) : x(static_cast<float>(other->x)), y(static_cast<float>(other->y)), z(static_cast<float>(other->z)) {}
    explicit vector3(const vector3_i other, const float w) : x(static_cast<float>(other.x) / w), y(static_cast<float>(other.y) / w), z(static_cast<float>(other.z) / w) {}
    explicit vector3(const vector3_i* other, const float w) : x(static_cast<float>(other->x) / w), y(static_cast<float>(other->y) / w), z(static_cast<float>(other->z) / w) {}
    
    vector3(const vector3& other) = default;
    vector3(vector3&& other) = default;

    vector3& operator=(const vector3& other) = default;
    vector3& operator=(vector3&& other) = default;

    explicit operator bx::Vec3() const { return bx::Vec3{x, y, z}; }
    explicit operator bx::Vec3*() const { return new bx::Vec3{x, y, z}; }
    explicit operator bx::Vec3&() const { return *new bx::Vec3{x, y, z}; }\

    explicit operator float*() const { return new float[3]{x, y, z}; }
    explicit operator float&() const { return *new float[3]{x, y, z}; }

    vector3 operator+(const vector3& other) const { return vector3{x + other.x, y + other.y, z + other.z}; }
    vector3 operator-(const vector3& other) const { return vector3{x - other.x, y - other.y, z - other.z}; }
    vector3 operator*(const vector3& other) const { return vector3{x * other.x, y * other.y, z * other.z}; }
    vector3 operator/(const vector3& other) const { return vector3{x / other.x, y / other.y, z / other.z}; }

    vector3 operator+=(const vector3& other) { return vector3{x += other.x, y += other.y, z += other.z}; }
    vector3 operator-=(const vector3& other) { return vector3{x -= other.x, y -= other.y, z -= other.z}; }
    vector3 operator*=(const vector3& other) { return vector3{x *= other.x, y *= other.y, z *= other.z}; }
    vector3 operator/=(const vector3& other) { return vector3{x /= other.x, y /= other.y, z /= other.z}; }

    vector3 operator+(const float other) const { return vector3{x + other, y + other, z + other}; }
    vector3 operator-(const float other) const { return vector3{x - other, y - other, z - other}; }
    vector3 operator*(const float other) const { return vector3{x * other, y * other, z * other}; }
    vector3 operator/(const float other) const { return vector3{x / other, y / other, z / other}; }

    vector3 operator+=(const float other) { return vector3{x += other, y += other, z += other}; }
    vector3 operator-=(const float other) { return vector3{x -= other, y -= other, z -= other}; }
    vector3 operator*=(const float other) { return vector3{x *= other, y *= other, z *= other}; }
    vector3 operator/=(const float other) { return vector3{x /= other, y /= other, z /= other}; }
};

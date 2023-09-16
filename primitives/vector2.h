#pragma once
#include <bx/math.h>

struct vector2
{
    float x;
    float y;

    ~vector2() = default;
    
    vector2() : x(0.0f), y(0.0f) {}
    vector2(const float x, const float y) : x(x), y(y) {}

    explicit vector2(const float other) : x(other), y(other) {}

    explicit vector2(const float* other) : x(other[0]), y(other[1]) {}
    explicit vector2(const float* other, const float w) : x(other[0] / w), y(other[1] / w) {}

    vector2(const vector2& other) = default;
    vector2(vector2&& other) = default;

    vector2& operator=(const vector2& other) = default;
    vector2& operator=(vector2&& other) = default;

    explicit operator bx::Vec3() const { return bx::Vec3{x, y, 0}; }
    explicit operator bx::Vec3*() const { return new bx::Vec3{x, y, 0}; }
    explicit operator bx::Vec3&() const { return *new bx::Vec3{x, y, 0}; }\

    explicit operator float*() const { return new float[]{x, y}; }
    explicit operator float&() const { return *new float[]{x, y}; }

    vector2 operator+(const vector2& other) const { return vector2{x + other.x, y + other.y}; }
    vector2 operator-(const vector2& other) const { return vector2{x - other.x, y - other.y}; }
    vector2 operator*(const vector2& other) const { return vector2{x * other.x, y * other.y}; }
    vector2 operator/(const vector2& other) const { return vector2{x / other.x, y / other.y}; }

    vector2 operator+=(const vector2& other) { return vector2{x += other.x, y += other.y}; }
    vector2 operator-=(const vector2& other) { return vector2{x -= other.x, y -= other.y}; }
    vector2 operator*=(const vector2& other) { return vector2{x *= other.x, y *= other.y}; }
    vector2 operator/=(const vector2& other) { return vector2{x /= other.x, y /= other.y}; }

    vector2 operator+(const float other) const { return vector2{x + other, y + other}; }
    vector2 operator-(const float other) const { return vector2{x - other, y - other}; }
    vector2 operator*(const float other) const { return vector2{x * other, y * other}; }
    vector2 operator/(const float other) const { return vector2{x / other, y / other}; }

    vector2 operator+=(const float other) { return vector2{x += other, y += other}; }
    vector2 operator-=(const float other) { return vector2{x -= other, y -= other}; }
    vector2 operator*=(const float other) { return vector2{x *= other, y *= other}; }
    vector2 operator/=(const float other) { return vector2{x /= other, y /= other}; }
};

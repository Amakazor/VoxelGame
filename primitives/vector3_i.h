#pragma once
#include <functional>

struct vector3_i
{
    int x;
    int y;
    int z;

    ~vector3_i() = default;
    
    vector3_i() : x(0), y(0), z(0) {}
    vector3_i(const int x, const int y, const int z) : x(x), y(y), z(z) {}

    explicit vector3_i(const int other) : x(other), y(other), z(other) {}

    explicit vector3_i(const int* other) : x(other[0]), y(other[1]), z(other[2]) {}
    explicit vector3_i(const int* other, const int w) : x(other[0] / w), y(other[1] / w), z(other[2] / w) {}
    
    vector3_i(const vector3_i& other) = default;
    vector3_i(vector3_i&& other) = default;

    vector3_i& operator=(const vector3_i& other) = default;
    vector3_i& operator=(vector3_i&& other) = default;

    explicit operator int*() const { return new int[3]{x, y, z}; }
    explicit operator int&() const { return *new int[3]{x, y, z}; }

    vector3_i operator+(const vector3_i& other) const { return vector3_i{x + other.x, y + other.y, z + other.z}; }
    vector3_i operator-(const vector3_i& other) const { return vector3_i{x - other.x, y - other.y, z - other.z}; }
    vector3_i operator*(const vector3_i& other) const { return vector3_i{x * other.x, y * other.y, z * other.z}; }
    vector3_i operator/(const vector3_i& other) const { return vector3_i{x / other.x, y / other.y, z / other.z}; }

    vector3_i operator+=(const vector3_i& other) { return vector3_i{x += other.x, y += other.y, z += other.z}; }
    vector3_i operator-=(const vector3_i& other) { return vector3_i{x -= other.x, y -= other.y, z -= other.z}; }
    vector3_i operator*=(const vector3_i& other) { return vector3_i{x *= other.x, y *= other.y, z *= other.z}; }
    vector3_i operator/=(const vector3_i& other) { return vector3_i{x /= other.x, y /= other.y, z /= other.z}; }

    vector3_i operator+(const int other) const { return vector3_i{x + other, y + other, z + other}; }
    vector3_i operator-(const int other) const { return vector3_i{x - other, y - other, z - other}; }
    vector3_i operator*(const int other) const { return vector3_i{x * other, y * other, z * other}; }
    vector3_i operator/(const int other) const { return vector3_i{x / other, y / other, z / other}; }

    vector3_i operator+=(const int other) { return vector3_i{x += other, y += other, z += other}; }
    vector3_i operator-=(const int other) { return vector3_i{x -= other, y -= other, z -= other}; }
    vector3_i operator*=(const int other) { return vector3_i{x *= other, y *= other, z *= other}; }
    vector3_i operator/=(const int other) { return vector3_i{x /= other, y /= other, z /= other}; }

    bool operator==(const vector3_i& other) const { return x == other.x && y == other.y && z == other.z; }
};

struct vector3_i_hasher
{
    std::size_t operator()(const vector3_i& vector) const
    {
        return std::hash<int>()(vector.x) ^ std::hash<int>()(vector.y) ^ std::hash<int>()(vector.z);
    }
};
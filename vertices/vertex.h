#pragma once
#include <cstdint>
#include "../primitives/vector3.h"

struct vertex_positioned_colored
{
    vector3 position;
    uint32_t color;

    vertex_positioned_colored() = default;
    vertex_positioned_colored(const vector3& position, const uint32_t abgr) : position(position), color(abgr) {}
    
    vertex_positioned_colored(const float x, const float y, const float z, const uint32_t abgr) : position(vector3{x, y, z}), color(uint32_t{abgr}) {}

    explicit vertex_positioned_colored(const vector3& position) : position(position), color(0xFFFFFFFF) {}
    vertex_positioned_colored(const float x, const float y, const float z) : position(vector3{x, y, z}), color(0xFFFFFFFF) {}
};

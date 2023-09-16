#pragma once

#include "vector3.h"

struct transform
{
    transform() : scale(1.0f) {}
    transform(const vector3 position, const vector3 rotation, const vector3 scale) : position(position), rotation(rotation), scale(scale) {}
    transform(const vector3 position, const vector3 rotation) : position(position), rotation(rotation), scale(1.0f) {}
    explicit transform(const vector3 position) : position(position), scale(1.0f) {}

    void move_local(const vector3& movement);
    void move_global(const vector3& movement);

    void rotate(const vector3& rot);
    void rotate_clamped_x(const vector3& rot);
    
    void rescale(const vector3& scl);
    
    vector3 position;
    vector3 rotation;
    vector3 scale;
};

#pragma once
#include "vector3.h"
#include "vector3_i.h"

struct quad
{
    vector3_i a;
    vector3_i b;
    vector3_i c;
    vector3_i d;

    [[nodiscard]] std::vector<vector3> to_triangles() const;

    [[nodiscard]] quad reversed() const;
    
    bool operator==(const quad& other) const;
};

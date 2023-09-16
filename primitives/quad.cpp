#include "quad.h"

std::vector<vector3> quad::to_triangles() const
{
    std::vector<vector3> triangles;
    triangles.reserve(6);

    triangles.emplace_back(a);
    triangles.emplace_back(b);
    triangles.emplace_back(c);

    triangles.emplace_back(a);
    triangles.emplace_back(c);
    triangles.emplace_back(d);

    return triangles;
}

quad quad::reversed() const
{
    return quad{d, c, b, a};
}

bool quad::operator==(const quad& other) const
{
    return (a == other.a && b == other.b && c == other.c && d == other.d)
        || (a == other.b && b == other.c && c == other.d && d == other.a)
        || (a == other.c && b == other.d && c == other.a && d == other.b)
        || (a == other.d && b == other.a && c == other.b && d == other.c);
}

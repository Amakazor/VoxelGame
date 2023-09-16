#pragma once
#include "message.h"

struct mouse_message final : message
{
    double x;
    double y;

    double dx;
    double dy;

    bool raw;

    mouse_message(const double x, const double y, const double dx, const double dy, const bool raw) : x(x), y(y), dx(dx), dy(dy), raw(raw) {}
};

#pragma once

#include "../primitives/quad.h"
#include "../primitives/vector3_i.h"

class block
{
    vector3_i position_;
    std::vector<quad> faces_;
public:
    explicit block(const vector3_i& position);

    [[nodiscard]] const vector3_i& position() const;
    [[nodiscard]] const std::vector<quad>& faces() const;
};

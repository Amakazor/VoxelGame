#pragma once
#include "primitives/transform.h"

class camera
{
    float view_[16];
    float proj_[16];

    float width_;
    float height_;

    bool is_transform_matrix_dirty_ = true;
    
public:
    transform object_transform{};
    
    camera(float width, float height);

    void mark_transform_matrix_dirty() {is_transform_matrix_dirty_ = true;}
    
    void set_view();
    void recalculate_projection(float width, float height);

    void tick(float delta_time);
    
private:
    void recalculate_view();
};

#include "camera.h"
#include "bx/math.h"
#include <bgfx/bgfx.h>

#include "handlers/input_handler.h"

camera::camera(const float width, const float height)
{
    width_ = width;
    height_ = height;
    
    recalculate_view();
    recalculate_projection(width, height);
}

void camera::set_view()
{
    if (is_transform_matrix_dirty_) recalculate_view();
    bgfx::setViewTransform(0, view_, proj_);
}

void camera::recalculate_projection(const float width, const float height)
{
    width_ = width;
    height_ = height;
    
    bx::mtxProj(proj_, 90.0f, width / height, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
}

void camera::tick(const float delta_time)
{
    const float forward_input = input_handler::get_instance()->get_input(forward) * delta_time * 5.0f;
    const float horizontal_input = input_handler::get_instance()->get_input(horizontal) * delta_time * 5.0f;
    const float vertical_input = input_handler::get_instance()->get_input(vertical) * delta_time * 5.0f;

    const float mouse_x_input = input_handler::get_instance()->get_input(mouse_x) * 0.005f;
    const float mouse_y_input = input_handler::get_instance()->get_input(mouse_y) * 0.005f;

    
    object_transform.move_local({0.0f, 0.0f, forward_input});
    object_transform.move_local({horizontal_input, 0.0f, 0.0f});
    object_transform.move_local({0.0f, vertical_input, 0.0f});

    object_transform.rotate_clamped_x({-mouse_y_input, -mouse_x_input, 0.0f});

    mark_transform_matrix_dirty();
}

void camera::recalculate_view()
{
    const vector3 look_from = object_transform.position;
    constexpr float forward[4] = {0.0f, 0.0f, 1.0f, 1.0f};
    float look_at_4[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    float rotation_matrix[16];
    bx::mtxRotateXYZ(rotation_matrix, object_transform.rotation.x, object_transform.rotation.y, object_transform.rotation.z);
    
    bx::vec4MulMtx(look_at_4, forward, rotation_matrix);
    
    const auto look_at = bx::Vec3{look_at_4[0] * 5.0f + look_from.x, look_at_4[1] * 5.0f + look_from.y, look_at_4[2] * 5.0f + look_from.z};
    
    bx::mtxLookAt(view_, static_cast<bx::Vec3&>(look_from), look_at);

    is_transform_matrix_dirty_ = false;
}

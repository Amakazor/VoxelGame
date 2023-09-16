#include "transform.h"

#include <float.h>

#include "vector3.h"
#include "vector4.h"

void transform::move_local(const vector3& movement)
{
    const vector4 movement_4(movement);
    float rotated_movement[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    float rotation_matrix[16];
    bx::mtxRotateXYZ(rotation_matrix, rotation.x, rotation.y, rotation.z);
    
    bx::vec4MulMtx(rotated_movement, static_cast<const float*>(movement_4), rotation_matrix);

    position += vector3{rotated_movement};
}

void transform::move_global(const vector3& movement)
{
    position += movement;
}

void transform::rotate(const vector3& rot)
{
    rotation += rot;
}

void transform::rotate_clamped_x(const vector3& rot)
{
    vector3 new_rot = rotation + rot;
    new_rot.x = bx::clamp(new_rot.x, -bx::kPiHalf + 1000 * FLT_EPSILON, bx::kPiHalf - 1000 * FLT_EPSILON);
    rotation = new_rot;
}

void transform::rescale(const vector3& scl)
{
    scale *= scl;
}

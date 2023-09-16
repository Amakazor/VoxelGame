#include "positioned.h"
#include "bx/math.h"

float* positioned::get_transform_matrix()
{
    if (is_transform_matrix_dirty_)
    {
        update_transform_matrix();
        is_transform_matrix_dirty_ = false;
    }

    return transform_matrix_;
}

void positioned::mark_transform_matrix_dirty()
{
    is_transform_matrix_dirty_ = true;
    for (const auto& child : children_)
    {
        child->mark_transform_matrix_dirty();
    }
}

void positioned::set_parent(const std::shared_ptr<positioned>& parent)
{
    parent_ = parent;
    parent->add_child(shared_from_this());
}

void positioned::update_transform_matrix()
{
    float translation_matrix[16];
    float rotation_matrix[16];
    float scale_matrix[16];

    bx::mtxTranslate(translation_matrix, object_transform.position.x, object_transform.position.y, object_transform.position.z);
    bx::mtxRotateXYZ(rotation_matrix, object_transform.rotation.x, object_transform.rotation.y, object_transform.rotation.z);
    bx::mtxScale(scale_matrix, object_transform.scale.x, object_transform.scale.y, object_transform.scale.z);

    float temporary_a[16];
    float temporary_b[16];
    bx::mtxIdentity(temporary_a);
    
    bx::mtxMul(temporary_b, temporary_a, scale_matrix);
    bx::mtxMul(temporary_a, temporary_b, rotation_matrix);
    bx::mtxMul(temporary_b, temporary_a, translation_matrix);

    if (parent_)
    {
        bx::mtxMul(transform_matrix_, temporary_b, parent_->get_transform_matrix());
    }
    else
    {
        for (int i = 0; i < 16; i++)
        {
            transform_matrix_[i] = temporary_b[i];
        }
    }
}

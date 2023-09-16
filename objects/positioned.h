#pragma once
#include <memory>
#include <vector>

#include "../primitives/transform.h"

class positioned : public std::enable_shared_from_this<positioned>
{
protected:
    float transform_matrix_[16] = {};
    bool is_transform_matrix_dirty_ = true;
    std::shared_ptr<positioned> parent_;
    std::vector<std::shared_ptr<positioned>> children_;
    
public:
    transform object_transform;
    
    explicit positioned(transform object_transform) : object_transform(object_transform) {}
    positioned() : object_transform(vector3(0.0f), vector3(0.0f), vector3(1.0f)) {}
    
    virtual ~positioned() = default;
    
    [[nodiscard]] float * get_transform_matrix();
    
    void mark_transform_matrix_dirty();

    void set_parent(const std::shared_ptr<positioned>& parent);
    [[nodiscard]] std::shared_ptr<positioned> get_parent() const { return parent_; }

    void add_child(const std::shared_ptr<positioned>& child) { children_.push_back(child); }
    [[nodiscard]] std::vector<std::shared_ptr<positioned>> get_children() const { return children_; }

protected:
    void update_transform_matrix();
};

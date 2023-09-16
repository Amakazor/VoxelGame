#pragma once
#include <memory>

class mesh;
class shader_program;

class drawable
{
protected:
    std::shared_ptr<mesh> mesh_;
    std::shared_ptr<shader_program> shader_program_;
    
public:
    virtual ~drawable() = default;
    drawable(const std::shared_ptr<mesh>& mesh, const std::shared_ptr<shader_program>& shader_program);

    [[nodiscard]] std::shared_ptr<mesh> get_mesh() const { return mesh_; }
    [[nodiscard]] std::shared_ptr<shader_program> get_shader_program() const { return shader_program_; }
    
    virtual void draw();
};

#include "object.h"

object::object(const std::shared_ptr<mesh>& mesh, const std::shared_ptr<shader_program>& shader_program,
    const transform& transform): positioned(transform), drawable(mesh, shader_program) {}

object::object(const std::shared_ptr<mesh>& mesh, const std::shared_ptr<shader_program>& shader_program):
    drawable(mesh, shader_program) {}

void object::draw()
{
    bgfx::setTransform(get_transform_matrix());
    bgfx::setVertexBuffer(0, mesh_->get_vbh());
    bgfx::setIndexBuffer(mesh_->get_ibh());
    bgfx::setState(BGFX_STATE_DEFAULT);

    bgfx::submit(0, shader_program_->get_program_handle());
}


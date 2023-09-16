#include "drawable.h"

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <../meshes/mesh.h>
#include <../shader_program.h>

drawable::drawable(const std::shared_ptr<mesh>& mesh, const std::shared_ptr<shader_program>& shader_program)
{
    mesh_ = mesh;
    shader_program_ = shader_program;
}

void drawable::draw()
{
    if (mesh_ == nullptr || shader_program_ == nullptr) return;
    if (mesh_->get_vbh().idx == bgfx::kInvalidHandle || mesh_->get_ibh().idx == bgfx::kInvalidHandle) return;
    
    float transform_matrix[16];
    bx::mtxIdentity(transform_matrix);
    
    bgfx::setTransform(transform_matrix);
    bgfx::setVertexBuffer(0, mesh_->get_vbh());
    bgfx::setIndexBuffer(mesh_->get_ibh());
    bgfx::setState(BGFX_STATE_DEFAULT);

    bgfx::submit(0, shader_program_->get_program_handle());
}

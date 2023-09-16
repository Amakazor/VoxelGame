#pragma once
#include <bgfx/bgfx.h>
#include "mesh.h"

struct vertex_positioned_colored;

class colored_mesh final : public mesh
{
    vertex_positioned_colored* vertices_;
    uint16_t* indices_;
    
    bgfx::VertexBufferHandle m_vbh_;
    bgfx::IndexBufferHandle m_ibh_;
public:
    colored_mesh(const vertex_positioned_colored* vertices, const uint16_t* indices, uint16_t sizeof_vertices, uint16_t sizeof_indices);
    ~colored_mesh() override;
    
    [[nodiscard]] bgfx::VertexBufferHandle get_vbh() const override { return m_vbh_; }
    [[nodiscard]] bgfx::IndexBufferHandle get_ibh() const override { return m_ibh_; }
};

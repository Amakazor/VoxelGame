#include "colored_mesh.h"

#include <iostream>
#include "../vertices/vertex.h"

colored_mesh::colored_mesh(const vertex_positioned_colored* vertices, const uint16_t* indices, const uint16_t sizeof_vertices, const uint16_t sizeof_indices):
    m_vbh_(BGFX_INVALID_HANDLE),
    m_ibh_(BGFX_INVALID_HANDLE)
{
    vertices_ = new vertex_positioned_colored[sizeof_vertices];
    indices_ = new uint16_t[sizeof_indices];
    
    bgfx::VertexLayout layout;
    layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
    
    m_vbh_ = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof_vertices), layout);
    m_ibh_ = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof_indices));
}

colored_mesh::~colored_mesh()
{
    std::cout << "colored_mesh::~colored_mesh()" << std::endl;
    delete[] vertices_;
    delete[] indices_;
}

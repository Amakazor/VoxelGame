#pragma once
#include <bgfx/bgfx.h>

class mesh
{
public:
    virtual ~mesh();
    [[nodiscard]] virtual bgfx::VertexBufferHandle get_vbh() const = 0;
    [[nodiscard]] virtual bgfx::IndexBufferHandle get_ibh() const = 0;

    // inline static const std::shared_ptr<mesh> NONE = {};
};
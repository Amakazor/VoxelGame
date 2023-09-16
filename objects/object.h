#pragma once

#include "drawable.h"
#include "positioned.h"
#include "../shader_program.h"
#include "../meshes/mesh.h"
#include "../primitives/transform.h"

class object : public positioned, public drawable
{
public:
    object(const std::shared_ptr<mesh>& mesh, const std::shared_ptr<shader_program>& shader_program, const transform& transform);
    object(const std::shared_ptr<mesh>& mesh, const std::shared_ptr<shader_program>& shader_program);

    void draw() override;
};

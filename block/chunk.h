#pragma once
#include <memory>
#include <vector>

#include "../shader_program.h"
#include "../objects/drawable.h"
#include "../primitives/vector3_i.h"
#include "../primitives/quad.h"

struct vertex_positioned_colored;
class block;

class chunk final : public drawable
{
    vector3_i position_;
    std::shared_ptr<std::vector<std::vector<std::vector<std::shared_ptr<block>>>>> blocks_ = std::make_shared<std::vector<std::vector<std::vector<std::shared_ptr<block>>>>>(chunk_size, std::vector(chunk_size, std::vector<std::shared_ptr<block>>(chunk_size, nullptr)));

    static int is_quad_duplicated(const quad& quad, const std::vector<::quad>& quads);
    static int is_vertex_duplicated(vector3 vertex, const std::vector<vertex_positioned_colored>& vertices);
    void generate_mesh();
    
public:
    static constexpr int chunk_size = 16;

    explicit chunk(const vector3_i& position) : drawable(nullptr, std::make_shared<shader_program>("./resources/shaders/build/simple/vs_cubes.bin","./resources/shaders/build/simple/fs_cubes.bin")), position_(position) {}

    [[nodiscard]] vector3_i position() const;
    [[nodiscard]] std::shared_ptr<std::vector<std::vector<std::vector<std::shared_ptr<block>>>>> blocks() const;

    bool add_block(const vector3_i& position, bool update_mesh = true);
};

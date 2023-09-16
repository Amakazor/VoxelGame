#include "chunk.h"

#include <set>

#include "block.h"
#include "../meshes/colored_mesh.h"
#include "../vertices/vertex.h"

bool chunk::add_block(const vector3_i& position, const bool update_mesh)
{
    if (position.x < 0 || position.x >= chunk_size || position.y < 0 || position.y >= chunk_size || position.z < 0 || position.z >= chunk_size)return false;
    if (blocks_->operator[](position.x)[position.y][position.z] != nullptr)return false;

    blocks_->operator[](position.x)[position.y][position.z] = std::make_shared<block>(position);
    if (update_mesh) generate_mesh();

    return true;
}

int chunk::is_quad_duplicated(const quad& quad, const std::vector<::quad>& quads)
{
    const ::quad reversed = quad.reversed();

    const int size = quads.size();  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-shorten-64-to-32, cppcoreguidelines-narrowing-conversions)
    for (int i = 0; i < size; i++)
    {
        if (quads[i] == quad || quads[i] == reversed)return i;
    }

    return -1;
}

int chunk::is_vertex_duplicated(const vector3 vertex, const std::vector<vertex_positioned_colored>& vertices)
{
    const int size = vertices.size();  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-shorten-64-to-32, cppcoreguidelines-narrowing-conversions)
    for (int i = 0; i < size; i++)
    {
        if (vertices[i].position == vertex) return i;
    }
    return -1;
}

void chunk::generate_mesh()
{
    std::vector<quad> quads;
    std::set<int> ignored_quads;

    quads.reserve(6 * chunk_size * chunk_size * chunk_size);  // NOLINT(bugprone-implicit-widening-of-multiplication-result)

    for (int x = 0; x < chunk_size; x++)
    {
        for (int y = 0; y < chunk_size; y++)
        {
            for (int z = 0; z < chunk_size; z++)
            {
                if (blocks_->operator[](x)[y][z] == nullptr)continue;

                for (const auto& face : blocks_->operator[](x)[y][z]->faces())
                {
                    if (int duplicated = is_quad_duplicated(face, quads); duplicated != -1)
                    {
                        ignored_quads.insert(duplicated);
                        continue;
                    }
                    
                    quads.emplace_back(face);
                }
            }
        }
    }

    std::vector<vertex_positioned_colored> vertices;
    std::vector<uint16_t> indices;

    const int size = quads.size();  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-shorten-64-to-32, cppcoreguidelines-narrowing-conversions)
    for (int i = 0; i < size; i++)
    {
        if (ignored_quads.contains(i)) continue;

        for (const std::vector<vector3> triangles = quads[i].to_triangles(); const auto& vertex : triangles)
        {
            if (const int duplicated = is_vertex_duplicated(vertex, vertices); duplicated != -1)
            {
                indices.emplace_back(duplicated);
                continue;
            }

            vertices.emplace_back(vertex, 0xff'aa'aa'aa);
            indices.emplace_back(vertices.size() - 1);
        }
    }

    auto* vertices_array = new vertex_positioned_colored[vertices.size()];
    auto* indices_array = new uint16_t[indices.size()];
    std::ranges::copy(vertices, vertices_array);
    std::ranges::copy(indices, indices_array);

    mesh_ = std::make_shared<colored_mesh>(vertices_array, indices_array, vertices.size() * sizeof vertex_positioned_colored, indices.size() * sizeof uint16_t);
}

vector3_i chunk::position() const
{
    return position_;
}

std::shared_ptr<std::vector<std::vector<std::vector<std::shared_ptr<block>>>>> chunk::blocks() const
{
    return blocks_;
}

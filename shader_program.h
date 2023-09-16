#pragma once
#include <bgfx/bgfx.h>

class shader_program
{
    bgfx::ProgramHandle m_program_handle_;
public:
    shader_program(const char* vertex_shader_file, const char* fragment_shader_file);

    [[nodiscard]] bgfx::ProgramHandle get_program_handle() const { return m_program_handle_; }

private:
    static bgfx::ShaderHandle load_shader(const char* shader_file);
    [[nodiscard]] bgfx::ProgramHandle create_program(const bgfx::ShaderHandle vertex_shader, const bgfx::ShaderHandle fragment_shader) const;
};

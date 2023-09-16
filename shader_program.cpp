// ReSharper disable CppClangTidyCertErr33C
#include "shader_program.h"

#include <cstdio>
#include <iostream>

shader_program::shader_program(const char* vertex_shader_file, const char* fragment_shader_file) : m_program_handle_(BGFX_INVALID_HANDLE)
{
    const bgfx::ShaderHandle vertex_shader = load_shader(vertex_shader_file);
    const bgfx::ShaderHandle fragment_shader = load_shader(fragment_shader_file);

    m_program_handle_ = create_program(vertex_shader, fragment_shader);
    std::cout << "Program handle: " << m_program_handle_.idx << std::endl;
}

bgfx::ShaderHandle shader_program::load_shader(const char* shader_file)
{
    FILE *file;

    if (const errno_t err = fopen_s(&file, shader_file, "rb"); err != 0)
    {
        return BGFX_INVALID_HANDLE;
    }

    fseek(file, 0, SEEK_END);
    const int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    const bgfx::Memory* mem = bgfx::alloc(file_size + 1);
    
    fread(mem->data, 1, file_size, file);
    
    mem->data[mem->size - 1] = '\0';
    fclose(file);
    
    return bgfx::createShader(mem);
}

bgfx::ProgramHandle shader_program::create_program(const bgfx::ShaderHandle vertex_shader, const bgfx::ShaderHandle fragment_shader) const
{
    return bgfx::createProgram(vertex_shader, fragment_shader, true);
}

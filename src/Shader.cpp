#include <glad/gl.h>
#include "Shader.h"

#include "utility/logger.h"
#include "utility/pgmath.h"

#include <fstream>

namespace pg
{

    GLenum to_gl_shader_type(const EShaderType &type)
    {
        switch (type)
        {
        case EShaderType::VERTEX:
            return GL_VERTEX_SHADER;

        case EShaderType::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        }

        return GL_VERTEX_SHADER;
    }

    void compile(unsigned int id, EShaderType type)
    {
        glCompileShader(id);

        // Report any errors
        int success;
        char log[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, nullptr, log);
            pg::log::error("[Shader({})]: Compilation failed.\n{}", type, log);
        }
    }

    void destroy_shader(unsigned int id)
    {
        glDeleteShader(id);
    }

    unsigned int create_shader_from_source(const std::string &filename, EShaderType type)
    {
        unsigned int id = glCreateShader(to_gl_shader_type(type));

        // Read contents
        std::ifstream ifs(filename);
        std::string source((std::istreambuf_iterator<char>(ifs)),
                           (std::istreambuf_iterator<char>()));

        const char *p_source = source.c_str();

        // Attach and compile the code for it
        // A nullptr as length (last parameter) indicates that each string passed is
        // supposed to be null-terminated
        glShaderSource(id, 1, &p_source, nullptr);

        return id;
    }

    Shader::Shader(const ShaderConfig &conf) : _conf(conf)
    {
        // Create the shader object
        _id = create_shader_from_source(_conf.filename, _conf.type);
        compile(_id, _conf.type);
    }

    Shader::~Shader()
    {
        destroy_shader(_id);
    }

    void Shader::attach_to_program(unsigned int program_id) const
    {
        glAttachShader(program_id, _id);
    }

    void Shader::detach_from_program(unsigned int program_id) const
    {
        glDetachShader(program_id, _id);
    }

    void Shader::reload()
    {
        destroy_shader(_id);
        _id = create_shader_from_source(_conf.filename, _conf.type);
        compile(_id, _conf.type);
    }
} // namespace pg

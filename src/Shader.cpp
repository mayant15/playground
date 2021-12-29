#include <glad/gl.h>
#include "Shader.h"
#include "utility/logger.h"

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

    Shader::Shader(const ShaderConfig &conf) : _conf(conf)
    {
        // Create the shader object
        _id = glCreateShader(to_gl_shader_type(conf.type));

        // Read contents
        std::ifstream ifs(conf.filename);
        std::string source((std::istreambuf_iterator<char>(ifs)),
                           (std::istreambuf_iterator<char>()));

        const char *p_source = source.c_str();

        // Attach and compile the code for it
        // A nullptr as length (last parameter) indicates that each string passed is
        // supposed to be null-terminated
        glShaderSource(_id, 1, &p_source, nullptr);

        compile();
    }

    Shader::~Shader()
    {
        glDeleteShader(_id);
    }

    void Shader::compile() const
    {
        glCompileShader(_id);

        // Report any errors
        int success;
        char log[512];
        glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(_id, 512, nullptr, log);
            pg::log::error("[Shader({})]: Compilation failed.\n{}", _conf.type, log);
        }
    }

    void Shader::attach_to_program(unsigned int program_id) const
    {
        glAttachShader(program_id, _id);
    }

    ShaderProgram::ShaderProgram(const std::vector<Shader *> &shaders)
    {
        _id = glCreateProgram();
        for (const auto *shader : shaders)
        {
            shader->attach_to_program(_id);
        }

        glLinkProgram(_id);

        // Report errors
        int success;
        char log[512];
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(_id, 512, nullptr, log);
            pg::log::error("[Shader({})]: Program linking failed for shaders");
            for (const auto *shader : shaders)
            {
                pg::log::error("\t{}", *shader);
            }
        }
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(_id);
    }

    void ShaderProgram::use() const
    {
        glUseProgram(_id);
    }

    void ShaderProgram::set_vec3f(const std::string &name, const glm::vec3 &vec) const
    {
        const int loc = glGetUniformLocation(_id, name.c_str());
        glUniform3f(loc, vec.x, vec.y, vec.z);
    }

} // namespace pg
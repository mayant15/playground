#include "ShaderProgramImpl.h"
#include "utility/logger.h"
#include "utility/pgmath.h"
#include <glm/gtc/type_ptr.hpp>

namespace pg
{
    void link(SRef<Shader> vertex, SRef<Shader> fragment, unsigned int id)
    {
        vertex->attach_to_program(id);
        fragment->attach_to_program(id);

        glLinkProgram(id);

        // Report errors
        int success;
        char log[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, nullptr, log);
            pg::log::error("[Shader]: Program linking failed for shaders\n{}\n{}\n{}", *vertex, *fragment, log);
        }
    }

    ShaderProgramImpl::ShaderProgramImpl(SRef<Shader> vertex, SRef<Shader> fragment)
        : _vertex(vertex), _fragment(fragment)
    {
        _id = glCreateProgram();
        link(_vertex, _fragment, _id);
    }

    ShaderProgramImpl::~ShaderProgramImpl()
    {
        glDeleteProgram(_id);
    }

    void ShaderProgramImpl::use() const
    {
        glUseProgram(_id);
    }

    void ShaderProgramImpl::reload()
    {
        _vertex->detach_from_program(_id);
        _vertex->reload();

        _fragment->detach_from_program(_id);
        _fragment->reload();

        link(_vertex, _fragment, _id);
    }

    void ShaderProgramImpl::set_vec3f(const std::string &name, const glm::vec3 &vec) const
    {
        const int loc = glGetUniformLocation(_id, name.c_str());
        glUniform3f(loc, XYZ(vec));
    }

    void ShaderProgramImpl::set_color(const std::string &name, const Color &color) const
    {
        const int loc = glGetUniformLocation(_id, name.c_str());
        glUniform4f(loc, XYZW(color));
    }

    void ShaderProgramImpl::set_mat4f(const std::string &name, const glm::mat4 &mat) const
    {
        const int loc = glGetUniformLocation(_id, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }
} // namespace pg

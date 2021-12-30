#include "ShaderProgramImpl.h"
#include "utility/logger.h"
#include "utility/pgmath.h"

namespace pg
{
    ShaderProgramImpl::ShaderProgramImpl(const Shader &vertex, const Shader &fragment)
    {
        _id = glCreateProgram();
        vertex.attach_to_program(_id);
        fragment.attach_to_program(_id);

        glLinkProgram(_id);

        // Report errors
        int success;
        char log[512];
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(_id, 512, nullptr, log);
            pg::log::error("[Shader({})]: Program linking failed for shaders\n{}\n{}", vertex, fragment);
        }
    }

    ShaderProgramImpl::~ShaderProgramImpl()
    {
        glDeleteProgram(_id);
    }

    void ShaderProgramImpl::use() const
    {
        glUseProgram(_id);
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
} // namespace pg

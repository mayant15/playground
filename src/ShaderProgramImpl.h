#pragma once

#include "Shader.h"

namespace pg
{
    class ShaderProgramImpl
    {
    public:
        ShaderProgramImpl(const Shader &vertex, const Shader &fragment);
        ~ShaderProgramImpl();

        void use() const;
        void set_vec3f(const std::string &name, const glm::vec3 &vec) const;
        void set_color(const std::string &name, const Color &color) const;

    private:
        unsigned int _id;
    };
} // namespace pg

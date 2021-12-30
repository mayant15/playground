#pragma once

#include "Shader.h"

namespace pg
{
    class ShaderProgramImpl
    {
    public:
        ShaderProgramImpl(SRef<Shader> vertex, SRef<Shader> fragment);
        ~ShaderProgramImpl();

        void use() const;
        void reload();
        void set_vec3f(const std::string &name, const glm::vec3 &vec) const;
        void set_mat4f(const std::string &name, const glm::mat4 &mat) const;
        void set_color(const std::string &name, const Color &color) const;

    private:
        unsigned int _id;
        SRef<Shader> _vertex;
        SRef<Shader> _fragment;
    };
} // namespace pg

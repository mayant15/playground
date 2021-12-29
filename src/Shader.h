#pragma once

#include <string>
#include <vector>

#include "utility/logger.h"
#include <glm/glm.hpp>

namespace pg
{

    constexpr unsigned int VERTEX_POSITION_LAYOUT_INDEX = 0;

    enum class EShaderType
    {
        VERTEX,
        FRAGMENT
    };

    template <typename OStream>
    inline OStream &operator<<(OStream &os, EShaderType value)
    {
        switch (value)
        {
        case EShaderType::VERTEX:
            os << "VERTEX";
            break;
        case EShaderType::FRAGMENT:
            os << "FRAGMENT";
            break;
        };
        return os;
    }

    struct ShaderConfig
    {
        std::string filename = "";
        EShaderType type = EShaderType::VERTEX;
    };

    class Shader
    {
    public:
        Shader(const ShaderConfig &conf);
        ~Shader();

        void reload();

        void attach_to_program(unsigned int program_id) const;

        template <typename OStream>
        friend inline OStream &operator<<(OStream &os, const Shader &shader)
        {
            return os << shader._conf.filename;
        }

    private:
        unsigned int _id;
        ShaderConfig _conf;

        void compile() const;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram(const std::vector<Shader *> &shaders);
        ~ShaderProgram();

        void use() const;
        void set_vec3f(const std::string &name, const glm::vec3 &vec) const;

    private:
        unsigned int _id;
    };
} // namespace pg

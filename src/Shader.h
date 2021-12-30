#pragma once

#include "base.h"

namespace pg
{
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
        void detach_from_program(unsigned int program_id) const;

        template <typename OStream>
        friend inline OStream &operator<<(OStream &os, const Shader &shader)
        {
            return os << "(" << shader._conf.type << ") " << shader._conf.filename;
        }

    private:
        unsigned int _id;
        ShaderConfig _conf;
    };
} // namespace pg

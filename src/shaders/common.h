#pragma once

#include <ShaderProgramImpl.h>

#define PG_DEFINE_UNIFORMS(...) void set_uniforms(__VA_ARGS__) const

#define PG_DEFINE_VERTEX_SHADER(FILE)                    \
    pg::ShaderConfig vertex_shader_config{};             \
    vertex_shader_config.filename = FILE;                \
    vertex_shader_config.type = pg::EShaderType::VERTEX; \
    pg::SRef<pg::Shader> vertex_shader = std::make_shared<pg::Shader>(vertex_shader_config);

#define PG_DEFINE_FRAGMENT_SHADER(FILE)                      \
    pg::ShaderConfig fragment_shader_config{};               \
    fragment_shader_config.filename = FILE;                  \
    fragment_shader_config.type = pg::EShaderType::FRAGMENT; \
    pg::SRef<pg::Shader> fragment_shader = std::make_shared<pg::Shader>(fragment_shader_config);

#define PG_DEFINE_SHADER(NAME, VERTEX, FRAGMENT, UNIFORM_FUNCTION)                           \
    class NAME                                                                               \
    {                                                                                        \
    public:                                                                                  \
        NAME()                                                                               \
        {                                                                                    \
            VERTEX                                                                           \
            FRAGMENT                                                                         \
            _impl = std::make_unique<pg::ShaderProgramImpl>(vertex_shader, fragment_shader); \
        }                                                                                    \
        UNIFORM_FUNCTION                                                                     \
        void use() const                                                                     \
        {                                                                                    \
            _impl->use();                                                                    \
        }                                                                                    \
        void reload()                                                                        \
        {                                                                                    \
            _impl->reload();                                                                 \
        }                                                                                    \
                                                                                             \
    private:                                                                                 \
        pg::URef<pg::ShaderProgramImpl> _impl;                                               \
    };

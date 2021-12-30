#pragma once

#include <ShaderProgramImpl.h>

#define PG_DEFINE_UNIFORMS(PARAMS) void set_uniforms(PARAMS) const

#define PG_DEFINE_VERTEX_SHADER(FILE)                    \
    pg::ShaderConfig vertex_shader_config{};             \
    vertex_shader_config.filename = FILE;                \
    vertex_shader_config.type = pg::EShaderType::VERTEX; \
    pg::Shader vertex_shader{vertex_shader_config};

#define PG_DEFINE_FRAGMENT_SHADER(FILE)                      \
    pg::ShaderConfig fragment_shader_config{};               \
    fragment_shader_config.filename = FILE;                  \
    fragment_shader_config.type = pg::EShaderType::FRAGMENT; \
    pg::Shader fragment_shader{fragment_shader_config};

#define PG_DEFINE_SHADER(NAME, VERTEX, FRAGMENT, UNIFORM_FUNCTION)             \
    class NAME                                                                 \
    {                                                                          \
    public:                                                                    \
        NAME()                                                                 \
        {                                                                      \
            VERTEX                                                             \
            FRAGMENT                                                           \
            _impl = new pg::ShaderProgramImpl{vertex_shader, fragment_shader}; \
        }                                                                      \
        ~NAME()                                                                \
        {                                                                      \
            delete _impl;                                                      \
        }                                                                      \
        UNIFORM_FUNCTION                                                       \
        void use() const                                                       \
        {                                                                      \
            _impl->use();                                                      \
        }                                                                      \
                                                                               \
    private:                                                                   \
        const pg::ShaderProgramImpl *_impl = nullptr;                          \
    };

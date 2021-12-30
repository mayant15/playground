#pragma once

#include "common.h"

namespace pg::shaders
{
    PG_DEFINE_SHADER(
        SolidShader,
        PG_DEFINE_VERTEX_SHADER("D:\\code\\graphics\\playground\\src\\shaders\\glsl\\mvp.vert"),
        PG_DEFINE_FRAGMENT_SHADER("D:\\code\\graphics\\playground\\src\\shaders\\glsl\\solid_color.frag"),
        PG_DEFINE_UNIFORMS(
            const Color &fill_color,
            const glm::mat4 &model,
            const glm::mat4 &view,
            const glm::mat4 &projection)
        {
            _impl->set_color("fill_color", fill_color);
            _impl->set_mat4f("u_model", model);
            _impl->set_mat4f("u_view", view);
            _impl->set_mat4f("u_projection", projection);
        })
} // namespace pg::shaders

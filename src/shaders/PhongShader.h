#pragma once

#include "common.h"

namespace pg::shaders
{
    PG_DEFINE_SHADER(
        PhongShader,
        PG_DEFINE_VERTEX_SHADER("D:\\code\\graphics\\playground\\src\\shaders\\glsl\\mvp.vert"),
        PG_DEFINE_FRAGMENT_SHADER("D:\\code\\graphics\\playground\\src\\shaders\\glsl\\phong.frag"),
        PG_DEFINE_UNIFORMS(
            const Color &ambient,
            const Color &albedo,
            const glm::vec3 &light_pos,
            const glm::mat4 &model,
            const glm::mat4 &view,
            const glm::mat4 &projection)
        {
            _impl->set_color("u_ambient", ambient);
            _impl->set_color("u_albedo", albedo);
            _impl->set_vec3f("u_light_pos", light_pos);
            _impl->set_mat4f("u_model", model);
            _impl->set_mat4f("u_view", view);
            _impl->set_mat4f("u_projection", projection);
        });

} // namespace pg

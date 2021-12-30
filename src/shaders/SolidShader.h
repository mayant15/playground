#pragma once

#include "common.h"

namespace pg::shaders
{
    PG_DEFINE_SHADER(
        SolidShader,
        PG_DEFINE_VERTEX_SHADER("D:\\code\\graphics\\playground\\src\\shaders\\glsl\\identity.vert"),
        PG_DEFINE_FRAGMENT_SHADER("D:\\code\\graphics\\playground\\src\\shaders\\glsl\\solid_color.frag"),
        PG_DEFINE_UNIFORMS(const Color &fill_color)
        {
            _impl->set_color("fill_color", fill_color);
        })
} // namespace pg::shaders

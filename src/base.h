#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <utility>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

namespace pg
{
    using vertex_layout_index_t = unsigned int;

    using vertex_t = float;
    using index_t = unsigned int;
} // namespace pg

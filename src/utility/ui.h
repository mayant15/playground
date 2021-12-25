#pragma once

#include <base.h>

namespace pg::ui
{

    void init(GLFWwindow *window);
    void new_frame();
    void demo_window(bool &show);
    void finalize_frame();
    void render();
    void shutdown();

} // namespace pg::ui

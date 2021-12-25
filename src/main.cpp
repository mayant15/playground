#include <iostream>

#include "base.h"
#include "Window.h"

#include "utility/logger.h"
#include "utility/ui.h"

int main(void)
{
    pg::Window window{};
    pg::WindowOp window_op{};

    if (window.init(window_op))
    {
        pg::log::error("Failed to create window");
        return EXIT_FAILURE;
    }

    window.set_current();

    // Initialize glad
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        pg::log::error("Failed to initialize glad");
        return EXIT_FAILURE;
    }

    glfwSwapInterval(1);

    pg::log::info("Successfully initialized OpenGL context");

    pg::ui::init(window.get_raw_pointer());

    bool show_demo_window = true;

    const auto &[width, height] = window.get_dims();
    glViewport(0, 0, width, height);

    glClearColor(0.5, 0.7, 0.4, 1.0);

    // Main loop
    while (!window.should_close())
    {
        pg::ui::new_frame();
        pg::ui::demo_window(show_demo_window);

        pg::ui::finalize_frame();

        glClear(GL_COLOR_BUFFER_BIT);

        pg::ui::render();

        window.swap_buffers();
        pg::poll_window_events();
    }

    // Shutdown
    pg::ui::shutdown();

    return EXIT_SUCCESS;
}

#include "Window.h"
#include "utility/logger.h"

namespace pg
{
    void glfw_error_callback(int error, const char *description)
    {
        pg::log::error("[GLFW{}]: {}", error, description);
    }

    void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int modifiers)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    int Window::init(const WindowOp &op)
    {
        const char *glsl_version = "#version 460";

        // Initialize
        if (glfwInit() == GLFW_FALSE)
        {
            pg::log::error("Failed to initialize GLFW");
            return EXIT_FAILURE;
        }
        glfwSetErrorCallback(glfw_error_callback);

        // Create a new window and OpenGL context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        _p_window = glfwCreateWindow(op.width, op.height, op.title.c_str(), nullptr, nullptr);
        if (!_p_window)
        {
            pg::log::error("Failed to create GLFW window");
            return EXIT_FAILURE;
        }
        glfwSetKeyCallback(_p_window, glfw_key_callback);

        return EXIT_SUCCESS;
    }

    Window::~Window()
    {
        glfwDestroyWindow(_p_window);
        glfwTerminate();
    }

    void Window::set_current() const
    {
        glfwMakeContextCurrent(_p_window);
    }

    std::pair<int, int> Window::get_dims() const
    {

        int width, height;
        glfwGetFramebufferSize(_p_window, &width, &height);
        return {width, height};
    }

    bool Window::should_close() const
    {
        return glfwWindowShouldClose(_p_window);
    }

    void Window::swap_buffers() const
    {
        glfwSwapBuffers(_p_window);
    }

    GLFWwindow *Window::get_raw_pointer() const
    {
        return _p_window;
    }

    void poll_window_events()
    {
        glfwPollEvents();
    }

} // namespace pg

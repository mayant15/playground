#include "Window.h"
#include "utility/errors.h"
#include "utility/logger.h"

namespace pg
{
    void glfw_error_callback(int error, const char *description)
    {
        pg::log::error("[GLFW{}]: {}", error, description);
    }

    void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int modifiers)

    {
        const auto *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
        for (const auto &callback : w->_key_press_callbacks)
        {
            std::invoke(callback, key);
        }
    }

    Window::Window(const WindowOp &op)
    {
        const char *glsl_version = "#version 460";

        // Initialize
        if (glfwInit() == GLFW_FALSE)
        {
            throw pg::Error{"Failed to initialize GLFW"};
        }
        glfwSetErrorCallback(glfw_error_callback);

        // Create a new window and OpenGL context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        _p_window = glfwCreateWindow(op.width, op.height, op.title.c_str(), nullptr, nullptr);
        if (!_p_window)
        {
            glfwDestroyWindow(_p_window);
            glfwTerminate();
            throw pg::Error{"Failed to create GLFW window"};
        }

        glfwSetWindowUserPointer(_p_window, this);

        glfwSetKeyCallback(_p_window, pg::glfw_key_callback);
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

    void Window::add_key_press_callback(const std::function<void(int)> &callback)
    {
        _key_press_callbacks.push_back(callback);
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

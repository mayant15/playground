#pragma once

#include "base.h"

namespace pg
{
    struct WindowOp
    {
        int width = 1920;
        int height = 1080;
        std::string title = "Playground";
    };

    class Window
    {
    public:
        Window() = default;
        ~Window();

        int init(const WindowOp &op);
        void set_current() const;
        std::pair<int, int> get_dims() const;
        bool should_close() const;
        void swap_buffers() const;
        GLFWwindow *get_raw_pointer() const;

        void add_key_press_callback(const std::function<void(int)> &callback);

    private:
        GLFWwindow *_p_window = nullptr;
        std::vector<std::function<void(int)>> _key_press_callbacks = {};

        friend void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int modifiers);
    };

    void poll_window_events();
} // namespace pg

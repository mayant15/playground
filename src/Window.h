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

    private:
        GLFWwindow *_p_window = nullptr;
    };

    void poll_window_events();
} // namespace pg

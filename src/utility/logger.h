#pragma once

#include <utility>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace pg::log
{
    template <typename... Args>
    void info(Args &&...args)
    {
        spdlog::info(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(Args &&...args)
    {
        spdlog::warn(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(Args &&...args)
    {
        spdlog::error(std::forward<Args>(args)...);
    }
}

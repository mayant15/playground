#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace pg
{
    using layout_index_t = unsigned int;

    using vertex_t = float;
    using index_t = unsigned int;

    using Color = glm::vec4;

    template <class T>
    using SRef = std::shared_ptr<T>;

    template <class T>
    using URef = std::unique_ptr<T>;
} // namespace pg

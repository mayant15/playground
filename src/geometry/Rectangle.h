#pragma once

#include <VertexArrayInfo.h>

namespace pg
{
    VertexArrayInfo create_rectangle_vertex_info()
    {
        // vertices and indices
        std::vector<pg::vertex_t> vertices = {
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top left
        };
        std::vector<pg::index_t> indices = {
            // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        VertexArrayInfo vertex_info{};
        vertex_info
            .add_vertex_array(vertices)
            .add_indices_array(indices)
            .layout_vertices(pg::VERTEX_POSITION_LAYOUT_INDEX);

        return vertex_info;
    }
} // namespace pg

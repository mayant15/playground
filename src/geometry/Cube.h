
#pragma once

#include <VertexArrayInfo.h>

namespace pg
{
    VertexArrayInfo create_cube_vertex_info()
    {
        // vertices
        std::vector<pg::vertex_t> vertices =
            {
                -0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,

                -0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,

                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,

                0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,

                -0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                0.5f,
                -0.5f,
                -0.5f,
                -0.5f,

                -0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                0.5f,
                -0.5f,
                0.5f,
                -0.5f,
            };

        VertexArrayInfo vertex_info{};
        vertex_info
            .add_vertex_array(vertices)
            .layout_vertices(pg::VERTEX_POSITION_LAYOUT_INDEX);

        return vertex_info;
    }
} // namespace pg

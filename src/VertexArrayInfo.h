#pragma once

#include "base.h"

namespace pg
{
    constexpr unsigned int DEFAULT_VERTEX_ARRAY_INFO_ID = 0;

    // Analogous to an OpenGL VAO. Keep all mesh related information here.
    class VertexArrayInfo
    {
    public:
        VertexArrayInfo();

        VertexArrayInfo &add_vertex_array(const std::vector<vertex_t> &vertices);
        VertexArrayInfo &add_indices_array(const std::vector<index_t> &indices);
        VertexArrayInfo &layout_vertices(layout_index_t index);
        VertexArrayInfo &layout_normals(layout_index_t index);
        void bind();
        void unbind();
        void render();

    private:
        unsigned int _id = DEFAULT_VERTEX_ARRAY_INFO_ID;

        unsigned int _vbo;
        unsigned int _vbo_size;
        bool _is_vbo_attached = false;

        unsigned int _ebo;
        unsigned int _ebo_size;
        bool _is_ebo_attached = false;

        bool _is_bound = false;
    };
} // namespace pg

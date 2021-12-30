#include "VertexArrayInfo.h"
#include "utility/logger.h"

namespace pg
{
    VertexArrayInfo::VertexArrayInfo()
    {
        glGenVertexArrays(1, &_id);
    }

    void VertexArrayInfo::bind()
    {
        glBindVertexArray(_id);
        _is_bound = true;
    }

    void VertexArrayInfo::unbind()
    {
        glBindVertexArray(DEFAULT_VERTEX_ARRAY_INFO_ID);
        _is_bound = false;
    }

    VertexArrayInfo &VertexArrayInfo::add_vertex_array(const std::vector<vertex_t> &vertices)
    {
        if (!_is_bound)
            bind();

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        _is_vbo_attached = true;
        _vbo_size = vertices.size();

        return *this;
    }

    VertexArrayInfo &VertexArrayInfo::add_indices_array(const std::vector<index_t> &indices)
    {
        if (!_is_bound)
            bind();

        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

        _is_ebo_attached = true;
        _ebo_size = indices.size();

        return *this;
    }

    VertexArrayInfo &VertexArrayInfo::layout_vertices(vertex_layout_index_t index)
    {
        if (!_is_bound)
            bind();

        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t) * 3, (void *)0);
        glEnableVertexAttribArray(index);

        return *this;
    }

    void VertexArrayInfo::render()
    {
        if (!_is_bound)
            bind();

        if (!_is_vbo_attached)
        {
            pg::log::error("[DRAW] No vertex information attached to VertexArrayInfo. Did you forget to use add_vertex_array()?");
            return;
        }

        // Render via indices if available, else render the vertices attached as they are
        if (_is_ebo_attached)
        {
            glDrawElements(GL_TRIANGLES, _ebo_size, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, _vbo_size);
        }

        unbind();
    }

} // namespace pg

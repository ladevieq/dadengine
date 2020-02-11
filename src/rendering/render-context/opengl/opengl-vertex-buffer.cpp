#include "opengl-vertex-buffer.hpp"

#include "opengl-wrapper.hpp"

namespace DadEngine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t _vertexCount,
                                           TArray<VertexInput> &_verticesLayout,
                                           TArray<float> &_data,
                                           uint32_t _stride)
        : VertexBuffer(_vertexCount, _verticesLayout, _data, _stride)
    {
        glGenVertexArrays(1U, &m_arrayIndex);
        glBindVertexArray(m_arrayIndex);

        glGenBuffers(1U, &m_bufferIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex);
        glBufferData(GL_ARRAY_BUFFER, m_data.Size() * sizeof(m_data[0]),
                     m_data.GetData(), GL_STATIC_DRAW);

        glBindVertexArray(0U);
        glBindBuffer(GL_ARRAY_BUFFER, 0U);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1U, &m_bufferIndex);
        glDeleteVertexArrays(1U, &m_arrayIndex);
    }
} // namespace DadEngine

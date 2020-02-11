#ifndef __OPENGL_VERTEX_BUFFER_HPP_
#define __OPENGL_VERTEX_BUFFER_HPP_

#include "opengl.hpp"

#include "vertex-buffer.hpp"

namespace DadEngine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {

        public:
        OpenGLVertexBuffer(uint32_t _vertexCount,
                           TArray<VertexInput> &_verticesLayout,
                           TArray<float> &_data,
                           uint32_t _stride);

        virtual ~OpenGLVertexBuffer();

        GLuint m_bufferIndex = 0U;
        GLuint m_arrayIndex = 0U;
    };
} // namespace DadEngine

#endif //!__OPENGL_VERTEX_BUFFER_HPP_


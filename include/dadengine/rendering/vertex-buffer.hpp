#ifndef __VERTEX_BUFFER_HPP_
#define __VERTEX_BUFFER_HPP_

#include "../core/core.hpp"
#include "mesh/vertex-input-layout.hpp"

namespace DadEngine
{
    class VertexBuffer
    {

        public:
        VertexBuffer(uint32_t _vertexCount, TArray<VertexInput> &_verticesLayout, uint32_t _stride);

        VertexBuffer(uint32_t _vertexCount,
                     TArray<VertexInput> &_verticesLayout,
                     TArray<float> &_data,
                     uint32_t _stride);

        virtual ~VertexBuffer()
        {
        }


        uint32_t m_vertexCount = 0U;
        uint32_t m_vertexLayoutStride = 0U;
        TArray<VertexInput> m_verticesLayout;
        TArray<float> m_data;
    };
} // namespace DadEngine

#endif //__VERTEX_BUFFER_HPP_

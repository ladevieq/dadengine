#include "VertexBuffer.hpp"

namespace DadEngine::Rendering
{
    VertexBuffer::VertexBuffer(uint32_t _InVertexCount, TArray<VertexInput> &_InVerticesLayout, uint32_t _InStride)
        : m_uiVertexCount(_InVertexCount), m_verticesLayout(_InVerticesLayout),
          m_uiVertexLayoutStride(_InStride)
    {
    }

    VertexBuffer::VertexBuffer(uint32_t _InVertexCount,
                               TArray<VertexInput> &_InVerticesLayout,
                               TArray<float> &_InData,
                               uint32_t _InStride)
        : m_uiVertexCount(_InVertexCount), m_verticesLayout(_InVerticesLayout), m_Data(_InData),
          m_uiVertexLayoutStride(_InStride)
    {
    }
} // namespace DadEngine::Rendering
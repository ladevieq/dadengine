#include "vertex-buffer.hpp"

namespace DadEngine
{
    VertexBuffer::VertexBuffer(uint32_t _vertexCount,
                               TArray<VertexInput> &_verticesLayout,
                               uint32_t _stride)
        : m_vertexCount(_vertexCount), m_verticesLayout(_verticesLayout),
          m_vertexLayoutStride(_stride)
    {
    }

    VertexBuffer::VertexBuffer(uint32_t _vertexCount,
                               TArray<VertexInput> &_verticesLayout,
                               TArray<float> &_data,
                               uint32_t _stride)
        : m_vertexCount(_vertexCount), m_verticesLayout(_verticesLayout),
          m_data(_data), m_vertexLayoutStride(_stride)
    {
    }
} // namespace DadEngine

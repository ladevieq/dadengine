#include "vertex-input-layout.hpp"

namespace DadEngine
{
    void VertexInput::GetInputTypeInfo(size_t &_inputTypeSize, uint32_t &_inputTypeElementCount)
    {
        switch (vertexInputType)
        {
        case VERTEX_INPUT_TYPE_POSITION:
        {
            _inputTypeElementCount = 3U;
            _inputTypeSize = _inputTypeElementCount * sizeof(float);
            break;
        }

        case VERTEX_INPUT_TYPE_COLOR:
        {
            _inputTypeElementCount = 3U;
            _inputTypeSize = _inputTypeElementCount * sizeof(float);
            break;
        }

        case MAX_VERTEX_INPUT_TYPE:
            break;
        }
    }

    void VertexInput::GetLayoutStride(TArray<VertexInput> &_vertexLayout, uint32_t &_stride)
    {
        _stride = 0U;

        for (VertexInput vi : _vertexLayout)
        {
            size_t size;
            uint32_t count;

            vi.GetInputTypeInfo(size, count);

            _stride += static_cast<uint32_t>(size);
        }
    }
} // namespace DadEngine

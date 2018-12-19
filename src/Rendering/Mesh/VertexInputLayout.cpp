#include "VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
    void VertexInput::GetInputTypeInfo(size_t &_OutInputTypeSize, uint32_t &_OutInputTypeElementCount)
    {
        switch (uiVertexInputType)
        {
        case VERTEX_INPUT_TYPE_POSITION:
        {
            _OutInputTypeElementCount = 3U;
            _OutInputTypeSize = _OutInputTypeElementCount * sizeof(float);
            break;
        }

        case VERTEX_INPUT_TYPE_COLOR:
        {
            _OutInputTypeElementCount = 3U;
            _OutInputTypeSize = _OutInputTypeElementCount * sizeof(float);
            break;
        }

        default:
            break;
        }
    }

    void VertexInput::GetLayoutStride(TArray<VertexInput> &_InVertexLayout, uint32_t &_OutStride)
    {
        _OutStride = 0U;

        for (VertexInput vi : _InVertexLayout)
        {
            size_t size;
            uint32_t count;

            vi.GetInputTypeInfo(size, count);

            _OutStride += (uint32_t)size;
        }
    }
}
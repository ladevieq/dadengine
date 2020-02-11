#ifndef __VERTEX_INPUT_LAYOUT_HPP_
#define __VERTEX_INPUT_LAYOUT_HPP_

#include "../../core/core.hpp"

namespace DadEngine
{
    enum VertexInputType
    {
        VERTEX_INPUT_TYPE_POSITION = 0x1,
        VERTEX_INPUT_TYPE_COLOR = 0x2,
        MAX_VERTEX_INPUT_TYPE = 0xff
    };

    // using VertexInputLayoutFlag = uint32;


    struct VertexInput
    {
        uint8_t index = 0U;
        VertexInputType vertexInputType;

        void GetInputTypeInfo(size_t &_inputTypeSize, uint32_t &_inputTypeElementCount);

        static void GetLayoutStride(TArray<VertexInput> &_vertexLayout, uint32_t &_stride);
    };
} // namespace DadEngine

#endif //!__VERTEX_INPUT_LAYOUT_HPP_


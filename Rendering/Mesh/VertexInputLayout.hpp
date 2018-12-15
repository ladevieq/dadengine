#ifndef __VERTEX_INPUT_LAYOUT_HPP_
#define __VERTEX_INPUT_LAYOUT_HPP_

#include "../../Core/Core.hpp"

namespace DadEngine::Rendering
{
	enum VertexInputType
	{
		VERTEX_INPUT_TYPE_POSITION = 0x1,
		VERTEX_INPUT_TYPE_COLOR = 0x2,
		MAX_VERTEX_INPUT_TYPE = 0xff
	};

	//using VertexInputLayoutFlag = uint32;


	struct VertexInput
	{
		uint8_t uiIndex = 0U;
		VertexInputType uiVertexInputType;

		void GetInputTypeInfo(size_t &_OutInputTypeSize, uint32_t &_OutInputTypeElementCount);

		static void GetLayoutStride(TArray<VertexInput> &_InVertexLayout, uint32_t &_OutStride);
	};
}

#endif //!__VERTEX_INPUT_LAYOUT_HPP_
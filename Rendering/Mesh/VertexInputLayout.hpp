#ifndef __VERTEX_INPUT_LAYOUT_HPP_
#define __VERTEX_INPUT_LAYOUT_HPP_


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

		FORCE_INLINE void GetInputTypeInfo(size_t& _OutInputTypeSize, uint32_t& _OutInputTypeElementCount)
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

		FORCE_INLINE static void GetLayoutStride(TArray<VertexInput> &_InVertexLayout, uint32_t &_OutStride)
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
	};
}

#endif //!__VERTEX_INPUT_LAYOUT_HPP_
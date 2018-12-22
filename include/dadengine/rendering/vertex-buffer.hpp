#ifndef __VERTEX_BUFFER_HPP_
#define __VERTEX_BUFFER_HPP_

#include "../core/core.hpp"
#include "mesh/vertex-input-layout.hpp"

namespace DadEngine::Rendering
{
	class VertexBuffer
	{

	public:

		VertexBuffer(uint32_t _InVertexCount, TArray<VertexInput> &_InVerticesLayout, uint32_t _InStride);

		VertexBuffer(uint32_t _InVertexCount, TArray<VertexInput> &_InVerticesLayout, TArray<float> &_InData, uint32_t _InStride);


		uint32_t m_uiVertexCount = 0U;
        uint32_t m_uiVertexLayoutStride = 0U;
		TArray<VertexInput> m_verticesLayout;
		TArray<float> m_Data;
	};
}

#endif//__VERTEX_BUFFER_HPP_
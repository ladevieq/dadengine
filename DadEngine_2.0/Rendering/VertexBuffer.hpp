#ifndef __VERTEX_BUFFER_HPP_
#define __VERTEX_BUFFER_HPP_

#include "../Core/Core.hpp"
#include "Mesh/VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
	class VertexBuffer
	{

	public:

		VertexBuffer(uint32 _InVertexCount, TArray<VertexInput>& _InVerticesLayout, uint32 _InStride)
			:	m_uiVertexCount(_InVertexCount),
				m_verticesLayout(_InVerticesLayout),
				m_uiVertexLayoutStride(_InStride)
		{}

		VertexBuffer(uint32 _InVertexCount, TArray<VertexInput>& _InVerticesLayout, TArray<float>& _InData, uint32 _InStride)
			:	m_uiVertexCount(_InVertexCount),
				m_verticesLayout(_InVerticesLayout),
				m_Data(_InData),
				m_uiVertexLayoutStride(_InStride)
		{}


		uint32 m_uiVertexCount = 0U;
		uint32 m_uiVertexLayoutStride = 0U;
		TArray<VertexInput> m_verticesLayout;
		TArray<float> m_Data;
	};
}

#endif//!__VERTEX_BUFFER_HPP_
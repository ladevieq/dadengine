#ifndef __VERTEX_FACTORY_HPP_
#define __VERTEX_FACTORY_HPP_

#include "RawMesh.hpp"
#include "VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
	class Vertexfactory
	{

	public:

		static void Create(RawMesh& _InMesh, TArray<float>& _OutData, TArray<VertexInput>& _InVerticesLayout, uint32_t& _OutStride)
		{
			_InMesh.Create(_InVerticesLayout, _OutData, _OutStride);
		}
	};
}

#endif //__VERTEX_FACTORY_HPP_
#ifndef __RAW_MESH_HPP_
#define __RAW_MESH_HPP_

#include "RawVertex.hpp"


namespace DadEngine::Rendering
{
	struct VertexInput;

	// Convert concrete files data into this data structure
	class RawMesh
	{
		
	public:

		void Create(const TArray<VertexInput> &_InVerticesLayout, TArray<float> &_OutData, uint32_t &_OutStride);


		TArray<RawVertex> m_vertices;
	};
}

#endif // !__RAW_MESH_HPP_

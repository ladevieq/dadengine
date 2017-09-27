#ifndef __RAW_MESH_HPP_
#define __RAW_MESH_HPP_

#include "RawVertex.hpp"

namespace DadEngine::Rendering
{
	// Convert concrete files data into this data structure
	class RawMesh
	{
		
	public:

		void Create(const VertexTypeEXT _InVerticesType, TArray<float>& _OutData)
		{
			for (RawVertex& currentVertex : m_vertices)
			{
				if (_InVerticesType & VERTEX_TYPE_POSITION)
				{

				}
			}
		}


	private:

		TArray<RawVertex> m_vertices;
	};
}

#endif // !__RAW_MESH_HPP_

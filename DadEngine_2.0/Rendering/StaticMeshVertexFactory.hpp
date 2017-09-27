#ifndef __STATIC_MESH_VERTEX_FACTORY_HPP_
#define __STATIC_MESH_VERTEX_FACTORY_HPP_

#include "RawMesh.hpp"

namespace DadEngine::Rendering
{
	class StaticMeshVertexfactory
	{
		static void Create(const RawMesh& _InMesh, TArray<float>& _OutData)
		{
			_InMesh.Create(VERTEX_TYPE_POSITION, _OutData);
		}
	};
}

#endif //__STATIC_MESH_VERTEX_FACTORY_HPP_
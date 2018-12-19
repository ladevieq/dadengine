#ifndef __RAW_VERTEX_HPP_
#define __RAW_VERTEX_HPP_

#include "../../Math/Math.hpp"

namespace DadEngine::Rendering
{
	// All information about one vertex from concrete files(.obj, .fbx, .gltf2.0)
	struct RawVertex
	{
		RawVertex() = default;

		RawVertex(const Vector3f& _InPosition): Position(_InPosition)
		{}

		RawVertex(const Vector3f& _InPosition, const Vector3f& _InColor0)
			: Position(_InPosition), Color0(_InColor0)
		{}


		Vector3f Position = NullVector3f;

		Vector3f Color0 = NullVector3f;
		//Vector3f Color1 = NullVector3f;
		//Vector3f Color2 = NullVector3f;
		//Vector3f Color3 = NullVector3f;

		//Vector3f Normal = NullVector3f;
		//Vector3f Tangent = NullVector3f;
	};
}

#endif // __RAW_VERTEX_HPP_
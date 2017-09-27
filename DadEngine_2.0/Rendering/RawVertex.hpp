#ifndef __RAW_VERTEX_HPP_
#define __RAW_VERTEX_HPP_

#include "../Core/Core.hpp"
#include "../Math/Math.hpp"

namespace DadEngine::Rendering
{
	// All information about one vertex from concrete files(.obj, .fbx)
	struct RawVertex
	{
		Vector3f Position;

		Vector3f Color0;
		Vector3f Color1;
		Vector3f Color2;
		Vector3f Color3;

		Vector3f Normal;
		Vector3f Tangent;
	};

	enum VertexInputLayout
	{
		VERTEX_TYPE_POSITION,
	};

	//using VertexTypeEXT = uint8;
	typedef uint8 VertexTypeEXT;
}

#endif // __RAW_VERTEX_HPP_
#include "vulkan-vertex-input-layout.hpp"

#include "../../mesh/vertex-input-layout.hpp"

namespace DadEngine::Rendering
{
	VkFormat VertexInputTypeFormat(VertexInputType _InInputType)
	{
		switch (_InInputType)
		{
		case VERTEX_INPUT_TYPE_POSITION:
			return VK_FORMAT_R32G32B32_SFLOAT;

		case VERTEX_INPUT_TYPE_COLOR:
			return VK_FORMAT_R32G32B32_SFLOAT;

		default:
			return VK_FORMAT_UNDEFINED;
		}
	}
}
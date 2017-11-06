#ifndef __VULKAN_VERTEX_INPUT_LAYOUT_HPP_
#define __VULKAN_VERTEX_INPUT_LAYOUT_HPP_

#include "../../Mesh/VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
	FORCE_INLINE VkFormat VertexInputTypeFormat(VertexInputType _InInputType)
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

#endif //!__VULKAN_VERTEX_INPUT_LAYOUT_HPP_
#ifndef __VULKAN_VERTEX_INPUT_LAYOUT_HPP_
#define __VULKAN_VERTEX_INPUT_LAYOUT_HPP_

#include <vulkan/vulkan.hpp>

#include "../../../Core/Core.hpp"
#include "../../Mesh/VertexInputLayout.hpp"


namespace DadEngine::Rendering
{
	VkFormat VertexInputTypeFormat(VertexInputType _InInputType);
}

#endif //!__VULKAN_VERTEX_INPUT_LAYOUT_HPP_
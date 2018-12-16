#ifndef __VULKAN_VERTEX_INPUT_LAYOUT_HPP_
#define __VULKAN_VERTEX_INPUT_LAYOUT_HPP_

#include <vulkan/vulkan.hpp>


namespace DadEngine::Rendering
{
    enum VertexInputType;

	VkFormat VertexInputTypeFormat(VertexInputType _InInputType);
}

#endif //!__VULKAN_VERTEX_INPUT_LAYOUT_HPP_
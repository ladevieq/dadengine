#ifndef __VULKAN_VERTEX_BUFFER_HPP_
#define __VULKAN_VERTEX_BUFFER_HPP_

#include "vulkan/vulkan.hpp"

#include "VulkanHelper.hpp"
#include "VulkanDebug.hpp"
#include "../../VertexBuffer.hpp"

namespace DadEngine::Rendering
{
	class VulkanVertexBuffer : public VertexBuffer
	{

	public:

		VulkanVertexBuffer(uint32 _InVertexCount, TArray<VertexInput>& _InVerticesInputLayout, TArray<float>& _InData, uint32 _InStride, VkDevice _InDevice, VkPhysicalDevice _InPhysicalDevice);

		VkBuffer m_buffer = VK_NULL_HANDLE;
		VkDeviceMemory m_memory = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_VERTEX_BUFFER_HPP_

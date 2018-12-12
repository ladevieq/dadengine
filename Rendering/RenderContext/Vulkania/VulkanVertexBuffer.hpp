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

		VulkanVertexBuffer(uint32_t _InVertexCount,
                       TArray<VertexInput> &_InVerticesInputLayout,
                       TArray<float> &_InData,
                       uint32_t _InStride,
                       VkDevice _InDevice,
                       VkPhysicalDevice _InPhysicalDevice);

		~VulkanVertexBuffer();



		VkDevice m_Device = VK_NULL_HANDLE;

		VkBuffer m_Buffer = VK_NULL_HANDLE;
		VkDeviceMemory m_Memory = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_VERTEX_BUFFER_HPP_

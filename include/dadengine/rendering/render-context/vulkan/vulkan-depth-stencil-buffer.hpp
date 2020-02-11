#ifndef __VULKAN_DEPTH_STENCIL_BUFFER_HPP_
#define __VULKAN_DEPTH_STENCIL_BUFFER_HPP_

#include <vulkan/vulkan.h>

#include "vulkan-image.hpp"

namespace DadEngine
{
	class VulkanDepthStencilBuffer : public VulkanImage
	{
	public:

		//VulkanDepthStencilBuffer(VkDevice _InDevice, VkExtent2D& _InImageSize, VkPhysicalDeviceMemoryProperties& _InPhysicalDeviceMemoryProps);

		VulkanDepthStencilBuffer() = default;

		VulkanDepthStencilBuffer(VkDevice _InDevice, VkFormat _InDepthStencilFormat, VkExtent2D& _InImageSize,
			VkPhysicalDevice _InPhysicalDevice, VkImageUsageFlags _InImageUses, VkCommandBuffer _InCommandBuffer);


	private:


		// Contain code similar for each constructor
		void CreateDepthStencilBuffer(VkPhysicalDevice _InPhysicalDevice, VkCommandBuffer _InCommandBuffer);

		void ChooseAspect();
	};
}

#endif //__VULKAN_DEPTH_STENCIL_BUFFER_HPP_


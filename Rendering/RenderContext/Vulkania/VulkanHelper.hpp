#ifndef __VULKAN_HELPER_HPP_
#define __VULKAN_HELPER_HPP_

#include "vulkan/vulkan.h"

#include "../../../Core/Core.hpp"
#include "VulkanDebug.hpp"

namespace DadEngine::Rendering
{
	class VulkanImage;

	namespace VulkanHelper
	{
		void EnumerateDevices(VkInstance _InInstance, TArray<VkPhysicalDevice>& _InPhysicalDevices);

		void EnumerateInstanceLayersAndExtensions();

		void EnumerateDeviceLayersAndExtensions(VkPhysicalDevice _InPhysicalDevice);

		uint32 CheckDeviceQueueFamilyProperties(VkPhysicalDevice _InPhysicalDevice, VkQueueFlags _InFlag);

		uint32 CheckMemoryTypeIndex(VkPhysicalDevice _InPhysicalDevice, uint32 _InMemoryTypeBits, VkMemoryPropertyFlags _InProperties);

		VkSurfaceFormatKHR CheckSurfaceFormats(VkPhysicalDevice _InPhysicalDevice, VkSurfaceKHR _InSurface);

		void CreateCommandBuffer(VkDevice _InDevice, VkCommandPool _InCommandPool, uint32 _InCount, VkCommandBuffer* _OutCommandBuffers);

		void CreateBuffer(VkDevice _InDevice, VkDeviceSize _InSize, VkBufferUsageFlags _InBufferUsage, VkBuffer& _OutBuffer);

		VkExtent2D GetExtent2D(VkPhysicalDevice _InDevice, VkSurfaceKHR _InSurface);

		VkFormat GetSupportDepthStencilFormats(VkPhysicalDevice _InDevice);

		void SetImageLayout(VkCommandBuffer _InCommandBuffer, VkImage _InImage,
			VkImageLayout _InOldImageLayout, VkImageLayout _InNewImageLayout,
			VkPipelineStageFlags _InSrcPipilineStageFalgs, VkPipelineStageFlags _InDstPipilineStageFalgs);

		void SetImageLayout(VkCommandBuffer _InCommandBuffer, VulkanImage& _Image,
			VkImageLayout _InNewImageLayout, VkPipelineStageFlags _InSrcPipilineStageFalgs,
			VkPipelineStageFlags _InDstPipilineStageFalgs);

		void AllocateBufferMemory(VkDevice _InDevice, VkPhysicalDevice _InPhysicalDevice, VkBuffer _InBuffer, VkMemoryPropertyFlags _InMemProperties, VkDeviceMemory& _OutMemory);
	}
}

#endif //__VULKAN_HELPER_HPP_
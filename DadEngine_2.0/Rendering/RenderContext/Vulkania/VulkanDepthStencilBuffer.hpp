#ifndef __VULKAN_DEPTH_STENCIL_BUFFER_HPP_
#define __VULKAN_DEPTH_STENCIL_BUFFER_HPP_

#include "vulkan/vulkan.hpp"

#include "VulkanImage.hpp"

namespace DadEngine::Rendering
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

		FORCE_INLINE void ChooseAspect()
		{
			switch (m_Format)
			{
			case VK_FORMAT_D32_SFLOAT_S8_UINT:
				m_ImageAspect = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
				break;
			case VK_FORMAT_D32_SFLOAT:
				m_ImageAspect = VK_IMAGE_ASPECT_DEPTH_BIT;
				break;
			case VK_FORMAT_D24_UNORM_S8_UINT:
				m_ImageAspect = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
				break;
			case VK_FORMAT_D16_UNORM_S8_UINT:
				m_ImageAspect = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
				break;
			case VK_FORMAT_D16_UNORM:
				m_ImageAspect = VK_IMAGE_ASPECT_DEPTH_BIT;
				break;
			default:
				LogDebugReport(DebugReport{ DEBUG_REPORT_CONTEXT_VULKAN, DEBUG_REPORT_TYPE_ERROR,
					DEBUG_REPORT_CODE_DEPTH_STENCIL_BUFFER_FORMAT_ERROR,
					"Depth stencil buffer have been created with invalid format !" });
				break;
			}
		}
	};
}

#endif //__VULKAN_DEPTH_STENCIL_BUFFER_HPP_
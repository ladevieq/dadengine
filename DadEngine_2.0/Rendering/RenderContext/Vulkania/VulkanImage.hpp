#ifndef __VULKAN_IMAGE_HPP_
#define __VULKAN_IMAGE_HPP_

#include "vulkan/vulkan.hpp"

#include "../../Image.hpp"
#include "VulkanDebug.hpp"
#include "VulkanHelper.hpp"

namespace DadEngine::Rendering
{
	class VulkanImage : public Image
	{
	
	public:

		VulkanImage() = default;

		VulkanImage(VkDevice _InDevice,
			VkFormat _InImageFormat,
			VkExtent2D& _InImageSize,
			VkImageUsageFlags _InImagUsage)
			: Image(*(Extent2D*)&_InImageSize),
				m_Device(_InDevice),
				m_Format(_InImageFormat),
				m_ImageUsage(_InImagUsage)
		{}

		VulkanImage(VkDevice _InDevice, VkPhysicalDeviceMemoryProperties _InPhysicalDeviceMemoryProps,
			VkCommandBuffer _InCommandBuffer, VkFormat _InImageFormat,
			VkImageUsageFlags _InImageUsage, VkImageAspectFlags _InImageAspects,
			VkImageLayout _InImageLayout, VkExtent2D& _InImageSize, size_t _InImageLayers);

		VulkanImage(VkDevice _InDevice, VkPhysicalDeviceMemoryProperties _InPhysicalDeviceMemoryProps,
			VkFormat _InImageFormat, VkImageUsageFlags _InImageUsage,
			VkImageAspectFlags _InImageAspects, VkExtent2D& _InImageSize,
			size_t _InImageLayers);


		VulkanImage(VkDevice _InDevice, VkImage _InImageHandle,
			VkImageView _InImageViewHandle, VkDeviceMemory _ImMemory,
			VkFormat _InImageFormat, VkExtent2D& _InImageSize,
			VkImageSubresourceRange& _InImageSubresourceRange)

			: Image(*((Extent2D*)&_InImageSize)),
			m_Device(_InDevice), m_Image(_InImageHandle),
			m_View(_InImageViewHandle), m_Memory(_ImMemory),
			m_Format(_InImageFormat), m_ImageSubresourceRange(_InImageSubresourceRange)
		{}


		~VulkanImage();



		VkDevice m_Device = VK_NULL_HANDLE;

		VkImage m_Image = VK_NULL_HANDLE;
		VkImageView m_View = VK_NULL_HANDLE;

		VkDeviceMemory m_Memory = VK_NULL_HANDLE;
		VkFormat m_Format = VK_FORMAT_UNDEFINED;
		VkImageLayout m_CurrentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkImageSubresourceRange m_ImageSubresourceRange = {};

		VkImageUsageFlags m_ImageUsage = 0U;
		VkImageAspectFlags m_ImageAspect = 0U;
		//VkClearColorValue
	};
}

#endif //!__VULKAN_IMAGE_HPP_
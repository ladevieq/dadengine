#include "VulkanDepthStencilBuffer.hpp"

namespace DadEngine::Rendering
{
	VulkanDepthStencilBuffer::VulkanDepthStencilBuffer(VkDevice _InDevice, VkFormat _InDepthStencilFormat,
		VkExtent2D& _InImageSize, VkPhysicalDeviceMemoryProperties& _InPhysicalDeviceMemoryProps,
		VkImageUsageFlags _InImageUses)
		: VulkanImage(_InDevice, _InDepthStencilFormat, _InImageSize,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | _InImageUses)
	{
		ChooseAspect();

		CreateDepthStencilBuffer(_InPhysicalDeviceMemoryProps);
	}

	void VulkanDepthStencilBuffer::CreateDepthStencilBuffer(VkPhysicalDeviceMemoryProperties& _InPhysicalDeviceMemoryProps)
	{
		// Image handle creation
		VkImageCreateInfo image_create_info = {};
		image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_create_info.pNext = VK_NULL_HANDLE;
		image_create_info.arrayLayers = 1U;
		image_create_info.format = m_Format;
		image_create_info.mipLevels = 1U;
		image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_create_info.queueFamilyIndexCount = 0U;
		image_create_info.pQueueFamilyIndices = VK_NULL_HANDLE;
		image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		image_create_info.usage = m_ImageUsage;
		image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		image_create_info.imageType = VK_IMAGE_TYPE_2D;
		image_create_info.extent = { m_ImageSize.width, m_ImageSize.height, 1U };
		image_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateImage(m_Device, &image_create_info, VK_NULL_HANDLE, &m_Image));


		// Image memory allocation and binding
		VkMemoryRequirements memory_requierements = {};
		vkGetImageMemoryRequirements(m_Device, m_Image, &memory_requierements);

		VkMemoryAllocateInfo memory_allocation_info = {};
		memory_allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memory_allocation_info.pNext = VK_NULL_HANDLE;
		memory_allocation_info.memoryTypeIndex = VulkanHelper::CheckMemoryType(memory_requierements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, _InPhysicalDeviceMemoryProps);
		memory_allocation_info.allocationSize = memory_requierements.size;

		VK_CHECK_RESULT(vkAllocateMemory(m_Device, &memory_allocation_info, VK_NULL_HANDLE, &m_Memory));
		VK_CHECK_RESULT(vkBindImageMemory(m_Device, m_Image, m_Memory, 0U));


		// ImageView handle creation
		VkImageViewCreateInfo image_view_create_info = {};
		image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_view_create_info.pNext = VK_NULL_HANDLE;
		image_view_create_info.format = m_Format;
		image_view_create_info.image = m_Image;
		image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		image_view_create_info.subresourceRange.baseArrayLayer = 0U;
		image_view_create_info.subresourceRange.layerCount = 1U;
		image_view_create_info.subresourceRange.baseMipLevel = 0U;
		image_view_create_info.subresourceRange.levelCount = 1U;
		image_view_create_info.subresourceRange.aspectMask = m_ImageAspect;
		image_view_create_info.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		image_view_create_info.flags = 0U;

		m_ImageSubresourceRange.aspectMask = m_ImageAspect;
		m_ImageSubresourceRange.baseArrayLayer = 0U;
		m_ImageSubresourceRange.baseMipLevel = 0U;
		m_ImageSubresourceRange.layerCount = 1U;
		m_ImageSubresourceRange.levelCount = 1U;

		VK_CHECK_RESULT(vkCreateImageView(m_Device, &image_view_create_info, VK_NULL_HANDLE, &m_View));
	}
}
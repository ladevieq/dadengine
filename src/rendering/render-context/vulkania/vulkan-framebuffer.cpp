#include "vulkan-framebuffer.hpp"

#include "vulkan-debug.hpp"
#include "vulkan-renderpass.hpp"

namespace DadEngine::Rendering
{
	VulkanFramebuffer::VulkanFramebuffer(VkDevice _InDevice, VkExtent2D& _InFramebufferSize, VulkanRenderPass& _InRenderPass, VkImageView* _InViewImages, size_t _InImageCount)
		: m_Device(_InDevice), m_Extent(_InFramebufferSize)
	{
		m_Attachements.Add(_InViewImages, _InImageCount);

		VkFramebufferCreateInfo framebuffer_create_info = {};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.pNext = VK_NULL_HANDLE;
        framebuffer_create_info.attachmentCount = (uint32_t)_InImageCount;
		framebuffer_create_info.pAttachments = _InViewImages;
		framebuffer_create_info.renderPass = _InRenderPass.m_Renderpass;
		framebuffer_create_info.width = _InFramebufferSize.width;
		framebuffer_create_info.height = _InFramebufferSize.height;
		framebuffer_create_info.layers = 1U;
		framebuffer_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateFramebuffer(_InDevice, &framebuffer_create_info, VK_NULL_HANDLE, &m_Framebuffer));
	}

	VulkanFramebuffer::~VulkanFramebuffer()
	{
		//vkDestroyFramebuffer(m_Device, m_Framebuffer, VK_NULL_HANDLE);
	}
}
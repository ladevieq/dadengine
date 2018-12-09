#ifndef __VULKAN_FRAMEBUFFER_HPP_
#define __VULKAN_FRAMEBUFFER_HPP_

#include "vulkan/vulkan.hpp"
#include "../../../Core/Core.hpp"
#include "../../Framebuffer.hpp"

namespace DadEngine::Rendering
{
	class VulkanRenderPass;

	class VulkanFramebuffer : public Framebuffer
	{
		
	public:

		VulkanFramebuffer(VkDevice _InDevice, VkExtent2D& _InFramebufferSize, VulkanRenderPass& _InRenderPass, VkImageView* _InImages, size_t _InImageCount);

		~VulkanFramebuffer();


		VkDevice m_Device = VK_NULL_HANDLE;

		VkFramebuffer m_Framebuffer;

		VkExtent2D m_Extent;
		TArray<VkImageView> m_Attachements;
	};
}

#endif //!__VULKAN_FRAMEBUFFER_HPP_
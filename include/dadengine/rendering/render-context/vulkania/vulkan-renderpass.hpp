#ifndef __VULKAN_RENDERPASS_HPP_
#define __VULKAN_RENDERPASS_HPP_


#include <vulkan/vulkan.hpp>

#include "vulkan-image.hpp"
#include "../../renderpass.hpp"

#include "../../../core/core.hpp"

namespace DadEngine::Rendering
{
	class VulkanRenderPass : public RenderPass
	{

	public:

		VulkanRenderPass() = default;

		VulkanRenderPass(VkDevice _InDevice, VulkanImage* _InImages, size_t _InImagesCount);

		~VulkanRenderPass();



		VkDevice m_Device = VK_NULL_HANDLE;

		TArray<VulkanImage*> m_Attachments;
		VkRenderPass m_Renderpass;
	};
}

#endif //!__VULKAN_RENDERPASS_HPP_
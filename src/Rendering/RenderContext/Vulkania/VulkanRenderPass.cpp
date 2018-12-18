#include "VulkanRenderPass.hpp"

#include "VulkanDebug.hpp"

namespace DadEngine::Rendering
{
	VulkanRenderPass::VulkanRenderPass(VkDevice _InDevice, VulkanImage* _InImages, size_t _InImagesCount)
		: m_Device(_InDevice)
	{
		// Dependency to prepare implicit barrier
		TArray<VkSubpassDependency> dependencies(2U);
		dependencies[0U].srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[0U].dstSubpass = 0;
		dependencies[0U].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		dependencies[0U].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[0U].srcAccessMask = /*VK_ACCESS_MEMORY_READ_BIT;//*/VK_ACCESS_TRANSFER_WRITE_BIT;
		dependencies[0U].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[0U].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		dependencies[1U].srcSubpass = 0;
		dependencies[1U].dstSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[1U].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[1U].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		dependencies[1U].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;//0U;
		dependencies[1U].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;//VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		dependencies[1U].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;


		//m_Attachments.Add(&_InImages, _InImagesCount);

		TArray<VkAttachmentDescription> attachments(_InImagesCount);
		attachments[0U].format = _InImages[0U].m_Format;
		attachments[0U].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[0U].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;//VK_ATTACHMENT_LOAD_OP_CLEAR;						// Clear the image during load
		attachments[0U].storeOp = VK_ATTACHMENT_STORE_OP_STORE;														// Store the render pass result in the buffer
		attachments[0U].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[0U].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[0U].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//_InImages[(uint32)i].m_CurrentLayout;			// Image initial layout, start of the renderpass
		attachments[0U].finalLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;		// Image final layout, end of the renderpass
		attachments[0U].flags = 0U;

		attachments[1U].format = _InImages[1U].m_Format;
		attachments[1U].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[1U].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;//VK_ATTACHMENT_LOAD_OP_CLEAR;						// Clear the image during load
		attachments[1U].storeOp = VK_ATTACHMENT_STORE_OP_STORE;														// Store the render pass result in the buffer
		attachments[1U].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[1U].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[1U].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;													// Image initial layout, start of the renderpass, we don't care about the precedent depth stuff so VK_IMAGE_LAYOUT_UNDEFINED
		attachments[1U].finalLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;//VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;		// Image final layout, end of the renderpass
		attachments[1U].flags = 0U;


		VkAttachmentReference color_attachement_reference = {};
		color_attachement_reference.attachment = 0U;
		color_attachement_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depth_stencil_attachement_reference = {};
		depth_stencil_attachement_reference.attachment = 1U;
		depth_stencil_attachement_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


		// Describe a subpass
		VkSubpassDescription subpass_description = {};
		subpass_description.flags = 0U;
		subpass_description.colorAttachmentCount = 1U;
		subpass_description.pColorAttachments = &color_attachement_reference;
		subpass_description.pDepthStencilAttachment = &depth_stencil_attachement_reference;
		subpass_description.inputAttachmentCount = 0U;
		subpass_description.pInputAttachments = VK_NULL_HANDLE;
		subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass_description.preserveAttachmentCount = 0U;
		subpass_description.pPreserveAttachments = VK_NULL_HANDLE;


		VkRenderPassCreateInfo renderpass_create_info = {};
		renderpass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderpass_create_info.pNext = VK_NULL_HANDLE;
        renderpass_create_info.attachmentCount = (uint32_t)attachments.Size();
		renderpass_create_info.pAttachments = attachments.GetData();
		renderpass_create_info.subpassCount = 1U;
		renderpass_create_info.pSubpasses = &subpass_description;
        renderpass_create_info.dependencyCount = (uint32_t)dependencies.Size();
		renderpass_create_info.pDependencies = dependencies.GetData();
		renderpass_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateRenderPass(_InDevice, &renderpass_create_info, VK_NULL_HANDLE, &m_Renderpass));
	}

	VulkanRenderPass::~VulkanRenderPass()
	{
		//vkDestroyRenderPass(m_Device, m_Renderpass, VK_NULL_HANDLE);
	}
}
#include "VulkanCommandBuffer.hpp"

#include "VulkanDebug.hpp"

namespace DadEngine::Rendering
{
	VulkanCommandBuffer::VulkanCommandBuffer(VkDevice _InDevice, VkCommandPool _InCommandPool/*, VkCommandBuffer _InPrimaryCmdBuffer*/, RenderContext * _InRenderContext)
		: CommandBuffer(_InRenderContext), m_Device(_InDevice), m_CommandPool(_InCommandPool)
	{
		VkCommandBufferAllocateInfo command_buffer_allocate_info = {};
		command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_allocate_info.pNext = VK_NULL_HANDLE;
		command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_allocate_info.commandPool = _InCommandPool;
		command_buffer_allocate_info.commandBufferCount = 1U;

		VK_CHECK_RESULT(vkAllocateCommandBuffers(_InDevice, &command_buffer_allocate_info, &m_CmdBuffer));
	}


	VulkanCommandBuffer::~VulkanCommandBuffer()
	{
		//vkFreeCommandBuffers(m_Device, m_CommandPool, 1U, &m_CmdBuffer);
	}
}
#ifndef __VULKAN_COMMAND_BUFFER_HPP_
#define __VULKAN_COMMAND_BUFFER_HPP_

#include "vulkan/vulkan.hpp"

#include "VulkanHelper.hpp"

#include "../../CommandBuffer.hpp"

namespace DadEngine::Rendering
{
	class VulkanCommandBuffer : public CommandBuffer
	{

	public:

		VulkanCommandBuffer(VkDevice _InDevice, VkCommandPool _InCommandPool)
		{
			Initialize(_InDevice, _InCommandPool);
		}

		// Initialize array element after allocation
		void Initialize(VkDevice _InDevice, VkCommandPool _InCommandPool)
		{
			VulkanHelper::CreateCommandBuffer(_InDevice, _InCommandPool, 1U, &m_cmdBuffer);
		}


		FORCE_INLINE void BeginRecord() override final
		{
			VkCommandBufferBeginInfo cmd_buffer_begin_info = {};
			cmd_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			cmd_buffer_begin_info.pNext = VK_NULL_HANDLE;
			cmd_buffer_begin_info.pInheritanceInfo = VK_NULL_HANDLE;
			cmd_buffer_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			vkBeginCommandBuffer(m_cmdBuffer, &cmd_buffer_begin_info);
		}

		FORCE_INLINE void EndRecord() override final
		{
			vkEndCommandBuffer(m_cmdBuffer);
		}


		VkCommandBuffer m_cmdBuffer = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_COMMAND_BUFFER_HPP_

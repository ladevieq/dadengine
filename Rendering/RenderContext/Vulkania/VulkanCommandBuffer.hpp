#ifndef __VULKAN_COMMAND_BUFFER_HPP_
#define __VULKAN_COMMAND_BUFFER_HPP_

#include "vulkan/vulkan.hpp"

#include "../../CommandBuffer.hpp"

#include "VulkanSwapchain.hpp"

namespace DadEngine::Rendering
{
	class VulkanCommandBuffer : public CommandBuffer
	{

	public:
		
		VulkanCommandBuffer()
			: CommandBuffer(nullptr)
		{};

		VulkanCommandBuffer(VkDevice _InDevice, VkCommandPool _InCommandPool/*, VkCommandBuffer _InPrimaryCmdBuffer*/, RenderContext* _InRenderContext);


		~VulkanCommandBuffer();


		FORCE_INLINE void BeginRecord() override final
		{
			/*VkCommandBufferInheritanceInfo command_buffer_inheritance_info = {};
			command_buffer_inheritance_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
			command_buffer_inheritance_info.pNext = VK_NULL_HANDLE;
			command_buffer_inheritance_info.*/

			VkCommandBufferBeginInfo cmd_buffer_begin_info = {};
			cmd_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			cmd_buffer_begin_info.pNext = VK_NULL_HANDLE;
			cmd_buffer_begin_info.pInheritanceInfo = VK_NULL_HANDLE;
			cmd_buffer_begin_info.flags = /*VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;*/VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			vkBeginCommandBuffer(m_CmdBuffer, &cmd_buffer_begin_info);
		}

		FORCE_INLINE void EndRecord() override final
		{
			vkEndCommandBuffer(m_CmdBuffer);

			m_ptrRenderContext->SubmitCommandBuffer(this);
		}


		VkDevice m_Device = VK_NULL_HANDLE;

		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
		VkCommandBuffer m_CmdBuffer = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_COMMAND_BUFFER_HPP_

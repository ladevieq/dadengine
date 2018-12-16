#include "VulkanCommandBuffer.hpp"

#include "../RenderContext.hpp"
#include "VulkanDebug.hpp"

namespace DadEngine::Rendering
{
    VulkanCommandBuffer::VulkanCommandBuffer()
		: CommandBuffer(nullptr)
	{
	};

    VulkanCommandBuffer::VulkanCommandBuffer(VkDevice _InDevice,
                                             VkCommandPool _InCommandPool /*, VkCommandBuffer _InPrimaryCmdBuffer*/,
                                             RenderContext *_InRenderContext)
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
        vkFreeCommandBuffers(m_Device, m_CommandPool, 1U, &m_CmdBuffer);
    }

    void VulkanCommandBuffer::BeginRecord()
    {
        /*VkCommandBufferInheritanceInfo command_buffer_inheritance_info = {};
        command_buffer_inheritance_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
        command_buffer_inheritance_info.pNext = VK_NULL_HANDLE;
        command_buffer_inheritance_info.*/

        VkCommandBufferBeginInfo cmd_buffer_begin_info = {};
        cmd_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmd_buffer_begin_info.pNext = VK_NULL_HANDLE;
        cmd_buffer_begin_info.pInheritanceInfo = VK_NULL_HANDLE;
        cmd_buffer_begin_info.flags =
            /*VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;*/ VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        vkBeginCommandBuffer(m_CmdBuffer, &cmd_buffer_begin_info);
    }

    void VulkanCommandBuffer::EndRecord()
    {
        vkEndCommandBuffer(m_CmdBuffer);

        m_ptrRenderContext->SubmitCommandBuffer(this);
    }
} // namespace DadEngine::Rendering
#ifndef __VULKAN_COMMAND_BUFFER_HPP_
#define __VULKAN_COMMAND_BUFFER_HPP_

#include <vulkan/vulkan.hpp>

#include "../../command-buffer.hpp"

namespace DadEngine::Rendering
{
    class RenderContext;

	class VulkanCommandBuffer : public CommandBuffer
	{

	public:
		
		VulkanCommandBuffer();

		VulkanCommandBuffer(VkDevice _InDevice, VkCommandPool _InCommandPool/*, VkCommandBuffer _InPrimaryCmdBuffer*/, RenderContext* _InRenderContext);


		~VulkanCommandBuffer();


		void BeginRecord() override final;

		void EndRecord() override final;


		VkDevice m_Device = VK_NULL_HANDLE;

		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
		VkCommandBuffer m_CmdBuffer = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_COMMAND_BUFFER_HPP_

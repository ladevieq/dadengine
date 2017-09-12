#ifndef __VULKAN_RENDER_CONTEXT_HPP_
#define __VULKAN_RENDER_CONTEXT_HPP_

// May be removed
#include <vulkan/vulkan.h>

#include "../RenderContext.hpp"
#include "../../Core/Core.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanHelper.hpp"


namespace DadEngine::Rendering
{
	struct VulkanImage
	{
		VkImage image;
		VkImageView view;
		VkDeviceMemory memory;
		VkFormat format;
	};

	class VulkanRenderContext : public RenderContext
	{

	public:

		VulkanRenderContext(PlatformWindow& _InWindow);
		~VulkanRenderContext();

		void ClearBuffer(Color& _InClearColor) override final;
		void Present() override final;


	private:

		void CreateInstance(PlatformWindow& _InWindow);

		void CreateDevice();

		void CreateCommandPool();

		void CreateCommandBuffers();

		void CreateSetupCommandBuffer();

		void GetQueues(); // Present and Graphics

		void GetPresentationMode(PlatformWindow& _InWindow);

		void DestroySetupCommandBuffer();

		void CreatePresentationSurface(PlatformWindow& _InWindow);

		void CreateDepthStencilBuffer();

		void CreateRenderpass();

		void CreateSemaphores();

		void CreatePipelineCache();

		void CreateFramebuffers();

		void RecordClearBuffers();


		uint32 m_uiGraphicsQueueFamilyIndex = 0U;
		uint32 m_uiPresentationsQueueFamilyIndex = 0U;

		VkInstance m_Instance = VK_NULL_HANDLE;
		VkDevice m_Device = VK_NULL_HANDLE; // Logical device
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties;

		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue m_PresentationQueue = VK_NULL_HANDLE;

		VkSemaphore m_ImageAvailableSemaphore = VK_NULL_HANDLE;
		VkSemaphore m_RenderingFinishedSemaphore = VK_NULL_HANDLE;

		VkCommandPool m_GraphicsCommandPool = VK_NULL_HANDLE;
		VkCommandPool m_PresentationCommandPool = VK_NULL_HANDLE;

		VkCommandBuffer m_setupCommandBuffer = VK_NULL_HANDLE;

		TArray<VkCommandBuffer> m_GraphicCommandBuffers;
		TArray<VkCommandBuffer> m_PresentationCommandBuffers;

		VulkanSwapchain m_Swapchain;

		VkSurfaceKHR m_PresentationSurface = VK_NULL_HANDLE;

		VkExtent2D m_windowExtent;

		VulkanImage m_depthStencilBuffer;

		VkRenderPass m_Renderpass = VK_NULL_HANDLE;

		VkPipelineCache m_PipelineChache = VK_NULL_HANDLE;

		VkPresentModeKHR m_PresentationMode;

		TArray<VkFramebuffer> m_Framebuffers;
	};
}

#endif //__VULKAN_RENDER_CONTEXT_HPP_
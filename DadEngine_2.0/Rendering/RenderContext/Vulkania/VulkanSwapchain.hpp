#ifndef __VULKAN_SWAPCHAIN_HPP_
#define __VULKAN_SWAPCHAIN_HPP_

#include "vulkan/vulkan.h"

#include "../../Core/Core.hpp"
#include "VulkanImage.hpp"
#include "VulkanHelper.hpp"


namespace DadEngine::Rendering
{

	/*struct SwapchainImage
	{
		VkImage image;
		VkImageView view;
	};*/

	class VulkanSwapchain
	{

	public:
		
		VulkanSwapchain() = default;

		~VulkanSwapchain();

		void Initialize(VkDevice& _InDevice, VkPhysicalDevice& _InPhysicalDevice, VkSurfaceKHR& _InSurface, VkPresentModeKHR& _InPresentationMode, PlatformWindow& _InWindow);


		void Present(VkQueue& _InQueue, VkSemaphore& _InRenderingFinishedSemaphore, uint32 _InImageIndex);


		uint32 GetNextImageIndex(VkSemaphore& _InImageAvailableSemaphore);

		FORCE_INLINE uint32 GetImageCount() { return (uint32)m_SwapchainImages.Size(); }

		FORCE_INLINE VkFormat GetFormat() { return m_surfaceFormat.format; }

		//TArray<SwapchainImage> m_SwapchainImages;
		TArray<VulkanImage> m_SwapchainImages;

		VkExtent2D m_SwapchainExtent;
		uint32 m_uiPresentQueueFamilyIndex = 0U;

	private:

		PFN_vkCreateSwapchainKHR CreateSwapchain = VK_NULL_HANDLE;
		PFN_vkDestroySwapchainKHR DestroySwapchain = VK_NULL_HANDLE;
		PFN_vkGetSwapchainImagesKHR GetSwapchainImages = VK_NULL_HANDLE;
		PFN_vkAcquireNextImageKHR AcquireNextImage = VK_NULL_HANDLE;
		PFN_vkQueuePresentKHR QueuePresent = VK_NULL_HANDLE;

		VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE;
		VkSurfaceFormatKHR m_surfaceFormat;

		VkDevice m_Device;
	};
}

#endif //__VULKAN_SWAPCHAIN_HPP_
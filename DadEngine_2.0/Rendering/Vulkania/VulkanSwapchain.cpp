#include "VulkanSwapchain.hpp"

namespace DadEngine::Rendering
{
	VulkanSwapchain::~VulkanSwapchain()
	{
		DestroySwapchain(m_Device, m_Swapchain, VK_NULL_HANDLE);
	}

	void VulkanSwapchain::Initialize(VkDevice& _InDevice, VkPhysicalDevice& _InPhysicalDevice, VkSurfaceKHR& _InSurface, VkPresentModeKHR& _InPresentationMode, PlatformWindow& _InWindow)
	{
		m_Device = _InDevice;

		CreateSwapchain = (PFN_vkCreateSwapchainKHR)vkGetDeviceProcAddr(_InDevice, "vkCreateSwapchainKHR");
		DestroySwapchain = (PFN_vkDestroySwapchainKHR)vkGetDeviceProcAddr(_InDevice, "vkDestroySwapchainKHR");
		SwapchainImages = (PFN_vkGetSwapchainImagesKHR)vkGetDeviceProcAddr(_InDevice, "vkGetSwapchainImagesKHR");
		AcquireNextImage = (PFN_vkAcquireNextImageKHR)vkGetDeviceProcAddr(_InDevice, "vkAcquireNextImageKHR");
		QueuePresent = (PFN_vkQueuePresentKHR)vkGetDeviceProcAddr(_InDevice, "vkQueuePresentKHR");

		uint32 supportedPresentationModesCount = 0U;

		vkGetPhysicalDeviceSurfacePresentModesKHR(_InPhysicalDevice, _InSurface, &supportedPresentationModesCount, VK_NULL_HANDLE);

		TArray<VkPresentModeKHR> supportedPresentationModes(supportedPresentationModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(_InPhysicalDevice, _InSurface, &supportedPresentationModesCount, supportedPresentationModes.GetData());


		// Get surface formats
		m_surfaceFormat = VulkanHelper::CheckSurfaceFormats(_InPhysicalDevice, _InSurface);

		// Check surface capabilities
		uint32 m_uiImageCount = 0U;
		VkSurfaceCapabilitiesKHR surface_capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_InPhysicalDevice, _InSurface, &surface_capabilities);

		m_uiImageCount = surface_capabilities.minImageCount + 1U;

		if (m_uiImageCount > surface_capabilities.maxImageCount && surface_capabilities.maxImageCount > 0U)
			m_uiImageCount = surface_capabilities.maxImageCount;


		if (surface_capabilities.currentExtent.width == -1)
		{
			m_SwapchainExtent.width = _InWindow.GetRect().right;
			m_SwapchainExtent.height = _InWindow.GetRect().bottom;
		}

		else
		{
			m_SwapchainExtent = surface_capabilities.currentExtent;
		}

		VkSwapchainCreateInfoKHR swapchain_create_info = {};
		swapchain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchain_create_info.pNext = VK_NULL_HANDLE;
		swapchain_create_info.imageFormat = m_surfaceFormat.format;
		swapchain_create_info.imageColorSpace = m_surfaceFormat.colorSpace;
		swapchain_create_info.imageArrayLayers = 1U;
		swapchain_create_info.imageExtent = m_SwapchainExtent;
		swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT /*| VK_IMAGE_USAGE_TRANSFER_DST_BIT*/; // /!\*
		swapchain_create_info.presentMode = _InPresentationMode;
		swapchain_create_info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		swapchain_create_info.oldSwapchain = m_Swapchain;
		swapchain_create_info.pQueueFamilyIndices = VK_NULL_HANDLE;
		swapchain_create_info.queueFamilyIndexCount = 0U;
		swapchain_create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchain_create_info.clipped = VK_TRUE;
		swapchain_create_info.surface = _InSurface;
		swapchain_create_info.minImageCount = m_uiImageCount;
		swapchain_create_info.flags = 0U;

		VK_CHECK_RESULT(CreateSwapchain(_InDevice, &swapchain_create_info, VK_NULL_HANDLE, &m_Swapchain));

		uint32 imageCount = 0U;
		SwapchainImages(m_Device, m_Swapchain, &imageCount, VK_NULL_HANDLE);

		TArray<VkImage> images(imageCount);
		VK_CHECK_RESULT(SwapchainImages(m_Device, m_Swapchain, &imageCount, images.GetData()));

		TArray<VkImageView> imageViews(imageCount);
		m_SwapchainImages.Resize(imageCount);

		for (size_t i = 0U; i < imageCount; i++)
		{
			VkImageViewCreateInfo image_view_create_info = {};
			image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			image_view_create_info.pNext = VK_NULL_HANDLE;
			image_view_create_info.image = images[i];
			image_view_create_info.format = m_surfaceFormat.format;
			image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			image_view_create_info.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G , VK_COMPONENT_SWIZZLE_B , VK_COMPONENT_SWIZZLE_A };
			image_view_create_info.subresourceRange.baseArrayLayer = 0U;
			image_view_create_info.subresourceRange.layerCount = 1U;
			image_view_create_info.subresourceRange.baseMipLevel = 0U;
			image_view_create_info.subresourceRange.levelCount = 1U;
			image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			image_view_create_info.flags = 0U;

			VK_CHECK_RESULT(vkCreateImageView(m_Device, &image_view_create_info, VK_NULL_HANDLE, &imageViews[i]));

			m_SwapchainImages[i] = { images[i] , imageViews[i] };
		}
	}


	void VulkanSwapchain::Present(VkQueue& _InQueue, VkSemaphore& _InRenderingFinishedSemaphore, VkSemaphore& _InImageAvailableSemaphore, uint32 _InImageIndex)
	{
		VkPresentInfoKHR present_info = {};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.pNext = VK_NULL_HANDLE;
		present_info.swapchainCount = 1U;
		present_info.pSwapchains = &m_Swapchain;
		present_info.waitSemaphoreCount = 1U;
		present_info.pWaitSemaphores = &_InRenderingFinishedSemaphore;
		present_info.pImageIndices = &_InImageIndex;
		present_info.pResults = VK_NULL_HANDLE;

		VK_CHECK_RESULT(QueuePresent(_InQueue, &present_info));
	}


	uint32 VulkanSwapchain::GetNextImageIndex(VkSemaphore& _InImageAvailableSemaphore)
	{
		// Need at least fence or semaphore
		AcquireNextImage(m_Device, m_Swapchain, UINT64_MAX, _InImageAvailableSemaphore, VK_NULL_HANDLE, &m_uiImageIndex);

		return m_uiImageIndex;
	}
}
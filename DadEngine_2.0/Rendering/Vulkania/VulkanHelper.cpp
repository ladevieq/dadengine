#include "VulkanHelper.hpp"

namespace DadEngine::Rendering::VulkanHelper
{
	void EnumerateInstanceLayersAndExtensions()
	{
		uint32 layerPropertiesCount = 0U;

		vkEnumerateInstanceLayerProperties(&layerPropertiesCount, VK_NULL_HANDLE);

		TArray<VkLayerProperties> layerProperties(layerPropertiesCount);

		vkEnumerateInstanceLayerProperties(&layerPropertiesCount, layerProperties.GetData());

		for (VkLayerProperties currentLayerProperties : layerProperties)
		{
			printf("%s: %s\n", currentLayerProperties.layerName, currentLayerProperties.description);

			uint32 extensionPropertiesCount = 0U;

			vkEnumerateInstanceExtensionProperties(currentLayerProperties.layerName, &extensionPropertiesCount, VK_NULL_HANDLE);

			TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

			vkEnumerateInstanceExtensionProperties(currentLayerProperties.layerName, &extensionPropertiesCount, extensionProperties.GetData());

			for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
			{
				printf("\t%s\n", currentExtensionPorperties.extensionName);
			}
		}

		uint32 extensionPropertiesCount = 0U;

		vkEnumerateInstanceExtensionProperties(NULL, &extensionPropertiesCount, VK_NULL_HANDLE);

		TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

		vkEnumerateInstanceExtensionProperties(NULL, &extensionPropertiesCount, extensionProperties.GetData());

		for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
		{
			printf("\n\t%s\n", currentExtensionPorperties.extensionName);
		}
	}

	void EnumerateDeviceLayersAndExtensions(VkPhysicalDevice& _InPhysicalDevice)
	{
		uint32 layerPropertiesCount = 0U;

		vkEnumerateDeviceLayerProperties(_InPhysicalDevice, &layerPropertiesCount, VK_NULL_HANDLE);

		TArray<VkLayerProperties> layerProperties(layerPropertiesCount);

		vkEnumerateDeviceLayerProperties(_InPhysicalDevice, &layerPropertiesCount, layerProperties.GetData());

		for (VkLayerProperties currentLayerProperties : layerProperties)
		{
			printf("%s: %s\n", currentLayerProperties.layerName, currentLayerProperties.description);

			uint32 extensionPropertiesCount = 0U;

			vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, currentLayerProperties.layerName, &extensionPropertiesCount, VK_NULL_HANDLE);

			TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

			vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, currentLayerProperties.layerName, &extensionPropertiesCount, extensionProperties.GetData());

			for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
			{
				printf("\t%s\n", currentExtensionPorperties.extensionName);
			}
		}

		uint32 extensionPropertiesCount = 0U;

		vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, NULL, &extensionPropertiesCount, VK_NULL_HANDLE);

		TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

		vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, NULL, &extensionPropertiesCount, extensionProperties.GetData());

		for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
		{
			printf("\n\t%s\n", currentExtensionPorperties.extensionName);
		}
	}

	void EnumerateDevices(VkInstance& _InInstance, TArray<VkPhysicalDevice>& _InPhysicalDevices)
	{
		uint32 physicalDevicesCount = 0U;

		vkEnumeratePhysicalDevices(_InInstance, &physicalDevicesCount, VK_NULL_HANDLE);

		_InPhysicalDevices.Resize(physicalDevicesCount);

		vkEnumeratePhysicalDevices(_InInstance, &physicalDevicesCount, _InPhysicalDevices.GetData());

		/*for (VkPhysicalDevice currentPhysicalDevice : _InPhysicalDevices)
		{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		VkPhysicalDeviceFeatures physicalDeviceFeatures;

		vkGetPhysicalDeviceProperties(currentPhysicalDevice, &physicalDeviceProperties);

		printf("%s%s\n", "Name: ", physicalDeviceProperties.deviceName);

		vkGetPhysicalDeviceFeatures(currentPhysicalDevice, &physicalDeviceFeatures);

		CheckDeviceQueueFamilyProperties(currentPhysicalDevice, VK_QUEUE_GRAPHICS_BIT);
		}*/
	}

	uint32 CheckDeviceQueueFamilyProperties(VkPhysicalDevice& _InPhysicalDevice, VkQueueFlags _InFlag)
	{
		uint32 queueFamilyPropertyCount = 0U;

		vkGetPhysicalDeviceQueueFamilyProperties(_InPhysicalDevice, &queueFamilyPropertyCount, VK_NULL_HANDLE);

		TArray<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(_InPhysicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.GetData());

		for (size_t i = 0U; i < queueFamilyProperties.Size(); i++)
		{
			if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & _InFlag)
			{
				return i;
			}
		}

		return 0U;
	}

	uint32 CheckMemoryType(uint32 _InMemoryTypeBits, VkFlags _InProperties, VkPhysicalDeviceMemoryProperties& _InPhysicalDeviceMemoryProperties)
	{
		for (size_t i = 0; i < 32U; i++)
		{
			if ((_InMemoryTypeBits & 1U) == 1U)
			{
				if (_InPhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & _InProperties)
				{
					return i;
				}

				else
				{
					//LOG_ASSERT(0, "Bad memory type");
				}
			}

			_InMemoryTypeBits >>= 1U;
		}

		return 0U;
	}

	VkSurfaceFormatKHR CheckSurfaceFormats(VkPhysicalDevice& _InPhysicalDevice, VkSurfaceKHR& _InSurface)
	{
		uint32 uiSurfaceFormatCount = 0U;
		vkGetPhysicalDeviceSurfaceFormatsKHR(_InPhysicalDevice, _InSurface, &uiSurfaceFormatCount, VK_NULL_HANDLE);

		TArray<VkSurfaceFormatKHR> surfaceFormats(uiSurfaceFormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(_InPhysicalDevice, _InSurface, &uiSurfaceFormatCount, surfaceFormats.GetData());

		if (surfaceFormats.Size() == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
		{
			return { VK_FORMAT_R8G8B8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
		}

		for (VkSurfaceFormatKHR currentSurfaceFormat : surfaceFormats)
		{
			if (currentSurfaceFormat.format == VK_FORMAT_R8G8B8A8_UNORM)
			{
				return currentSurfaceFormat;
			}
		}

		return surfaceFormats[0];
	}

	void CreateCommandBuffer(VkDevice& _InDevice, VkCommandPool& _InCommandPool, uint32 _InCount, VkCommandBuffer* _OutCommandBUffers)
	{
		VkCommandBufferAllocateInfo command_buffer_allocate_info = {};
		command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_allocate_info.pNext = VK_NULL_HANDLE;
		command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_allocate_info.commandPool = _InCommandPool;
		command_buffer_allocate_info.commandBufferCount = _InCount;

		VK_CHECK_RESULT(vkAllocateCommandBuffers(_InDevice, &command_buffer_allocate_info, _OutCommandBUffers));
	}

	VkExtent2D GetExtent2D(VkPhysicalDevice & _InPhysicalDevice, VkSurfaceKHR & _InSurface)
	{
		VkSurfaceCapabilitiesKHR surface_capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_InPhysicalDevice, _InSurface, &surface_capabilities);

		return surface_capabilities.currentExtent;
	}

	VkFormat GetSupportDepthStencilFormats(VkPhysicalDevice& _InPhysicalDevice)
	{
		TArray<VkFormat> depthStencilFormats;
		depthStencilFormats.Add(VK_FORMAT_D32_SFLOAT_S8_UINT);
		depthStencilFormats.Add(VK_FORMAT_D32_SFLOAT);
		depthStencilFormats.Add(VK_FORMAT_D24_UNORM_S8_UINT);
		depthStencilFormats.Add(VK_FORMAT_D16_UNORM_S8_UINT);
		depthStencilFormats.Add(VK_FORMAT_D16_UNORM);

		// Video 4 3:03:00
		for (VkFormat currentDepthStencilFormat : depthStencilFormats)
		{
			VkFormatProperties format_properties;

			vkGetPhysicalDeviceFormatProperties(_InPhysicalDevice, currentDepthStencilFormat, &format_properties);

			if (format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			{
				return currentDepthStencilFormat;
			}
		}
	}


	// Setting oldlayout to VK_IMAGE_LAYOUT_UNDEFINED invalidates image contents
	void SetImageLayout(VkCommandBuffer& _InCommandBuffer, VkImage& _InImage,
		VkImageLayout _InOldImageLayout, VkImageLayout _InNewImageLayout,
		VkPipelineStageFlags _InSrcPipilineStageFalgs, VkPipelineStageFlags _InDstPipilineStageFalgs)
	{
		VkImageMemoryBarrier image_memory_barrier = {};
		image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		image_memory_barrier.image = _InImage;
		image_memory_barrier.pNext = VK_NULL_HANDLE;
		image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier.oldLayout = _InOldImageLayout;
		image_memory_barrier.newLayout = _InNewImageLayout;
		image_memory_barrier.subresourceRange.baseArrayLayer = 0U;
		image_memory_barrier.subresourceRange.layerCount = 1U;
		image_memory_barrier.subresourceRange.baseMipLevel = 0U;
		image_memory_barrier.subresourceRange.levelCount = 1U;
		image_memory_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

		switch (_InOldImageLayout) {
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			image_memory_barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			image_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			image_memory_barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
			break;

		default:
			break;
		}

		switch (_InNewImageLayout) {
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			image_memory_barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			image_memory_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		default:
			break;
		}

		vkCmdPipelineBarrier(_InCommandBuffer, _InSrcPipilineStageFalgs, _InDstPipilineStageFalgs, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
	}
}
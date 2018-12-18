#include "VulkanHelper.hpp"

#include "VulkanImage.hpp"
#include "VulkanDebug.hpp"


namespace DadEngine::Rendering::VulkanHelper
{
	void EnumerateInstanceLayersAndExtensions()
	{
        uint32_t layerPropertiesCount = 0U;

		vkEnumerateInstanceLayerProperties(&layerPropertiesCount, VK_NULL_HANDLE);

		TArray<VkLayerProperties> layerProperties(layerPropertiesCount);

		vkEnumerateInstanceLayerProperties(&layerPropertiesCount, layerProperties.GetData());

		for (VkLayerProperties currentLayerProperties : layerProperties)
		{
			printf("%s: %s\n", currentLayerProperties.layerName, currentLayerProperties.description);

			uint32_t extensionPropertiesCount = 0U;

			vkEnumerateInstanceExtensionProperties(currentLayerProperties.layerName, &extensionPropertiesCount, VK_NULL_HANDLE);

			TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

			vkEnumerateInstanceExtensionProperties(currentLayerProperties.layerName, &extensionPropertiesCount, extensionProperties.GetData());

			for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
			{
				printf("\t%s\n", currentExtensionPorperties.extensionName);
			}
		}

		uint32_t extensionPropertiesCount = 0U;

		vkEnumerateInstanceExtensionProperties(NULL, &extensionPropertiesCount, VK_NULL_HANDLE);

		TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

		vkEnumerateInstanceExtensionProperties(NULL, &extensionPropertiesCount, extensionProperties.GetData());

		for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
		{
			printf("\n\t%s\n", currentExtensionPorperties.extensionName);
		}
	}

	void EnumerateDeviceLayersAndExtensions(VkPhysicalDevice _InPhysicalDevice)
	{
        uint32_t layerPropertiesCount = 0U;

		vkEnumerateDeviceLayerProperties(_InPhysicalDevice, &layerPropertiesCount, VK_NULL_HANDLE);

		TArray<VkLayerProperties> layerProperties(layerPropertiesCount);

		vkEnumerateDeviceLayerProperties(_InPhysicalDevice, &layerPropertiesCount, layerProperties.GetData());

		for (VkLayerProperties currentLayerProperties : layerProperties)
		{
			printf("%s: %s\n", currentLayerProperties.layerName, currentLayerProperties.description);

			uint32_t extensionPropertiesCount = 0U;

			vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, currentLayerProperties.layerName, &extensionPropertiesCount, VK_NULL_HANDLE);

			TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

			vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, currentLayerProperties.layerName, &extensionPropertiesCount, extensionProperties.GetData());

			for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
			{
				printf("\t%s\n", currentExtensionPorperties.extensionName);
			}
		}

		uint32_t extensionPropertiesCount = 0U;

		vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, NULL, &extensionPropertiesCount, VK_NULL_HANDLE);

		TArray<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

		vkEnumerateDeviceExtensionProperties(_InPhysicalDevice, NULL, &extensionPropertiesCount, extensionProperties.GetData());

		for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
		{
			printf("\n\t%s\n", currentExtensionPorperties.extensionName);
		}
	}

	void EnumerateDevices(VkInstance _InInstance, TArray<VkPhysicalDevice>& _InPhysicalDevices)
	{
        uint32_t physicalDevicesCount = 0U;

		vkEnumeratePhysicalDevices(_InInstance, &physicalDevicesCount, VK_NULL_HANDLE);

		_InPhysicalDevices.Resize(physicalDevicesCount);

		vkEnumeratePhysicalDevices(_InInstance, &physicalDevicesCount, _InPhysicalDevices.GetData());

		for (VkPhysicalDevice currentPhysicalDevice : _InPhysicalDevices)
		{
			VkPhysicalDeviceProperties physicalDeviceProperties;
			VkPhysicalDeviceFeatures physicalDeviceFeatures;

			vkGetPhysicalDeviceProperties(currentPhysicalDevice, &physicalDeviceProperties);

			printf("%s%s\n", "Name: ", physicalDeviceProperties.deviceName);

			vkGetPhysicalDeviceFeatures(currentPhysicalDevice, &physicalDeviceFeatures);

			CheckDeviceQueueFamilyProperties(currentPhysicalDevice, VK_QUEUE_GRAPHICS_BIT);
		}
	}

	uint32_t CheckDeviceQueueFamilyProperties(VkPhysicalDevice _InPhysicalDevice, VkQueueFlags _InFlag)
	{
        uint32_t queueFamilyPropertyCount = 0U;

		vkGetPhysicalDeviceQueueFamilyProperties(_InPhysicalDevice, &queueFamilyPropertyCount, VK_NULL_HANDLE);

		TArray<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(_InPhysicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.GetData());

		for (size_t i = 0U; i < queueFamilyProperties.Size(); i++)
		{
            if (queueFamilyProperties[(uint32_t)i].queueCount > 0 &&
                queueFamilyProperties[(uint32_t)i].queueFlags & _InFlag)
			{
                return (uint32_t)i;
			}
		}

		return 0U;
	}


	/*
		Return the index of the first memory type mathing the requirements

		@_InMemoryTypeBits	flag representing the wanted memory types
		@_InProperties		flag reprensenting the needed properties on the mem type
	*/
    uint32_t CheckMemoryTypeIndex(VkPhysicalDevice _InPhysicalDevice, uint32_t _InMemoryTypeBits, VkMemoryPropertyFlags _InProperties)
	{
		VkPhysicalDeviceMemoryProperties memory_properties;
		vkGetPhysicalDeviceMemoryProperties(_InPhysicalDevice, &memory_properties);

		// Loop throught the supported memory types
		for (size_t i = 0; i < memory_properties.memoryTypeCount; i++) {
			// Check that this mem type match the wanted mem types
			if ((_InMemoryTypeBits & (1U << i)))
			{
				// Check that this mem type has this properties
				if ((memory_properties.memoryTypes[i].propertyFlags & _InProperties) == _InProperties) {
					return (uint32_t)i;
				}
			}
		}

		return 0U;
	}

	VkSurfaceFormatKHR CheckSurfaceFormats(VkPhysicalDevice _InPhysicalDevice, VkSurfaceKHR _InSurface)
	{
        uint32_t uiSurfaceFormatCount = 0U;
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

	void CreateCommandBuffer(VkDevice _InDevice, VkCommandPool _InCommandPool, uint32_t _InCount, VkCommandBuffer *_OutCommandBuffers)
	{
		VkCommandBufferAllocateInfo command_buffer_allocate_info = {};
		command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_allocate_info.pNext = VK_NULL_HANDLE;
		command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_allocate_info.commandPool = _InCommandPool;
		command_buffer_allocate_info.commandBufferCount = _InCount;

		VK_CHECK_RESULT(vkAllocateCommandBuffers(_InDevice, &command_buffer_allocate_info, _OutCommandBuffers));
	}

	void CreateBuffer(VkDevice _InDevice, VkDeviceSize _InSize, VkBufferUsageFlags _InBufferUsage, VkBuffer& _OutBuffer) {
		VkBufferCreateInfo buffer_create_info = {};
		buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_create_info.pNext = VK_NULL_HANDLE;
		buffer_create_info.usage = _InBufferUsage;
		buffer_create_info.size = _InSize;
		buffer_create_info.queueFamilyIndexCount = 0U;				// Ignored as sharingMode is not VK_SHARING_MODE_CONCURRENT
		buffer_create_info.pQueueFamilyIndices = VK_NULL_HANDLE;	// Ignored as sharingMode is not VK_SHARING_MODE_CONCURRENT
		buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		buffer_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateBuffer(_InDevice, &buffer_create_info, VK_NULL_HANDLE, &_OutBuffer));
	}

	VkExtent2D GetExtent2D(VkPhysicalDevice _InPhysicalDevice, VkSurfaceKHR _InSurface)
	{
		VkSurfaceCapabilitiesKHR surface_capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_InPhysicalDevice, _InSurface, &surface_capabilities);

		return surface_capabilities.currentExtent;
	}

	VkFormat GetSupportDepthStencilFormats(VkPhysicalDevice _InPhysicalDevice)
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

		return VK_FORMAT_UNDEFINED;
	}


	// Setting oldlayout to VK_IMAGE_LAYOUT_UNDEFINED invalidates image contents
	void SetImageLayout(VkCommandBuffer _InCommandBuffer, VkImage _InImage,
		VkImageLayout _InOldImageLayout, VkImageLayout _InNewImageLayout,
		VkPipelineStageFlags _InSrcPipelineStageFlags, VkPipelineStageFlags _InDstPipelineStageFlags)
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

		vkCmdPipelineBarrier(_InCommandBuffer, _InSrcPipelineStageFlags, _InDstPipelineStageFlags, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);
	}

	void SetImageLayout(VkCommandBuffer _InCommandBuffer, VulkanImage& _InImage, VkImageLayout _InNewImageLayout,
		VkPipelineStageFlags _InSrcPipelineStageFlags, VkPipelineStageFlags _InDstPipelineStageFlags)
	{
		VkImageMemoryBarrier image_memory_barrier = {};
		image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		image_memory_barrier.image = _InImage.m_Image;
		image_memory_barrier.pNext = VK_NULL_HANDLE;
		image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier.oldLayout = _InImage.m_CurrentLayout;
		image_memory_barrier.newLayout = _InNewImageLayout;
		image_memory_barrier.subresourceRange.baseArrayLayer = 0U;
		image_memory_barrier.subresourceRange.layerCount = 1U;
		image_memory_barrier.subresourceRange.baseMipLevel = 0U;
		image_memory_barrier.subresourceRange.levelCount = 1U;
		image_memory_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT | VK_IMAGE_ASPECT_COLOR_BIT;

		switch (_InImage.m_CurrentLayout) {
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

		vkCmdPipelineBarrier(_InCommandBuffer, _InSrcPipelineStageFlags, _InDstPipelineStageFlags, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier);

		_InImage.m_CurrentLayout = _InNewImageLayout;
	}


	void AllocateBufferMemory(VkDevice _InDevice, VkPhysicalDevice _InPhysicalDevice, VkBuffer _InBuffer, VkMemoryPropertyFlags _InMemProperties, VkDeviceMemory& _OutMemory)
	{
		VkMemoryRequirements buffer_memory_requirements;
		vkGetBufferMemoryRequirements(_InDevice, _InBuffer, &buffer_memory_requirements);

		uint32_t memIndex =
        CheckMemoryTypeIndex(_InPhysicalDevice, buffer_memory_requirements.memoryTypeBits, _InMemProperties);

		VkMemoryAllocateInfo memory_allocate_info = {};
		memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memory_allocate_info.pNext = VK_NULL_HANDLE;
		memory_allocate_info.allocationSize = buffer_memory_requirements.size;
        memory_allocate_info.memoryTypeIndex = (uint32_t)memIndex;

		VK_CHECK_RESULT(vkAllocateMemory(_InDevice, &memory_allocate_info, VK_NULL_HANDLE, &_OutMemory));
	}
}
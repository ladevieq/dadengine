#include "vulkan-helper.hpp"

#include "vulkan-debug.hpp"
#include "vulkan-image.hpp"


namespace DadEngine::VulkanHelper
{
    void EnumerateInstanceLayersAndExtensions()
    {
        uint32_t layerPropertiesCount = 0U;

        vkEnumerateInstanceLayerProperties(&layerPropertiesCount, nullptr);

        std::vector<VkLayerProperties> layerProperties(layerPropertiesCount);

        vkEnumerateInstanceLayerProperties(&layerPropertiesCount,
                                           layerProperties.data());

        for (VkLayerProperties currentLayerProperties : layerProperties)
        {
            printf("%s: %s\n", currentLayerProperties.layerName,
                   currentLayerProperties.description);

            uint32_t extensionPropertiesCount = 0U;

            vkEnumerateInstanceExtensionProperties(currentLayerProperties.layerName,
                                                   &extensionPropertiesCount, nullptr);

            std::vector<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

            vkEnumerateInstanceExtensionProperties(currentLayerProperties.layerName,
                                                   &extensionPropertiesCount,
                                                   extensionProperties.data());

            for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
            {
                printf("\t%s\n", currentExtensionPorperties.extensionName);
            }
        }

        uint32_t extensionPropertiesCount = 0U;

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertiesCount, nullptr);

        std::vector<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertiesCount,
                                               extensionProperties.data());

        for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
        {
            printf("\n\t%s\n", currentExtensionPorperties.extensionName);
        }
    }

    void EnumerateDeviceLayersAndExtensions(VkPhysicalDevice _physicalDevice)
    {
        uint32_t layerPropertiesCount = 0U;

        vkEnumerateDeviceLayerProperties(_physicalDevice, &layerPropertiesCount, nullptr);

        std::vector<VkLayerProperties> layerProperties(layerPropertiesCount);

        vkEnumerateDeviceLayerProperties(_physicalDevice, &layerPropertiesCount,
                                         layerProperties.data());

        for (VkLayerProperties currentLayerProperties : layerProperties)
        {
            printf("%s: %s\n", currentLayerProperties.layerName,
                   currentLayerProperties.description);

            uint32_t extensionPropertiesCount = 0U;

            vkEnumerateDeviceExtensionProperties(_physicalDevice,
                                                 currentLayerProperties.layerName,
                                                 &extensionPropertiesCount, nullptr);

            std::vector<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

            vkEnumerateDeviceExtensionProperties(_physicalDevice,
                                                 currentLayerProperties.layerName,
                                                 &extensionPropertiesCount,
                                                 extensionProperties.data());

            for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
            {
                printf("\t%s\n", currentExtensionPorperties.extensionName);
            }
        }

        uint32_t extensionPropertiesCount = 0U;

        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr,
                                             &extensionPropertiesCount, nullptr);

        std::vector<VkExtensionProperties> extensionProperties(extensionPropertiesCount);

        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionPropertiesCount,
                                             extensionProperties.data());

        for (VkExtensionProperties currentExtensionPorperties : extensionProperties)
        {
            printf("\n\t%s\n", currentExtensionPorperties.extensionName);
        }
    }

    void EnumerateDevices(VkInstance _instance, std::vector<VkPhysicalDevice> &_physicalDevices)
    {
        uint32_t physicalDevicesCount = 0U;

        vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, nullptr);

        _physicalDevices.resize(physicalDevicesCount);

        vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount,
                                   _physicalDevices.data());

        for (VkPhysicalDevice currentPhysicalDevice : _physicalDevices)
        {
            VkPhysicalDeviceProperties physicalDeviceProperties;
            VkPhysicalDeviceFeatures physicalDeviceFeatures;

            vkGetPhysicalDeviceProperties(currentPhysicalDevice, &physicalDeviceProperties);

            printf("%s%s\n", "Name: ", physicalDeviceProperties.deviceName);

            vkGetPhysicalDeviceFeatures(currentPhysicalDevice, &physicalDeviceFeatures);

            CheckDeviceQueueFamilyProperties(currentPhysicalDevice, VK_QUEUE_GRAPHICS_BIT);
        }
    }

    uint32_t CheckDeviceQueueFamilyProperties(VkPhysicalDevice _physicalDevice, VkQueueFlags _flag)
    {
        uint32_t queueFamilyPropertyCount = 0U;

        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyPropertyCount,
                                                 nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);

        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyPropertyCount,
                                                 queueFamilyProperties.data());

        for (size_t i = 0U; i < queueFamilyProperties.size(); i++)
        {
            if (queueFamilyProperties[(uint32_t)i].queueCount > 0 &&
                queueFamilyProperties[(uint32_t)i].queueFlags & _flag)
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
    uint32_t CheckMemoryTypeIndex(VkPhysicalDevice _physicalDevice,
                                  uint32_t _memoryTypeBits,
                                  VkMemoryPropertyFlags _properties)
    {
        VkPhysicalDeviceMemoryProperties memory_properties;
        vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &memory_properties);

        // Loop throught the supported memory types
        for (size_t i = 0; i < memory_properties.memoryTypeCount; i++)
        {
            // Check that this mem type match the wanted mem types
            if ((_memoryTypeBits & (1U << i)))
            {
                // Check that this mem type has this properties
                if ((memory_properties.memoryTypes[i].propertyFlags & _properties) == _properties)
                {
                    return (uint32_t)i;
                }
            }
        }

        return 0U;
    }

    VkSurfaceFormatKHR CheckSurfaceFormats(VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface)
    {
        uint32_t uiSurfaceFormatCount = 0U;
        vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, _surface,
                                             &uiSurfaceFormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> surfaceFormats(uiSurfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, _surface, &uiSurfaceFormatCount,
                                             surfaceFormats.data());

        if (surfaceFormats.size() == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
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

    void CreateCommandBuffer(VkDevice _device,
                             VkCommandPool _commandPool,
                             uint32_t _count,
                             VkCommandBuffer *_commandBuffers)
    {
        VkCommandBufferAllocateInfo command_buffer_allocate_info = {};
        command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        command_buffer_allocate_info.pNext = nullptr;
        command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        command_buffer_allocate_info.commandPool = _commandPool;
        command_buffer_allocate_info.commandBufferCount = _count;

        VK_CHECK_RESULT(vkAllocateCommandBuffers(_device, &command_buffer_allocate_info,
                                                 _commandBuffers));
    }

    void CreateBuffer(VkDevice _device,
                      VkDeviceSize _size,
                      VkBufferUsageFlags _bufferUsage,
                      VkBuffer &_buffer)
    {
        VkBufferCreateInfo buffer_create_info = {};
        buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_create_info.pNext = nullptr;
        buffer_create_info.usage = _bufferUsage;
        buffer_create_info.size = _size;
        buffer_create_info.queueFamilyIndexCount =
            0U; // Ignored as sharingMode is not VK_SHARING_MODE_CONCURRENT
        buffer_create_info.pQueueFamilyIndices =
            nullptr; // Ignored as sharingMode is not VK_SHARING_MODE_CONCURRENT
        buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        buffer_create_info.flags = 0U;

        VK_CHECK_RESULT(vkCreateBuffer(_device, &buffer_create_info,
                                       nullptr, &_buffer));
    }

    VkExtent2D GetExtent2D(VkPhysicalDevice _physicalDevice, VkSurfaceKHR _surface)
    {
        VkSurfaceCapabilitiesKHR surface_capabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, _surface,
                                                  &surface_capabilities);

        return surface_capabilities.currentExtent;
    }

    VkFormat GetSupportDepthStencilFormats(VkPhysicalDevice _physicalDevice)
    {
        std::vector<VkFormat> depthStencilFormats;
        depthStencilFormats.push_back(VK_FORMAT_D32_SFLOAT_S8_UINT);
        depthStencilFormats.push_back(VK_FORMAT_D32_SFLOAT);
        depthStencilFormats.push_back(VK_FORMAT_D24_UNORM_S8_UINT);
        depthStencilFormats.push_back(VK_FORMAT_D16_UNORM_S8_UINT);
        depthStencilFormats.push_back(VK_FORMAT_D16_UNORM);

        // Video 4 3:03:00
        for (VkFormat currentDepthStencilFormat : depthStencilFormats)
        {
            VkFormatProperties format_properties;

            vkGetPhysicalDeviceFormatProperties(_physicalDevice, currentDepthStencilFormat,
                                                &format_properties);

            if (format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
            {
                return currentDepthStencilFormat;
            }
        }

        return VK_FORMAT_UNDEFINED;
    }


    // Setting oldlayout to VK_IMAGE_LAYOUT_UNDEFINED invalidates image contents
    void SetImageLayout(VkCommandBuffer _commandBuffer,
                        VkImage _image,
                        VkImageLayout _oldImageLayout,
                        VkImageLayout _newImageLayout,
                        VkPipelineStageFlags _srcPipelineStageFlags,
                        VkPipelineStageFlags _dstPipelineStageFlags)
    {
        VkImageMemoryBarrier image_memory_barrier = {};
        image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        image_memory_barrier.image = _image;
        image_memory_barrier.pNext = nullptr;
        image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        image_memory_barrier.oldLayout = _oldImageLayout;
        image_memory_barrier.newLayout = _newImageLayout;
        image_memory_barrier.subresourceRange.baseArrayLayer = 0U;
        image_memory_barrier.subresourceRange.layerCount = 1U;
        image_memory_barrier.subresourceRange.baseMipLevel = 0U;
        image_memory_barrier.subresourceRange.levelCount = 1U;
        image_memory_barrier.subresourceRange.aspectMask =
            VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

        switch (_oldImageLayout)
        {
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

        switch (_newImageLayout)
        {
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

        vkCmdPipelineBarrier(_commandBuffer, _srcPipelineStageFlags, _dstPipelineStageFlags,
                             0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier);
    }

    void SetImageLayout(VkCommandBuffer _commandBuffer,
                        VulkanImage &_image,
                        VkImageLayout _newImageLayout,
                        VkPipelineStageFlags _srcPipelineStageFlags,
                        VkPipelineStageFlags _dstPipelineStageFlags)
    {
        VkImageMemoryBarrier image_memory_barrier = {};
        image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        image_memory_barrier.image = _image.m_image;
        image_memory_barrier.pNext = nullptr;
        image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        image_memory_barrier.oldLayout = _image.m_currentLayout;
        image_memory_barrier.newLayout = _newImageLayout;
        image_memory_barrier.subresourceRange.baseArrayLayer = 0U;
        image_memory_barrier.subresourceRange.layerCount = 1U;
        image_memory_barrier.subresourceRange.baseMipLevel = 0U;
        image_memory_barrier.subresourceRange.levelCount = 1U;
        image_memory_barrier.subresourceRange.aspectMask =
            VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT | VK_IMAGE_ASPECT_COLOR_BIT;

        switch (_image.m_currentLayout)
        {
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

        switch (_newImageLayout)
        {
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

        vkCmdPipelineBarrier(_commandBuffer, _srcPipelineStageFlags, _dstPipelineStageFlags,
                             0, 0, nullptr, 0, nullptr, 1, &image_memory_barrier);

        _image.m_currentLayout = _newImageLayout;
    }


    void AllocateBufferMemory(VkDevice _device,
                              VkPhysicalDevice _physicalDevice,
                              VkBuffer _buffer,
                              VkMemoryPropertyFlags _memProperties,
                              VkDeviceMemory &_memory)
    {
        VkMemoryRequirements buffer_memory_requirements;
        vkGetBufferMemoryRequirements(_device, _buffer, &buffer_memory_requirements);

        uint32_t memIndex = CheckMemoryTypeIndex(_physicalDevice,
                                                 buffer_memory_requirements.memoryTypeBits,
                                                 _memProperties);

        VkMemoryAllocateInfo memory_allocate_info = {};
        memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memory_allocate_info.pNext = nullptr;
        memory_allocate_info.allocationSize = buffer_memory_requirements.size;
        memory_allocate_info.memoryTypeIndex = reinterpret_cast<uint32_t>(memIndex);

        VK_CHECK_RESULT(vkAllocateMemory(_device, &memory_allocate_info,
                                         nullptr, &_memory));
    }
} // namespace DadEngine

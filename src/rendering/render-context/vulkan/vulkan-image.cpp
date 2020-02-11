#include "vulkan-image.hpp"

#include "vulkan-debug.hpp"
#include "vulkan-helper.hpp"

namespace DadEngine::Rendering
{
    VulkanImage::VulkanImage(VkDevice _InDevice, VkFormat _InImageFormat, VkExtent2D &_InImageSize, VkImageUsageFlags _InImagUsage)
        : Image(*(Extent2D *)&_InImageSize), m_Device(_InDevice), m_Format(_InImageFormat),
          m_ImageUsage(_InImagUsage)
    {
    }

    VulkanImage::VulkanImage(VkDevice _InDevice,
                             VkPhysicalDevice _InPhysicalDevice,
                             VkCommandBuffer _InCommandBuffer,
                             VkFormat _InImageFormat,
                             VkImageUsageFlags _InImageUsage,
                             VkImageAspectFlags _InImageAspects,
                             VkImageLayout _InImageLayout,
                             VkExtent2D &_InImageSize,
                             size_t _InImageLayers)

        : Image(*(Extent2D *)&_InImageSize), m_Device(_InDevice), m_Format(_InImageFormat),
          m_CurrentLayout(_InImageLayout)
    {
        // Image handle creation
        VkImageCreateInfo image_create_info = {};
        image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_create_info.pNext = VK_NULL_HANDLE;
        image_create_info.arrayLayers = 1U;
        image_create_info.format = m_Format;
        image_create_info.mipLevels = 1U;
        image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_create_info.queueFamilyIndexCount = 0U;
        image_create_info.pQueueFamilyIndices = VK_NULL_HANDLE;
        image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        image_create_info.usage = _InImageUsage;
        image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_create_info.imageType = VK_IMAGE_TYPE_2D;
        image_create_info.extent = { _InImageSize.width, _InImageSize.height, (uint32_t)_InImageLayers };
        image_create_info.flags = 0U;

        VK_CHECK_RESULT(vkCreateImage(_InDevice, &image_create_info, VK_NULL_HANDLE, &m_Image));


        // Image memory allocation and binding
        VkMemoryRequirements memory_requierements = {};
        vkGetImageMemoryRequirements(_InDevice, m_Image, &memory_requierements);

        VkMemoryAllocateInfo memory_allocation_info = {};
        memory_allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memory_allocation_info.pNext = VK_NULL_HANDLE;
        memory_allocation_info.memoryTypeIndex =
            VulkanHelper::CheckMemoryTypeIndex(_InPhysicalDevice, memory_requierements.memoryTypeBits,
                                               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory_allocation_info.allocationSize = memory_requierements.size;

        VK_CHECK_RESULT(vkAllocateMemory(_InDevice, &memory_allocation_info, VK_NULL_HANDLE, &m_Memory));
        VK_CHECK_RESULT(vkBindImageMemory(_InDevice, m_Image, m_Memory, 0U));


        // ImageView handle creation
        VkImageViewCreateInfo image_view_create_info = {};
        image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_create_info.pNext = VK_NULL_HANDLE;
        image_view_create_info.format = m_Format;
        image_view_create_info.image = m_Image;
        image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_create_info.subresourceRange.baseArrayLayer = 0U;
        image_view_create_info.subresourceRange.layerCount = 1U;
        image_view_create_info.subresourceRange.baseMipLevel = 0U;
        image_view_create_info.subresourceRange.levelCount = 1U;
        image_view_create_info.subresourceRange.aspectMask = _InImageAspects;
        image_view_create_info.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
                                              VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
        image_view_create_info.flags = 0U;

        m_ImageSubresourceRange.aspectMask = _InImageAspects;
        m_ImageSubresourceRange.baseArrayLayer = 0U;
        m_ImageSubresourceRange.baseMipLevel = 0U;
        m_ImageSubresourceRange.layerCount = 1U;
        m_ImageSubresourceRange.levelCount = 1U;

        VK_CHECK_RESULT(vkCreateImageView(_InDevice, &image_view_create_info, VK_NULL_HANDLE, &m_View));

        VulkanHelper::SetImageLayout(_InCommandBuffer, m_Image, VK_IMAGE_LAYOUT_UNDEFINED,
                                     m_CurrentLayout, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                                     VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT);
    }

    VulkanImage::VulkanImage(VkDevice _InDevice,
                             VkPhysicalDevice _InPhysicalDevice,
                             VkFormat _InImageFormat,
                             VkImageUsageFlags _InImageUsage,
                             VkImageAspectFlags _InImageAspects,
                             VkExtent2D &_InImageSize,
                             size_t _InImageLayers)

        : Image(*(Extent2D *)&_InImageSize), m_Device(_InDevice), m_Format(_InImageFormat),
          m_CurrentLayout(VK_IMAGE_LAYOUT_UNDEFINED)
    {
        // Image handle creation
        VkImageCreateInfo image_create_info = {};
        image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_create_info.pNext = VK_NULL_HANDLE;
        image_create_info.arrayLayers = 1U;
        image_create_info.format = m_Format;
        image_create_info.mipLevels = 1U;
        image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_create_info.queueFamilyIndexCount = 0U;
        image_create_info.pQueueFamilyIndices = VK_NULL_HANDLE;
        image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        image_create_info.usage = _InImageUsage;
        image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_create_info.imageType = VK_IMAGE_TYPE_2D;
        image_create_info.extent = { _InImageSize.width, _InImageSize.height, (uint32_t)_InImageLayers };
        image_create_info.flags = 0U;

        VK_CHECK_RESULT(vkCreateImage(_InDevice, &image_create_info, VK_NULL_HANDLE, &m_Image));


        // Image memory allocation and binding
        VkMemoryRequirements memory_requierements = {};
        vkGetImageMemoryRequirements(_InDevice, m_Image, &memory_requierements);

        VkMemoryAllocateInfo memory_allocation_info = {};
        memory_allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memory_allocation_info.pNext = VK_NULL_HANDLE;
        memory_allocation_info.memoryTypeIndex =
            VulkanHelper::CheckMemoryTypeIndex(_InPhysicalDevice, memory_requierements.memoryTypeBits,
                                               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory_allocation_info.allocationSize = memory_requierements.size;

        VK_CHECK_RESULT(vkAllocateMemory(_InDevice, &memory_allocation_info, VK_NULL_HANDLE, &m_Memory));
        VK_CHECK_RESULT(vkBindImageMemory(_InDevice, m_Image, m_Memory, 0U));


        m_ImageSubresourceRange.aspectMask = _InImageAspects;
        m_ImageSubresourceRange.baseArrayLayer = 0U;
        m_ImageSubresourceRange.baseMipLevel = 0U;
        m_ImageSubresourceRange.layerCount = 1U;
        m_ImageSubresourceRange.levelCount = 1U;

        // ImageView handle creation
        VkImageViewCreateInfo image_view_create_info = {};
        image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_create_info.pNext = VK_NULL_HANDLE;
        image_view_create_info.format = m_Format;
        image_view_create_info.image = m_Image;
        image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        image_view_create_info.subresourceRange.baseArrayLayer = 0U;
        image_view_create_info.subresourceRange.layerCount = 1U;
        image_view_create_info.subresourceRange.baseMipLevel = 0U;
        image_view_create_info.subresourceRange.levelCount = 1U;
        image_view_create_info.subresourceRange.aspectMask = _InImageAspects;
        image_view_create_info.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
                                              VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
        image_view_create_info.flags = 0U;

        VK_CHECK_RESULT(vkCreateImageView(_InDevice, &image_view_create_info, VK_NULL_HANDLE, &m_View));
    }

    VulkanImage::VulkanImage(::VkDevice _InDevice,
                             ::VkImage _InImageHandle,
                             ::VkImageView _InImageViewHandle,
                             ::VkDeviceMemory _ImMemory,
                             ::VkFormat _InImageFormat,
                             ::VkExtent2D &_InImageSize,
                             ::VkImageSubresourceRange &_InImageSubresourceRange)
        : Image(*((Extent2D *)&_InImageSize)), m_Device(_InDevice), m_Image(_InImageHandle),
          m_View(_InImageViewHandle), m_Memory(_ImMemory), m_Format(_InImageFormat),
          m_ImageSubresourceRange(_InImageSubresourceRange)
    {
    }


    VulkanImage::~VulkanImage()
    {
        /*vkDestroyImage(m_Device, m_Image, VK_NULL_HANDLE);
        vkDestroyImageView(m_Device, m_View, VK_NULL_HANDLE);

        vkFreeMemory(m_Device, m_Memory, VK_NULL_HANDLE);*/
    }

} // namespace DadEngine::Rendering
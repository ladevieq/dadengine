#ifndef __VULKAN_IMAGE_HPP_
#define __VULKAN_IMAGE_HPP_

#include <vulkan/vulkan.h>

#include "../../image.hpp"

namespace DadEngine
{
    class VulkanImage : public Image
    {

        public:
        VulkanImage() = default;

        VulkanImage(VkDevice _InDevice, VkFormat _InImageFormat, VkExtent2D &_InImageSize, VkImageUsageFlags _InImagUsage);

        VulkanImage(VkDevice _InDevice,
                    VkPhysicalDevice _InPhysicalDevice,
                    VkCommandBuffer _InCommandBuffer,
                    VkFormat _InImageFormat,
                    VkImageUsageFlags _InImageUsage,
                    VkImageAspectFlags _InImageAspects,
                    VkImageLayout _InImageLayout,
                    VkExtent2D &_InImageSize,
                    size_t _InImageLayers);

        VulkanImage(VkDevice _InDevice,
                    VkPhysicalDevice _InPhysicalDevice,
                    VkFormat _InImageFormat,
                    VkImageUsageFlags _InImageUsage,
                    VkImageAspectFlags _InImageAspects,
                    VkExtent2D &_InImageSize,
                    size_t _InImageLayers);


        VulkanImage(VkDevice _InDevice,
                    VkImage _InImageHandle,
                    VkImageView _InImageViewHandle,
                    VkDeviceMemory _ImMemory,
                    VkFormat _InImageFormat,
                    VkExtent2D &_InImageSize,
                    VkImageSubresourceRange &_InImageSubresourceRange);


        ~VulkanImage();


        VkDevice m_device = nullptr;

        VkImage m_image = nullptr;
        VkImageView m_view = nullptr;

        VkDeviceMemory m_memory = nullptr;
        VkFormat m_format = VK_FORMAT_UNDEFINED;
        VkImageLayout m_currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkImageSubresourceRange m_imageSubresourceRange = {};

        VkImageUsageFlags m_imageUsage = 0U;
        VkImageAspectFlags m_imageAspect = 0U;
        // VkClearColorValue
    };
} // namespace DadEngine

#endif //!__VULKAN_IMAGE_HPP_


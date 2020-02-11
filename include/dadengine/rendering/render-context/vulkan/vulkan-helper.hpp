#ifndef __VULKAN_HELPER_HPP_
#define __VULKAN_HELPER_HPP_

#include <vulkan/vulkan.h>

#include <cstdint>
#include <vector>


namespace DadEngine
{
    class VulkanImage;

    namespace VulkanHelper
    {
        void EnumerateDevices(VkInstance _instance,
                              std::vector<VkPhysicalDevice> &_physicalDevices);

        void EnumerateInstanceLayersAndExtensions();

        void EnumerateDeviceLayersAndExtensions(VkPhysicalDevice _physicalDevice);

        uint32_t CheckDeviceQueueFamilyProperties(VkPhysicalDevice _physicalDevice,
                                                  VkQueueFlags _flag);

        uint32_t CheckMemoryTypeIndex(VkPhysicalDevice _physicalDevice,
                                      uint32_t _memoryTypeBits,
                                      VkMemoryPropertyFlags _properties);

        VkSurfaceFormatKHR CheckSurfaceFormats(VkPhysicalDevice _physicalDevice,
                                               VkSurfaceKHR _surface);

        void CreateCommandBuffer(VkDevice _device,
                                 VkCommandPool _commandPool,
                                 uint32_t _count,
                                 VkCommandBuffer *_commandBuffers);

        void CreateBuffer(VkDevice _device,
                          VkDeviceSize _size,
                          VkBufferUsageFlags _bufferUsage,
                          VkBuffer &_buffer);

        VkExtent2D GetExtent2D(VkPhysicalDevice _device, VkSurfaceKHR _surface);

        VkFormat GetSupportDepthStencilFormats(VkPhysicalDevice _device);

        void SetImageLayout(VkCommandBuffer _commandBuffer,
                            VkImage _image,
                            VkImageLayout _oldImageLayout,
                            VkImageLayout _newImageLayout,
                            VkPipelineStageFlags _srcPipilineStageFalgs,
                            VkPipelineStageFlags _dstPipilineStageFalgs);

        void SetImageLayout(VkCommandBuffer _commandBuffer,
                            VulkanImage &_image,
                            VkImageLayout _newImageLayout,
                            VkPipelineStageFlags _srcPipilineStageFalgs,
                            VkPipelineStageFlags _dstPipilineStageFalgs);

        void AllocateBufferMemory(VkDevice _device,
                                  VkPhysicalDevice _physicalDevice,
                                  VkBuffer _buffer,
                                  VkMemoryPropertyFlags _memProperties,
                                  VkDeviceMemory &_memory);
    } // namespace VulkanHelper
} // namespace DadEngine

#endif //__VULKAN_HELPER_HPP_


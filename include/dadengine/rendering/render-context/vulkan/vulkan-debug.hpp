#ifndef __VULKAN_DEBUG_HPP_
#define __VULKAN_DEBUG_HPP_

#include <vulkan/vulkan.h>

#define VK_CHECK_RESULT(result) \
    if (result != VK_SUCCESS)   \
    throw

namespace DadEngine
{
    VkBool32 VKAPI_PTR MessageCallback(VkDebugReportFlagsEXT _flag,
                                       VkDebugReportObjectTypeEXT _objectType,
                                       uint64_t _srcObject,
                                       size_t _memoryLocation,
                                       int32_t _messageCode,
                                       const char *_prefixLayer,
                                       const char *_message,
                                       void *_userData);

    void InitializeVulkanDebug(VkInstance &_instance);

    void DestroyVulkanDebug(VkInstance &_instance);
} // namespace DadEngine::Rendering::VulkanDebug

#endif //__VULKAN_DEBUG_HPP_

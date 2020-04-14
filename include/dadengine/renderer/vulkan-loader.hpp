#pragma once

#include <optional>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

#if defined(WINDOWS)
#include <Windows.h>
#include <windowsx.h>

#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.h>

#define VULKAN_EXPORTED_FUNCTIONS \
    X(vkGetInstanceProcAddr)      \
    X(vkGetDeviceProcAddr)

#define VULKAN_APPLICATION_FUNCTIONS          \
    X(vkCreateInstance)                       \
    X(vkEnumerateInstanceVersion)             \
    X(vkEnumerateInstanceExtensionProperties) \
    X(vkEnumerateInstanceLayerProperties)

#define VULKAN_INSTANCE_FUNCTIONS                \
    X(vkDestroyInstance)                         \
    X(vkEnumeratePhysicalDevices)                \
    X(vkGetPhysicalDeviceProperties)             \
    X(vkGetPhysicalDeviceFeatures)               \
    X(vkGetPhysicalDeviceQueueFamilyProperties)  \
    X(vkCreateDevice)                            \
    X(vkEnumerateDeviceExtensionProperties)      \
    X(vkDestroySurfaceKHR)                       \
    X(vkGetPhysicalDeviceSurfaceSupportKHR)      \
    X(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) \
    X(vkGetPhysicalDeviceSurfaceFormatsKHR)      \
    X(vkGetPhysicalDeviceSurfacePresentModesKHR) \
    X(vkCreateDebugUtilsMessengerEXT)            \
    X(vkDestroyDebugUtilsMessengerEXT)

#if defined(WINDOWS)
#define PLATFORM_VULKAN_INSTANCE_FUNCTIONS X(vkCreateWin32SurfaceKHR)
#else
#define PLATFORM_VULKAN_INSTANCE_FUNCTIONS
#endif

#define VULKAN_DEVICE_FUNCTIONS \
    X(vkGetDeviceQueue)         \
    X(vkDestroyDevice)          \
    X(vkDeviceWaitIdle)         \
    X(vkCreateSwapchainKHR)     \
    X(vkGetSwapchainImagesKHR)  \
    X(vkAcquireNextImageKHR)    \
    X(vkDestroySwapchainKHR)    \
    X(vkQueuePresentKHR)        \
    X(vkCreateSemaphore)        \
    X(vkDestroySemaphore)

namespace DadEngine
{
    struct VulkanContext
    {
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
    };

#define X(name) extern PFN_##name name;
    VULKAN_EXPORTED_FUNCTIONS
    VULKAN_APPLICATION_FUNCTIONS
    VULKAN_INSTANCE_FUNCTIONS
    PLATFORM_VULKAN_INSTANCE_FUNCTIONS
    VULKAN_DEVICE_FUNCTIONS
#undef X


#define X(name) void Load_##name();
    VULKAN_EXPORTED_FUNCTIONS
    VULKAN_APPLICATION_FUNCTIONS
#undef X

#define X(name) void Load_##name(VkInstance _instance);
    VULKAN_INSTANCE_FUNCTIONS
    PLATFORM_VULKAN_INSTANCE_FUNCTIONS
#undef X

#define X(name) void Load_##name(VkDevice _device);
    VULKAN_DEVICE_FUNCTIONS
#undef X

    void LoadVulkan();

    std::optional<VkInstance> CreateInstance(std::vector<const char *> &_requiredLayers,
                                             std::vector<const char *> &_requiredExtensions);

    int32_t GetQueueFamilyIndex(VkPhysicalDevice _physicalDevice,
                                VkQueueFlags _requiredQueueFlags);
    int32_t GetPresentationQueueIndex(VkPhysicalDevice _physicalDevice,
                                      VkSurfaceKHR _presentationSurface);

    // TODO: Move this to vulkan helper file
    std::optional<VkPhysicalDevice>
    SelectPhysicalDevice(VkInstance _instance,
                         VkQueueFlags _requiredQueueFlags,
                         std::vector<const char *> &_requiredExtensions,
                         VkSurfaceKHR _presentationSurface);

    std::optional<VkDevice> CreateDevice(VkPhysicalDevice _physicalDevice,
                                         std::vector<uint32_t> &_queueFamiliesIndices,
                                         std::vector<const char *> &_requiredExtensions);

} // namespace DadEngine

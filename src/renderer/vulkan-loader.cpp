#include "vulkan-loader.hpp"

#include <cstdint>
#include <cstring>

#include <optional>
#include <vector>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

#if defined(WINDOWS)
HMODULE vulkanLibrary = LoadLibrary("vulkan-1.dll");

#define LoadProcAddress GetProcAddress
#endif

namespace DadEngine
{
#define X(name) PFN_##name name;
    VULKAN_EXPORTED_FUNCTIONS
    VULKAN_APPLICATION_FUNCTIONS
    VULKAN_INSTANCE_FUNCTIONS
    PLATFORM_VULKAN_INSTANCE_FUNCTIONS
    VULKAN_DEVICE_FUNCTIONS
#undef X

#define X(name)                                                                     \
    void Load_##name()                                                              \
    {                                                                               \
        name = reinterpret_cast<PFN_##name>(LoadProcAddress(vulkanLibrary, #name)); \
        if (!name) {                                                                \
            printf("%s%s\n", "Cannot load vulkan function ", #name);                \
        }                                                                           \
    }
    VULKAN_EXPORTED_FUNCTIONS
#undef X

#define X(name)                                                                     \
    void Load_##name()                                                              \
    {                                                                               \
        name = reinterpret_cast<PFN_##name>(vkGetInstanceProcAddr(nullptr, #name)); \
        if (!name) {                                                                \
            printf("%s%s\n", "Cannot load vulkan function ", #name);                \
        }                                                                           \
    }
    VULKAN_APPLICATION_FUNCTIONS
#undef X

#define X(name)                                                                       \
    void Load_##name(VkInstance _instance)                                            \
    {                                                                                 \
        name = reinterpret_cast<PFN_##name>(vkGetInstanceProcAddr(_instance, #name)); \
        if (!name) {                                                                  \
            printf("%s%s\n", "Cannot load vulkan function ", #name);                  \
        }                                                                             \
    }
    VULKAN_INSTANCE_FUNCTIONS
    PLATFORM_VULKAN_INSTANCE_FUNCTIONS
#undef X

#define X(name)                                                                   \
    void Load_##name(VkDevice _device)                                            \
    {                                                                             \
        name = reinterpret_cast<PFN_##name>(vkGetDeviceProcAddr(_device, #name)); \
        if (!name) {                                                              \
            printf("%s%s\n", "Cannot load vulkan function ", #name);              \
        }                                                                         \
    }
    VULKAN_DEVICE_FUNCTIONS
#undef X

    void LoadVulkan()
    {
#define X(name) Load_##name();
        VULKAN_EXPORTED_FUNCTIONS
        VULKAN_APPLICATION_FUNCTIONS
#undef X
    };

    VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT _severity,
                                                 VkDebugUtilsMessageTypeFlagsEXT _type,
                                                 const VkDebugUtilsMessengerCallbackDataEXT *_data,
                                                 void *_userData)
    {
        printf("%s\n", _data->pMessage);
        return VK_FALSE;
    }


    std::optional<VkInstance> CreateInstance(std::vector<const char *> &_requiredLayers,
                                             std::vector<const char *> &_requiredExtensions)
    {
        uint32_t apiVersion;
        vkEnumerateInstanceVersion(&apiVersion);

#if defined(_DEBUG)
        printf("Creating Vulkan instance");
        printf("Vulkan API Version : %d.%d.%d\n", VK_VERSION_MAJOR(apiVersion),
               VK_VERSION_MINOR(apiVersion), VK_VERSION_PATCH(apiVersion));
#endif

        // Extensions
        uint32_t supportedExtensionsCount = 0;
        uint32_t extensionsCount          = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

        if (extensionsCount) {
            std::vector<VkExtensionProperties> extensions(extensionsCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount,
                                                   extensions.data());
            for (auto &extension : extensions) {
                for (auto &requiredExtensions : _requiredExtensions) {
                    if (strcmp(requiredExtensions, extension.extensionName) == 0) {
                        supportedExtensionsCount++;
                        break;
                    }
                }
            }
        }

        if (supportedExtensionsCount < _requiredExtensions.size()) {
            printf("Some needed extensions are not supported\n");
            return std::nullopt;
        }

        // Layers
        uint32_t supportedLayersCount = 0;
        uint32_t layersCount          = 0;
        vkEnumerateInstanceLayerProperties(&layersCount, nullptr);

        if (layersCount) {
            std::vector<VkLayerProperties> layers(layersCount);
            vkEnumerateInstanceLayerProperties(&layersCount, layers.data());

            // TODO: Support layer extensions
            for (auto &layer : layers) {

                uint32_t layerExtensionsCount = 0;
                vkEnumerateInstanceExtensionProperties(layer.layerName,
                                                       &layerExtensionsCount, nullptr);

                if (layerExtensionsCount) {
                    std::vector<VkExtensionProperties> layerExtensions(layerExtensionsCount);
                    vkEnumerateInstanceExtensionProperties(layer.layerName, &layerExtensionsCount,
                                                           layerExtensions.data());
                    for (auto &extension : layerExtensions) {
                        for (auto &requiredExtensions : _requiredExtensions) {
                            if (strcmp(requiredExtensions, extension.extensionName) == 0) {
                                supportedExtensionsCount++;
                                break;
                            }
                        }
                    }
                }

                for (auto &requiredLayer : _requiredLayers) {
                    if (strcmp(requiredLayer, layer.layerName) == 0) {
                        supportedLayersCount++;
                        break;
                    }
                }
            }
        }

        if (supportedLayersCount < _requiredLayers.size()) {
            printf("Some required layers are not supported\n");
            return std::nullopt;
        }


        // Instance creation
        VkApplicationInfo appInfo {
            VK_STRUCTURE_TYPE_APPLICATION_INFO,
            nullptr,
            "DadEngine Main Instance",
            VK_MAKE_VERSION(1, 0, 0),
            "DadEngine",
            VK_MAKE_VERSION(0, 0, 1),
            apiVersion,
        };

        VkInstanceCreateInfo instanceCreateInfo {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            nullptr,
            0,
            &appInfo,
            static_cast<uint32_t>(_requiredLayers.size()),
            _requiredLayers.data(),
            static_cast<uint32_t>(_requiredExtensions.size()),
            _requiredExtensions.data(),
        };

        VkInstance instance;
        if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
            printf("Failed to create a Vulkan instance !\n");
            return std::nullopt;
        }

#define X(name) Load_##name(instance);
        VULKAN_INSTANCE_FUNCTIONS
        PLATFORM_VULKAN_INSTANCE_FUNCTIONS
#undef X

        VkDebugUtilsMessengerEXT debugMessenger;
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengeCreateInfo {
            VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            nullptr,
            0,
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
            DebugCallback,
            nullptr,
        };

        vkCreateDebugUtilsMessengerEXT(instance, &debugUtilsMessengeCreateInfo,
                                       nullptr, &debugMessenger);

        return std::optional(instance);
    }


    /**
     * Does this physical device support those flags and presentation surface
     */
    bool CheckQueueFamilyCapabilities(VkPhysicalDevice _physicalDevice,
                                      VkQueueFlags _requiredQueueFlags,
                                      VkSurfaceKHR _presentationSurface)
    {
        VkQueueFlags supportQueueFlags = 0;
        uint32_t supportPresentation   = false;
        uint32_t queueFamilyCount      = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount, nullptr);

        if (queueFamilyCount) {
            std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount,
                                                     queueFamilyProperties.data());

            for (size_t queueFamilyIndex = 0;
                 queueFamilyIndex < queueFamilyCount; queueFamilyIndex++) {
                auto familyProperties = queueFamilyProperties[queueFamilyIndex];
                uint32_t queueSupportPresentation = false;

                if (familyProperties.queueCount) {
                    supportQueueFlags |= familyProperties.queueFlags;
                }

                vkGetPhysicalDeviceSurfaceSupportKHR(_physicalDevice, queueFamilyIndex,
                                                     _presentationSurface,
                                                     &queueSupportPresentation);

                supportPresentation |= queueSupportPresentation;
            }
        }

        return supportQueueFlags & _requiredQueueFlags && supportPresentation;
    }

    /**
     * This function should be used to query family index, one flag at a time
     * unless you know you will get a queue supporting the whole flag
     * \return a queue index when a queue support your needs, -1 otherwise
     */
    int32_t GetQueueFamilyIndex(VkPhysicalDevice _physicalDevice, VkQueueFlags _requiredQueueFlags)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount,
                                                 queueFamilyProperties.data());

        for (size_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount;
             queueFamilyIndex++) {
            auto familyProperties = queueFamilyProperties[queueFamilyIndex];

            if (familyProperties.queueCount && familyProperties.queueFlags & _requiredQueueFlags) {
                return queueFamilyIndex;
            }
        }

        printf("No capable queues were found !\n");
        return -1;
    }

    int32_t GetPresentationQueueIndex(VkPhysicalDevice _physicalDevice, VkSurfaceKHR _presentationSurface)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyCount,
                                                 queueFamilyProperties.data());

        for (size_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount;
             queueFamilyCount++) {
            uint32_t supportPresentation;

            vkGetPhysicalDeviceSurfaceSupportKHR(_physicalDevice, queueFamilyIndex,
                                                 _presentationSurface, &supportPresentation);

            if (supportPresentation) {
                return queueFamilyIndex;
            }
        }

        printf("No presentation capable queues were found !\n");
        return -1;
    }


    bool CheckPhysicalDeviceExtensionsSupport(VkPhysicalDevice _physicalDevice,
                                              std::vector<const char *> &_requiredExtensions)
    {
        uint32_t supportedExtensionsCount = 0;
        uint32_t extensionsCount          = 0;
        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr,
                                             &extensionsCount, nullptr);

        if (extensionsCount) {
            std::vector<VkExtensionProperties> extensions(extensionsCount);
            vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr,
                                                 &extensionsCount, extensions.data());

            for (auto &extension : extensions) {
                for (auto &requiredExtension : _requiredExtensions) {
                    if (strcmp(requiredExtension, extension.extensionName) == 0) {
                        supportedExtensionsCount++;
                        break;
                    }
                }
            }
        }

        return supportedExtensionsCount == _requiredExtensions.size();
    } // namespace DadEngine

    /**
     * Return a physical device that fit the required capabilities
     * TODO: Move elsewhere
     * \param[in] _instance
     * \param[in] _requiredQueueFlags support only one flag for now
     * \param[in] _requiredExtensions
     * \param[in] _presentationSurface
     * \return a physical device fitting our needs (e.g queue capabilities)
     */
    std::optional<VkPhysicalDevice>
    SelectPhysicalDevice(VkInstance _instance,
                         VkQueueFlags _requiredQueueFlags,
                         std::vector<const char *> &_requiredExtensions,
                         VkSurfaceKHR _presentationSurface)
    {
        VkPhysicalDevice physicalDevice = nullptr;

        uint32_t physicalDevicesCount = 0;
        vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, nullptr);

        if (physicalDevicesCount) {
            std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
            vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount,
                                       physicalDevices.data());

            for (auto &currentPhysicalDevice : physicalDevices) {
                bool supportQueueCapabilities
                    = CheckQueueFamilyCapabilities(currentPhysicalDevice, _requiredQueueFlags,
                                                   _presentationSurface);

                bool supportExtensions
                    = CheckPhysicalDeviceExtensionsSupport(currentPhysicalDevice,
                                                           _requiredExtensions);

                if (supportQueueCapabilities && supportExtensions) {
                    return currentPhysicalDevice;
                }
            }

            if (!physicalDevice) {
                printf("Cannot find a suitable physical device !\n");
                return std::nullopt;
            }
        }

        printf("No physical devices found !\n");
        return std::nullopt;
    }

    std::optional<VkDevice> CreateDevice(VkPhysicalDevice _physicalDevice,
                                         std::vector<uint32_t> &_queueFamiliesIndices,
                                         std::vector<const char *> &_requiredExtensions)
    {
        std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos;
        std::vector<float> queuePriorities { 1.f };

        for (auto queueFamilyIndex : _queueFamiliesIndices) {
            VkDeviceQueueCreateInfo queueCreateInfo {
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                nullptr,
                0,
                queueFamilyIndex,
                static_cast<uint32_t>(queuePriorities.size()),
                queuePriorities.data()
            };

            deviceQueueCreateInfos.emplace_back(queueCreateInfo);
        }

        // Device layers are deprecated
        // https://github.com/KhronosGroup/Vulkan-Loader/blob/master/loader/LoaderAndLayerInterface.md#application-layer-usage
        VkDeviceCreateInfo deviceCreateInfo {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            nullptr,
            0,
            static_cast<uint32_t>(deviceQueueCreateInfos.size()),
            deviceQueueCreateInfos.data(),
            0,
            nullptr,
            static_cast<uint32_t>(_requiredExtensions.size()),
            _requiredExtensions.data(),
            nullptr
        };

        VkDevice device;
        if (DadEngine::vkCreateDevice(_physicalDevice, &deviceCreateInfo, nullptr, &device)
            != VK_SUCCESS) {
            printf("Failed to create logical device !\n");
            return std::nullopt;
        }

#define X(name) Load_##name(device);
        VULKAN_DEVICE_FUNCTIONS
#undef X

        return std::optional(device);
    }
}; // namespace DadEngine

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <limits>
#include <numeric>

#include "camera/camera.hpp"
#include "math/matrix/matrix4x4.hpp"
#include "model/model.hpp"
#include "window/window.hpp"

#include "loaders/gltf-loader.hpp"

using namespace DadEngine;

#if defined(OPENGL)

#include "renderer/opengl-loader.hpp"
#include "renderer/opengl-renderer.hpp"

int main()
{
    Application app { { "DadViewer", 1280, 720 } };
    OpenGLRenderer renderer { app.GetWindow(), true };
    std::string shaderName = "default";
    OpenGLShader shader    = renderer.RegisterShader(shaderName);
    RECT rect              = app.GetWindow().GetRect();
    float aspect = static_cast<float>(rect.right) / static_cast<float>(rect.bottom);
    Camera camera(Vector3(2.f, 1.f, 0.f), Vector3(-1.f, 1.f, 0.f), aspect);

    std::filesystem::path modelPath("../data/sponza/Sponza.gltf");
    Mesh sponza = LoadGLTF(modelPath)[0];

    Matrix4x4 model;
    model.m_11 = 0.008f;
    model.m_22 = 0.008f;
    model.m_33 = 0.008f;

    while (app.GetWindow().IsOpen()) {
        app.GetWindow().MessagePump();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader.programID);

        // printf("%d\n", glGetUniformLocation(shader.programID, "baseColorFactor"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "baseColorTexture"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "metallicFactor"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "roughnessFactor"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "metallicRoughnessTexture"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "normalScale"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "normalTexture"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "occlusionStrength"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "occlusionTexture"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "emissiveFactor"));
        // printf("%d\n", glGetUniformLocation(shader.programID, "emissiveTexture"));

        GLint viewLocation = glGetUniformLocation(shader.programID, "view");
        GLint projectionLocation
            = glGetUniformLocation(shader.programID, "projection");
        GLint modelLocation = glGetUniformLocation(shader.programID, "model");
        GLint cameraPositionLocation
            = glGetUniformLocation(shader.programID, "cameraPosition");

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE,
                           reinterpret_cast<float *>(&camera.view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE,
                           reinterpret_cast<float *>(&camera.projection));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, reinterpret_cast<float *>(&model));
        glUniform4fv(cameraPositionLocation, 1,
                     reinterpret_cast<float *>(&camera.position));

        sponza.Render();

        renderer.Present();
    }

    return 0;
}
#else

#include "renderer/vulkan-loader.hpp"

#define VMA_IMPLEMENTATION
#include <VulkanMemoryAllocator/vk_mem_alloc.h>

inline std::optional<VkSwapchainKHR> CreateSwapchain(VkDevice _device,
                                                     VkPhysicalDevice _physicalDevice,
                                                     VkSurfaceKHR _presentationSurface,
                                                     VkSwapchainKHR _oldSwapchain)
{
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_physicalDevice, _presentationSurface,
                                              &surfaceCapabilities);

    uint32_t surfaceFormatCount = 0;

    vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, _presentationSurface,
                                         &surfaceFormatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(_physicalDevice, _presentationSurface,
                                         &surfaceFormatCount, surfaceFormats.data());

    VkSurfaceFormatKHR surfaceFormat = surfaceFormats[0];

    if (surfaceFormatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED) {
        surfaceFormat = { VK_FORMAT_R8G8B8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
    }
    else {
        for (auto &currentSurfaceFormat : surfaceFormats) {
            if (currentSurfaceFormat.format == VK_FORMAT_R8G8B8A8_UNORM) {
                surfaceFormat = currentSurfaceFormat;
                break;
            }
        }
    }

    uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
    if (surfaceCapabilities.maxImageCount) {
        imageCount = std::min(imageCount, surfaceCapabilities.maxImageCount);
    }

    VkExtent2D imageExtent = surfaceCapabilities.currentExtent;

    if (imageExtent.height == std::numeric_limits<uint32_t>::max()) {
        // TODO: Take client rect ??
        imageExtent = surfaceCapabilities.minImageExtent;
    }

    VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
                                   & surfaceCapabilities.supportedUsageFlags;

    uint32_t presentModesCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(_physicalDevice, _presentationSurface,
                                              &presentModesCount, nullptr);

    std::vector<VkPresentModeKHR> presentModes(presentModesCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(_physicalDevice, _presentationSurface,
                                              &presentModesCount, presentModes.data());

    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
    for (auto &currentPresentMode : presentModes) {
        if (currentPresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
            break;
        }
    }


    // Swapchain creation
    VkSwapchainCreateInfoKHR swapchainCreateInfo { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                                                   nullptr,
                                                   0,
                                                   _presentationSurface,
                                                   imageCount,
                                                   surfaceFormat.format,
                                                   surfaceFormat.colorSpace,
                                                   imageExtent,
                                                   1,
                                                   imageUsage,
                                                   VK_SHARING_MODE_EXCLUSIVE,
                                                   0,
                                                   nullptr,
                                                   surfaceCapabilities.currentTransform,
                                                   VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                                                   presentMode,
                                                   VK_TRUE,
                                                   _oldSwapchain };

    VkSwapchainKHR swapchain;
    if (vkCreateSwapchainKHR(_device, &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS) {
        printf("Failed to create a swapchain !\n");
    }

    return std::optional(swapchain);
}

VkInstance instance;
VkPhysicalDevice physicalDevice;
VkDevice device;
VkSwapchainKHR swapchain;
VkSemaphore imageAvailableSemaphore;
VkSemaphore renderingFinishedSemaphore;

inline void SetupVulkan(Window &_window)
{
    LoadVulkan();

    std::vector<const char *> neededInstanceLayers
        = { "VK_LAYER_KHRONOS_validation" };
    std::vector<const char *> neededInstanceExtensions
        = { VK_KHR_SURFACE_EXTENSION_NAME,
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#if defined(WINDOWS)
            VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
          };

    instance = CreateInstance(neededInstanceLayers, neededInstanceExtensions).value();

    VkSurfaceKHR presentationSurface;

#if defined(WINDOWS)
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo {
        VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, nullptr, 0,
        _window.GetWindowHInstance(), _window.GetWindowHandle()
    };

    if (vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, nullptr, &presentationSurface)
        != VK_SUCCESS) {
        printf("Failed to create win32 surface\n");
    }
#endif

    std::vector<const char *> requiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    auto requiredQueueFlags = VK_QUEUE_GRAPHICS_BIT;

    physicalDevice = SelectPhysicalDevice(instance, requiredQueueFlags,
                                          requiredDeviceExtensions, presentationSurface)
                         .value();

    int32_t graphicsQueueIndex = GetQueueFamilyIndex(physicalDevice, requiredQueueFlags);
    int32_t presentationQueueIndex
        = GetPresentationQueueIndex(physicalDevice, presentationSurface);
    std::vector<uint32_t> queueFamilyIndices;

    if (graphicsQueueIndex == presentationQueueIndex) {
        queueFamilyIndices.emplace_back(graphicsQueueIndex);
    }
    else {
        queueFamilyIndices.emplace_back(static_cast<uint32_t>(graphicsQueueIndex));
        queueFamilyIndices.emplace_back(static_cast<uint32_t>(presentationQueueIndex));
    }

    device = CreateDevice(physicalDevice, queueFamilyIndices, requiredDeviceExtensions)
                 .value();

    swapchain
        = CreateSwapchain(device, physicalDevice, presentationSurface, nullptr).value();

    VkSemaphoreCreateInfo semaphoreCreateInfo { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                                                nullptr, 0 };

    vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &imageAvailableSemaphore);
    vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &renderingFinishedSemaphore);
}

void Draw()
{
    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, swapchain, std::numeric_limits<uint64_t>::max(),
                          imageAvailableSemaphore, nullptr, &imageIndex);
}

int main()
{
    Application app { { "DadViewer", 1280, 720 } };
    RECT rect = app.GetWindow().GetRect();
    float aspect = static_cast<float>(rect.right) / static_cast<float>(rect.bottom);
    Camera camera(Vector3(2.f, 1.f, 0.f), Vector3(-1.f, 1.f, 0.f), aspect);

    SetupVulkan(app.GetWindow());
    // std::filesystem::path modelPath("../data/sponza/Sponza.gltf");
    // Mesh sponza = LoadGLTF(modelPath)[0];

    Matrix4x4 model;

    model.SetIdentity();
    model.m_11 = 0.008f;
    model.m_22 = 0.008f;
    model.m_33 = 0.008f;

    while (app.GetWindow().IsOpen()) {
        app.GetWindow().MessagePump();
    }

    return 0;
}
#endif

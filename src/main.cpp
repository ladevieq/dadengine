#include <cmath>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <limits>
#include <numeric>
#include <vulkan/vulkan_core.h>

#include "camera/camera.hpp"
#include "helpers/file.hpp"
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

#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

VkFormat SwapchainFormat;
VkExtent2D SwapchainImagesSize;

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

    SwapchainFormat = surfaceFormat.format;

    uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
    if (surfaceCapabilities.maxImageCount) {
        imageCount = std::min(imageCount, surfaceCapabilities.maxImageCount);
    }

    VkExtent2D imageExtent = surfaceCapabilities.currentExtent;

    if (imageExtent.height == std::numeric_limits<uint32_t>::max()) {
        // TODO: Take client rect ??
        imageExtent = surfaceCapabilities.minImageExtent;
    }

    SwapchainImagesSize = imageExtent;

    VkImageUsageFlags imageUsage
        = (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT)
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

VkInstance Instance;
VkPhysicalDevice PhysicalDevice;
VkDevice Device;
VkSwapchainKHR Swapchain;
uint32_t GraphicsQueueIndex            = 0;
uint32_t PresentationQueueIndex        = 0;
VkQueue GraphicsQueue                  = nullptr;
VkQueue PresentationQueue              = nullptr;
VkCommandPool GraphicsQueueCmdPool     = nullptr;
VkCommandPool PresentationQueueCmdPool = nullptr;
VkShaderModule VertexShaderModule      = nullptr;
VkShaderModule FragmentShaderModule    = nullptr;
VkRenderPass RenderPass                = nullptr;
VkPipeline GraphicsPipeline            = nullptr;
VmaAllocator Allocator                 = nullptr;
VkClearValue ClearValue { { { 0.f, 1.f, 0.f, 1.f } } };


// Define each rendering ressources count
// CommandBuffers, Framebuffers, Fences, etc
uint32_t VirtualFramesCount = 3;

// Rendering ressources
std::vector<VkCommandBuffer> GraphicsCommandBuffers { VirtualFramesCount };
std::vector<VkCommandBuffer> PresentationCommandBuffers { VirtualFramesCount };
std::vector<VkImage> SwapchainImages { VirtualFramesCount };
std::vector<VkFramebuffer> Framebuffers { VirtualFramesCount };
std::vector<VkImageView> SwapchainImagesViews { VirtualFramesCount };
std::vector<VkFence> GraphicsCommandBuffersFences { VirtualFramesCount };
std::vector<VkSemaphore> ImageAvailableSemaphores { VirtualFramesCount };
std::vector<VkSemaphore> QueueProcessingFinishedSemaphores { VirtualFramesCount };

std::vector<Vertex> VB {
    {
        { -0.7f, -0.7f, 0.f },
        { 1.f, 0.f, 0.f },
    },
    {
        { -0.7f, 0.7f, 0.f },
        { 0.f, 1.f, 0.f },
    },
    {
        { 0.7f, -0.7f, 0.f },
        { 0.f, 0.f, 1.f },
    },
    {
        { 0.7f, 0.7f, 0.f },
        { 0.f, 0.f, 0.f },
    },
};
VkBuffer VertexBufferHandle                 = nullptr;
VmaAllocation VertexBufferAllocation        = nullptr;
VkBuffer StagingVertexBufferHandle          = nullptr;
VmaAllocation StagingVertexBufferAllocation = nullptr;

std::vector<uint32_t> IB {
    0, 1, 2, 1, 3, 2,
};
VkBuffer IndexBufferHandle                 = nullptr;
VmaAllocation IndexBufferAllocation        = nullptr;
VkBuffer StagingIndexBufferHandle          = nullptr;
VmaAllocation StagingIndexBufferAllocation = nullptr;

inline void CreateFramebuffer(uint32_t _virtualFrameIndex);

inline void RecordCommands(uint32_t _virtualFrameIndex)
{
    if (Framebuffers[_virtualFrameIndex] != VK_NULL_HANDLE) {
        vkDestroyFramebuffer(Device, Framebuffers[_virtualFrameIndex], nullptr);
    }

    CreateFramebuffer(_virtualFrameIndex);


    VkCommandBufferBeginInfo commandBufferBeginInfo {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr,
        VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr
    };


    vkBeginCommandBuffer(GraphicsCommandBuffers[_virtualFrameIndex], &commandBufferBeginInfo);

    VkImageSubresourceRange imageSubresourceRange { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    // Change ressource queue ownership
    if (GraphicsQueueIndex != PresentationQueueIndex) {
        VkImageMemoryBarrier barrierFromPresentToRenderpass {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            nullptr,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            PresentationQueueIndex,
            GraphicsQueueIndex,
            SwapchainImages[_virtualFrameIndex],
            imageSubresourceRange
        };

        vkCmdPipelineBarrier(GraphicsCommandBuffers[_virtualFrameIndex],
                             VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                             VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &barrierFromPresentToRenderpass);
    }


    VkRenderPassBeginInfo renderPassBeginInfo {
        VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        nullptr,
        RenderPass,
        Framebuffers[_virtualFrameIndex],
        { {
              0,
              0,
          },
          { SwapchainImagesSize.width, SwapchainImagesSize.height } },
        1,
        &ClearValue
    };

    vkCmdBeginRenderPass(GraphicsCommandBuffers[_virtualFrameIndex],
                         &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(GraphicsCommandBuffers[_virtualFrameIndex],
                      VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);

    VkDeviceSize offset = 0;
    vkCmdBindIndexBuffer(GraphicsCommandBuffers[_virtualFrameIndex],
                         IndexBufferHandle, offset, VK_INDEX_TYPE_UINT32);
    vkCmdBindVertexBuffers(GraphicsCommandBuffers[_virtualFrameIndex], 0, 1,
                           &VertexBufferHandle, &offset);
    // vkCmdDraw(GraphicsCommandBuffers[_virtualFrameIndex], 3, 1, 0, 0);
    vkCmdDrawIndexed(GraphicsCommandBuffers[_virtualFrameIndex], 6, 1, 0, 0, 0);

    vkCmdEndRenderPass(GraphicsCommandBuffers[_virtualFrameIndex]);


    // Change ressource queue ownership
    if (GraphicsQueueIndex != PresentationQueueIndex) {
        VkImageMemoryBarrier barrierFromRenderpassToPresent {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            nullptr,
            VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            GraphicsQueueIndex,
            PresentationQueueIndex,
            SwapchainImages[_virtualFrameIndex],
            imageSubresourceRange
        };

        vkCmdPipelineBarrier(GraphicsCommandBuffers[_virtualFrameIndex],
                             VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                             VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr,
                             0, nullptr, 1, &barrierFromRenderpassToPresent);
    }

    vkEndCommandBuffer(GraphicsCommandBuffers[_virtualFrameIndex]);
}

inline void CreateRenderpass()
{
    std::vector<VkAttachmentDescription> attachementsDescriptions {
        { 0, SwapchainFormat, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_CLEAR,
          VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
          VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR }
    };

    std::vector<VkAttachmentReference> colorAttachmentsReferences {
        { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL }
    };

    // Memory dependencies between subpasses (image memory barrier
    std::vector<VkSubpassDependency> subpassesDependencies {
        { VK_SUBPASS_EXTERNAL, 0, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
          VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_ACCESS_MEMORY_READ_BIT,
          VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_DEPENDENCY_BY_REGION_BIT },
        { 0, VK_SUBPASS_EXTERNAL, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
          VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
          VK_ACCESS_MEMORY_READ_BIT, VK_DEPENDENCY_BY_REGION_BIT }
    };

    VkSubpassDescription subpassDescription { 0,
                                              VK_PIPELINE_BIND_POINT_GRAPHICS,
                                              0,
                                              nullptr,
                                              static_cast<uint32_t>(
                                                  colorAttachmentsReferences.size()),
                                              colorAttachmentsReferences.data(),
                                              nullptr,
                                              nullptr,
                                              0,
                                              nullptr };
    std::vector<VkSubpassDescription> subpassesDescriptions { subpassDescription };

    VkRenderPassCreateInfo renderPassCreateInfo {
        VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        nullptr,
        0,
        static_cast<uint32_t>(attachementsDescriptions.size()),
        attachementsDescriptions.data(),
        static_cast<uint32_t>(subpassesDescriptions.size()),
        subpassesDescriptions.data(),
        static_cast<uint32_t>(subpassesDependencies.size()),
        subpassesDependencies.data()
    };

    if (vkCreateRenderPass(Device, &renderPassCreateInfo, nullptr, &RenderPass) != VK_SUCCESS) {
        printf("Failed to create render pass !\n");
    }
}

inline void CreateFramebuffer(uint32_t _virtualFrameIndex)
{
    VkFramebufferCreateInfo framebufferCreateInfo { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                                                    nullptr,
                                                    0,
                                                    RenderPass,
                                                    1,
                                                    &SwapchainImagesViews[_virtualFrameIndex],
                                                    SwapchainImagesSize.width,
                                                    SwapchainImagesSize.height,
                                                    1 };

    vkCreateFramebuffer(Device, &framebufferCreateInfo, nullptr,
                        &Framebuffers[_virtualFrameIndex]);
}

inline void CreatePipeline()
{
    std::vector<uint8_t> vertexShaderCode
        = DadEngine::ReadFile("../data/shaders/easy.vert.spv");

    VkShaderModuleCreateInfo vertexShaderModuleCreateInfo {
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, nullptr, 0,
        vertexShaderCode.size() - 1,
        reinterpret_cast<uint32_t *>(vertexShaderCode.data())
    };

    vkCreateShaderModule(Device, &vertexShaderModuleCreateInfo, nullptr, &VertexShaderModule);

    auto fragmentShaderCode
        = DadEngine::ReadFile("../data/shaders/easy.frag.spv");

    VkShaderModuleCreateInfo fragmentShaderModuleCreateInfo {
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, nullptr, 0,
        fragmentShaderCode.size() - 1,
        reinterpret_cast<uint32_t *>(fragmentShaderCode.data())
    };

    vkCreateShaderModule(Device, &fragmentShaderModuleCreateInfo, nullptr, &FragmentShaderModule);

    std::vector<VkPipelineShaderStageCreateInfo> shaderStagesCreateInfos {
        { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0,
          VK_SHADER_STAGE_VERTEX_BIT, VertexShaderModule, "main", nullptr },
        { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0,
          VK_SHADER_STAGE_FRAGMENT_BIT, FragmentShaderModule, "main", nullptr }
    };


    // Define vertex buffer layout ??
    std::vector<VkVertexInputBindingDescription> vertexBindingsDescriptions {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    };
    std::vector<VkVertexInputAttributeDescription> vertexInputAttributesDescriptions {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) }
    };

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        nullptr,
        0,
        static_cast<uint32_t>(vertexBindingsDescriptions.size()),
        vertexBindingsDescriptions.data(),
        static_cast<uint32_t>(vertexInputAttributesDescriptions.size()),
        vertexInputAttributesDescriptions.data()
    };

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, nullptr, 0,
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE
    };


    VkViewport viewport { 0.f,
                          0.f,
                          static_cast<float>(SwapchainImagesSize.width),
                          static_cast<float>(SwapchainImagesSize.height),
                          0.f,
                          1.f };

    VkRect2D scissor { {
                           static_cast<int32_t>(0.f),
                           static_cast<int32_t>(0.f),
                       },
                       { SwapchainImagesSize.width, SwapchainImagesSize.height } };

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, nullptr, 0, 1, &viewport, 1, &scissor
    };


    VkPipelineRasterizationStateCreateInfo raterizationStateCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_FALSE,
        VK_FALSE,
        VK_POLYGON_MODE_FILL,
        VK_CULL_MODE_BACK_BIT,
        VK_FRONT_FACE_COUNTER_CLOCKWISE,
        VK_FALSE,
        0.f,
        0.f,
        0.f,
        1.f
    };


    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_SAMPLE_COUNT_1_BIT,
        VK_FALSE,
        1.f,
        nullptr,
        VK_FALSE,
        VK_FALSE
    };


    VkPipelineColorBlendAttachmentState colorBlendAttachmentState {
        VK_FALSE,
        VK_BLEND_FACTOR_ONE,
        VK_BLEND_FACTOR_ZERO,
        VK_BLEND_OP_ADD,
        VK_BLEND_FACTOR_ONE,
        VK_BLEND_FACTOR_ZERO,
        VK_BLEND_OP_ADD,
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
    };

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        nullptr,
        0,
        VK_FALSE,
        VK_LOGIC_OP_COPY,
        1,
        &colorBlendAttachmentState,
        { 0.f, 0.f, 0.f, 0.f }
    };


    VkPipelineLayoutCreateInfo layoutCreateInfo {
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, nullptr, 0, 0, nullptr, 0, nullptr
    };

    VkPipelineLayout layout;
    vkCreatePipelineLayout(Device, &layoutCreateInfo, nullptr, &layout);

    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo {
        VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        nullptr,
        0,
        static_cast<uint32_t>(shaderStagesCreateInfos.size()),
        shaderStagesCreateInfos.data(),
        &vertexInputStateCreateInfo,
        &inputAssemblyStateCreateInfo,
        nullptr,
        &viewportStateCreateInfo,
        &raterizationStateCreateInfo,
        &multisampleStateCreateInfo,
        nullptr,
        &colorBlendStateCreateInfo,
        nullptr,
        layout,
        RenderPass,
        0,
        VK_NULL_HANDLE,
        -1
    };

    if (vkCreateGraphicsPipelines(Device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo,
                                  nullptr, &GraphicsPipeline)
        != VK_SUCCESS) {
        printf("Failed to create graphics pipeline !");
    }
}

void CreateVertexBuffer()
{
    // Device vertex buffer
    VkDeviceSize bufferSize = VB.size() * sizeof(Vertex);
    VkBufferCreateInfo bufferCreateInfo { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                          nullptr,
                                          0,
                                          bufferSize,
                                          VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                                          VK_SHARING_MODE_EXCLUSIVE,
                                          0,
                                          nullptr };

    VmaAllocationCreateInfo allocationCreateInfo {};
    allocationCreateInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

    vmaCreateBuffer(Allocator, &bufferCreateInfo, &allocationCreateInfo,
                    &VertexBufferHandle, &VertexBufferAllocation, nullptr);

    // Staging vertex buffer
    VkBufferCreateInfo stagingBufferCreateInfo { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                                 nullptr,
                                                 0,
                                                 bufferSize,
                                                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT, // No need to specify vertex buffer bit a this buffer won't be bound as vertex buffer
                                                 VK_SHARING_MODE_EXCLUSIVE,
                                                 0,
                                                 nullptr };

    VmaAllocationCreateInfo stagingAllocationCreateInfo {};
    stagingAllocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;

    vmaCreateBuffer(Allocator, &stagingBufferCreateInfo, &stagingAllocationCreateInfo,
                    &StagingVertexBufferHandle, &StagingVertexBufferAllocation, nullptr);

    void *deviceMemory = nullptr;
    vmaMapMemory(Allocator, StagingVertexBufferAllocation, &deviceMemory);
    memcpy(deviceMemory, VB.data(), bufferSize);
    vmaUnmapMemory(Allocator, StagingVertexBufferAllocation);


    // Copy staging buffer content to vertex buffer
    VkCommandBufferBeginInfo beginInfo
        = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr,
            VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr };

    vkWaitForFences(Device, 1, &GraphicsCommandBuffersFences[0], VK_TRUE,
                    std::numeric_limits<uint64_t>::max());
    vkResetFences(Device, 1, &GraphicsCommandBuffersFences[0]);

    vkBeginCommandBuffer(GraphicsCommandBuffers[0], &beginInfo);

    VkBufferCopy bufferCopy { 0, 0, bufferSize };
    vkCmdCopyBuffer(GraphicsCommandBuffers[0], StagingVertexBufferHandle,
                    VertexBufferHandle, 1, &bufferCopy);

    VkBufferMemoryBarrier bufferMemoryBarrier { VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
                                                nullptr,
                                                VK_ACCESS_MEMORY_WRITE_BIT,
                                                VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
                                                GraphicsQueueIndex,
                                                GraphicsQueueIndex,
                                                VertexBufferHandle,
                                                0,
                                                bufferSize };

    vkCmdPipelineBarrier(GraphicsCommandBuffers[0], VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, 0, 0, nullptr, 1,
                         &bufferMemoryBarrier, 0, nullptr);

    vkEndCommandBuffer(GraphicsCommandBuffers[0]);

    VkSubmitInfo submitInfo {
        VK_STRUCTURE_TYPE_SUBMIT_INFO, nullptr, 0,      nullptr, nullptr, 1,
        &GraphicsCommandBuffers[0],    0,       nullptr
    };

    vkQueueSubmit(GraphicsQueue, 1, &submitInfo, GraphicsCommandBuffersFences[0]);
}

void CreateIndexBuffer()
{
    VkDeviceSize bufferSize = IB.size() * sizeof(uint32_t);
    VkBufferCreateInfo bufferCreateInfo { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                          nullptr,
                                          0,
                                          bufferSize,
                                          VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                                          VK_SHARING_MODE_EXCLUSIVE,
                                          0,
                                          nullptr };

    VmaAllocationCreateInfo allocationCreateInfo {};
    allocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    vmaCreateBuffer(Allocator, &bufferCreateInfo, &allocationCreateInfo,
                    &IndexBufferHandle, &IndexBufferAllocation, nullptr);


    // Staging index buffer
    VkBufferCreateInfo stagingBufferCreateInfo { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                                 nullptr,
                                                 0,
                                                 bufferSize,
                                                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT, // No need to specify vertex buffer bit a this buffer won't be bound as vertex buffer
                                                 VK_SHARING_MODE_EXCLUSIVE,
                                                 0,
                                                 nullptr };

    VmaAllocationCreateInfo stagingAllocationCreateInfo {};
    stagingAllocationCreateInfo.usage = VMA_MEMORY_USAGE_CPU_ONLY;

    vmaCreateBuffer(Allocator, &stagingBufferCreateInfo, &stagingAllocationCreateInfo,
                    &StagingIndexBufferHandle, &StagingIndexBufferAllocation, nullptr);

    void *deviceMemory = nullptr;
    vmaMapMemory(Allocator, StagingIndexBufferAllocation, &deviceMemory);
    memcpy(deviceMemory, IB.data(), bufferSize);
    vmaUnmapMemory(Allocator, StagingIndexBufferAllocation);


    // Copy staging buffer content to vertex buffer
    VkCommandBufferBeginInfo beginInfo
        = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr,
            VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr };

    vkWaitForFences(Device, 1, &GraphicsCommandBuffersFences[0], VK_TRUE,
                    std::numeric_limits<uint64_t>::max());
    vkResetFences(Device, 1, &GraphicsCommandBuffersFences[0]);

    vkBeginCommandBuffer(GraphicsCommandBuffers[0], &beginInfo);

    VkBufferCopy bufferCopy { 0, 0, bufferSize };
    vkCmdCopyBuffer(GraphicsCommandBuffers[0], StagingIndexBufferHandle,
                    IndexBufferHandle, 1, &bufferCopy);

    VkBufferMemoryBarrier bufferMemoryBarrier { VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
                                                nullptr,
                                                VK_ACCESS_MEMORY_WRITE_BIT,
                                                VK_ACCESS_INDEX_READ_BIT,
                                                GraphicsQueueIndex,
                                                GraphicsQueueIndex,
                                                IndexBufferHandle,
                                                0,
                                                bufferSize };

    vkCmdPipelineBarrier(GraphicsCommandBuffers[0], VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, 0, 0, nullptr, 1,
                         &bufferMemoryBarrier, 0, nullptr);

    vkEndCommandBuffer(GraphicsCommandBuffers[0]);

    VkSubmitInfo submitInfo {
        VK_STRUCTURE_TYPE_SUBMIT_INFO, nullptr, 0,      nullptr, nullptr, 1,
        &GraphicsCommandBuffers[0],    0,       nullptr
    };

    vkQueueSubmit(GraphicsQueue, 1, &submitInfo, GraphicsCommandBuffersFences[0]);
}

void Draw()
{
    static uint32_t virtualFrameIndex = 0;
    uint32_t imageIndex;

    virtualFrameIndex = (virtualFrameIndex + 1) % VirtualFramesCount;

    if (vkWaitForFences(Device, 1, &GraphicsCommandBuffersFences[virtualFrameIndex], VK_TRUE, 1000000000)
        == VK_TIMEOUT) {
        printf("Fence wasn't signaled within 1 second !\n");
        return;
    }
    vkResetFences(Device, 1, &GraphicsCommandBuffersFences[virtualFrameIndex]);

    // Acquire the next image index, and give a semaphore to signal once were allowed to draw on it
    vkAcquireNextImageKHR(Device, Swapchain, std::numeric_limits<uint64_t>::max(),
                          ImageAvailableSemaphores[virtualFrameIndex], nullptr, &imageIndex);

    RecordCommands(virtualFrameIndex);

    // Where does the semaphore needs to wait
    VkPipelineStageFlags waitPipelineStages = VK_PIPELINE_STAGE_TRANSFER_BIT;

    // Send command buffers to the queue to execute it
    VkSubmitInfo submitInfo { VK_STRUCTURE_TYPE_SUBMIT_INFO,
                              nullptr,
                              1,
                              &ImageAvailableSemaphores[virtualFrameIndex], // Useless for now ?
                              &waitPipelineStages,
                              1,
                              &GraphicsCommandBuffers[virtualFrameIndex],
                              1,
                              &QueueProcessingFinishedSemaphores[virtualFrameIndex] };

    vkQueueSubmit(GraphicsQueue, 1, &submitInfo,
                  GraphicsCommandBuffersFences[virtualFrameIndex]);

    // Present the resulting image once the finishes processing commands
    VkPresentInfoKHR presentInfo { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                   nullptr,
                                   1,
                                   &QueueProcessingFinishedSemaphores[virtualFrameIndex],
                                   1,
                                   &Swapchain,
                                   &imageIndex,
                                   nullptr };

    vkQueuePresentKHR(PresentationQueue, &presentInfo);
}

inline void CreateRenderingRessources()
{
    VkSemaphoreCreateInfo semaphoreCreateInfo { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                                                nullptr, 0 };

    for (size_t virtualFrameIndex = 0; virtualFrameIndex < VirtualFramesCount;
         virtualFrameIndex++) {
        vkCreateSemaphore(Device, &semaphoreCreateInfo, nullptr,
                          &ImageAvailableSemaphores[virtualFrameIndex]);
        vkCreateSemaphore(Device, &semaphoreCreateInfo, nullptr,
                          &QueueProcessingFinishedSemaphores[virtualFrameIndex]);
    }


    VkCommandBufferAllocateInfo graphicsCommandBuffersAllocateInfo {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, nullptr,
        GraphicsQueueCmdPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VirtualFramesCount
    };
    vkAllocateCommandBuffers(Device, &graphicsCommandBuffersAllocateInfo,
                             GraphicsCommandBuffers.data());

    VkCommandBufferAllocateInfo presentationCommandBuffersAllocateInfo {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, nullptr,
        PresentationQueueCmdPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, VirtualFramesCount
    };
    vkAllocateCommandBuffers(Device, &presentationCommandBuffersAllocateInfo,
                             PresentationCommandBuffers.data());


    VkFenceCreateInfo fenceCreateInfo { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, nullptr, 0 };

    for (auto &fence : GraphicsCommandBuffersFences) {
        vkCreateFence(Device, &fenceCreateInfo, nullptr, &fence);
    }


    // Image views, recreate them on swapchain recreation ?
    for (size_t imageIndex = 0; imageIndex < SwapchainImages.size(); imageIndex++) {
        VkComponentMapping componentMapping
            = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
        VkImageSubresourceRange imageSubresourceRange { VK_IMAGE_ASPECT_COLOR_BIT,
                                                        0, 1, 0, 1 };

        VkImageViewCreateInfo imageViewCreateInfo { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                                                    nullptr,
                                                    0,
                                                    SwapchainImages[imageIndex],
                                                    VK_IMAGE_VIEW_TYPE_2D,
                                                    SwapchainFormat,
                                                    componentMapping,
                                                    imageSubresourceRange };

        vkCreateImageView(Device, &imageViewCreateInfo, nullptr,
                          &SwapchainImagesViews[imageIndex]);
    }
}

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

    Instance = CreateInstance(neededInstanceLayers, neededInstanceExtensions).value();

    VkSurfaceKHR presentationSurface;

#if defined(WINDOWS)
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo {
        VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, nullptr, 0,
        _window.GetWindowHInstance(), _window.GetWindowHandle()
    };

    if (vkCreateWin32SurfaceKHR(Instance, &surfaceCreateInfo, nullptr, &presentationSurface)
        != VK_SUCCESS) {
        printf("Failed to create win32 surface\n");
    }
#endif

    std::vector<const char *> requiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    auto requiredQueueFlags = VK_QUEUE_GRAPHICS_BIT;

    PhysicalDevice = SelectPhysicalDevice(Instance, requiredQueueFlags,
                                          requiredDeviceExtensions, presentationSurface)
                         .value();

    GraphicsQueueIndex = GetQueueFamilyIndex(PhysicalDevice, requiredQueueFlags);
    PresentationQueueIndex = GetPresentationQueueIndex(PhysicalDevice, presentationSurface);

    std::vector<uint32_t> queueFamilyIndices;
    if (GraphicsQueueIndex == PresentationQueueIndex) {
        queueFamilyIndices.emplace_back(GraphicsQueueIndex);
    }
    else {
        queueFamilyIndices.emplace_back(static_cast<uint32_t>(GraphicsQueueIndex));
        queueFamilyIndices.emplace_back(static_cast<uint32_t>(PresentationQueueIndex));
    }

    Device = CreateDevice(PhysicalDevice, queueFamilyIndices, requiredDeviceExtensions)
                 .value();

    VmaVulkanFunctions vmaVulkanFunctions;
    vmaVulkanFunctions.vkGetPhysicalDeviceProperties = vkGetPhysicalDeviceProperties;
    vmaVulkanFunctions.vkGetPhysicalDeviceMemoryProperties = vkGetPhysicalDeviceMemoryProperties;
    vmaVulkanFunctions.vkCreateImage                       = vkCreateImage;
    vmaVulkanFunctions.vkCreateBuffer                      = vkCreateBuffer;
    vmaVulkanFunctions.vkAllocateMemory                    = vkAllocateMemory;
    vmaVulkanFunctions.vkMapMemory                         = vkMapMemory;
    vmaVulkanFunctions.vkBindBufferMemory                  = vkBindBufferMemory;
    vmaVulkanFunctions.vkBindImageMemory                   = vkBindImageMemory;
    vmaVulkanFunctions.vkGetBufferMemoryRequirements = vkGetBufferMemoryRequirements;
    vmaVulkanFunctions.vkGetImageMemoryRequirements = vkGetImageMemoryRequirements;
    vmaVulkanFunctions.vkCmdCopyBuffer              = vkCmdCopyBuffer;
    vmaVulkanFunctions.vkUnmapMemory                = vkUnmapMemory;
    vmaVulkanFunctions.vkFlushMappedMemoryRanges    = vkFlushMappedMemoryRanges;
    vmaVulkanFunctions.vkInvalidateMappedMemoryRanges = vkInvalidateMappedMemoryRanges;
    vmaVulkanFunctions.vkFreeMemory                   = vkFreeMemory;
    vmaVulkanFunctions.vkDestroyImage                 = vkDestroyImage;
    vmaVulkanFunctions.vkDestroyBuffer                = vkDestroyBuffer;
    VmaAllocatorCreateInfo allocatorCreateInfo {};
    allocatorCreateInfo.physicalDevice   = PhysicalDevice;
    allocatorCreateInfo.device           = Device;
    allocatorCreateInfo.pVulkanFunctions = &vmaVulkanFunctions;

    vmaCreateAllocator(&allocatorCreateInfo, &Allocator);


    vkGetDeviceQueue(Device, GraphicsQueueIndex, 0, &GraphicsQueue);
    vkGetDeviceQueue(Device, PresentationQueueIndex, 0, &PresentationQueue);

    VkCommandPoolCreateInfo graphicsCommandPoolCreateInfo {
        VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, nullptr,
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, GraphicsQueueIndex
    };
    vkCreateCommandPool(Device, &graphicsCommandPoolCreateInfo, nullptr, &GraphicsQueueCmdPool);

    VkCommandPoolCreateInfo presentationCommandPoolCreateInfo {
        VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, nullptr,
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, PresentationQueueIndex
    };
    vkCreateCommandPool(Device, &presentationCommandPoolCreateInfo, nullptr,
                        &PresentationQueueCmdPool);


    Swapchain
        = CreateSwapchain(Device, PhysicalDevice, presentationSurface, nullptr).value();

    uint32_t imagesCount = 0;
    vkGetSwapchainImagesKHR(Device, Swapchain, &imagesCount, nullptr);

    SwapchainImages.resize(imagesCount);
    vkGetSwapchainImagesKHR(Device, Swapchain, &imagesCount, SwapchainImages.data());

    CreateRenderingRessources();

    // Change swapchain images memory layout
    VkCommandBufferBeginInfo commandBufferBeginInfo {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr,
        VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr
    };

    VkImageSubresourceRange imageSubresourceRange { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    // Change image layout foreach swapchain images
    for (size_t imageIndex = 0; imageIndex < imagesCount; imageIndex++) {
        uint32_t virtualFrameIndex  = imageIndex % VirtualFramesCount;
        uint32_t acquiredImageIndex = 0;

        vkAcquireNextImageKHR(Device, Swapchain, std::numeric_limits<uint64_t>::max(),
                              ImageAvailableSemaphores[virtualFrameIndex],
                              nullptr, &acquiredImageIndex);

        // Change current swapchain image layout
        VkImageMemoryBarrier fromUndefinedToPresentBarrier {
            VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
            nullptr,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_ACCESS_MEMORY_READ_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            GraphicsQueueIndex,
            GraphicsQueueIndex,
            SwapchainImages[acquiredImageIndex],
            imageSubresourceRange
        };

        vkBeginCommandBuffer(GraphicsCommandBuffers[virtualFrameIndex], &commandBufferBeginInfo);
        vkCmdPipelineBarrier(GraphicsCommandBuffers[virtualFrameIndex],
                             VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                             VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 0, 0, nullptr,
                             0, nullptr, 1, &fromUndefinedToPresentBarrier);
        vkEndCommandBuffer(GraphicsCommandBuffers[virtualFrameIndex]);

        VkPipelineStageFlags waitPipelineStages = VK_PIPELINE_STAGE_TRANSFER_BIT;

        // Send command buffers to the queue to execute it
        VkSubmitInfo submitInfo { VK_STRUCTURE_TYPE_SUBMIT_INFO,
                                  nullptr,
                                  1,
                                  &ImageAvailableSemaphores[virtualFrameIndex],
                                  &waitPipelineStages,
                                  1,
                                  &GraphicsCommandBuffers[virtualFrameIndex],
                                  1,
                                  &QueueProcessingFinishedSemaphores[virtualFrameIndex] };

        vkQueueSubmit(GraphicsQueue, 1, &submitInfo,
                      GraphicsCommandBuffersFences[virtualFrameIndex]);

        // Present the resulting image, give it back to the presentation engine
        VkPresentInfoKHR presentInfo { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                       nullptr,
                                       1,
                                       &QueueProcessingFinishedSemaphores[virtualFrameIndex],
                                       1,
                                       &Swapchain,
                                       &acquiredImageIndex,
                                       nullptr };

        vkQueuePresentKHR(PresentationQueue, &presentInfo);
    }

    CreateRenderpass();
    CreatePipeline();
    CreateVertexBuffer();
    CreateIndexBuffer();
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

        Draw();
    }

    return 0;
}
#endif

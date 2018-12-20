add_library(vulkania VulkanCommandBuffer.cpp VulkanDebug.cpp
			VulkanDepthStencilBuffer.cpp VulkanFragmentShader.cpp
			VulkanFramebuffer.cpp VulkanGeometryShader.cpp
			VulkanHelper.cpp VulkanImage.cpp VulkanRenderContext.cpp
			VulkanRenderPass.cpp VulkanShader.cpp
			VulkanSwapchain.cpp VulkanVertexBuffer.cpp
			VulkanVertexInputLayout.cpp VulkanVertexShader.cpp)

target_include_directories(vulkania PRIVATE "$ENV{VULKAN_SDK}/Include")
target_include_directories(vulkania PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering/RenderContext/Vulkania)
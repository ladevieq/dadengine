include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Rendering/RenderContext/Vulkania)

add_library(vulkania VulkanCommandBuffer.cpp VulkanDebug.cpp
			VulkanDepthStencilBuffer.cpp VulkanFragmentShader.cpp
			VulkanFramebuffer.cpp VulkanGeometryShader.cpp
			VulkanHelper.cpp VulkanImage.cpp VulkanRenderContext.cpp
			VulkanRenderPass.cpp VulkanShader.cpp
			VulkanSwapchain.cpp VulkanVertexBuffer.cpp
			VulkanVertexInputLayout.cpp VulkanVertexShader.cpp)
add_library(vulkania vulkan-command-buffer.cpp vulkan-debug.cpp
			vulkan-depth-stencil-buffer.cpp vulkan-fragment-shader.cpp
			vulkan-framebuffer.cpp vulkan-geometry-shader.cpp
			vulkan-helper.cpp vulkan-image.cpp vulkan-render-context.cpp
			vulkan-renderpass.cpp vulkan-shader.cpp
			vulkan-swapchain.cpp vulkan-vertex-buffer.cpp
			vulkan-vertex-input-layout.cpp vulkan-vertex-shader.cpp)

target_include_directories(vulkania PRIVATE "$ENV{VULKAN_SDK}/Include")
target_include_directories(vulkania PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context/vulkania)
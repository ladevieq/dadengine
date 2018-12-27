add_library(vulkania vulkan-command-buffer.cpp vulkan-debug.cpp
			vulkan-depth-stencil-buffer.cpp vulkan-fragment-shader.cpp
			vulkan-framebuffer.cpp vulkan-geometry-shader.cpp
			vulkan-helper.cpp vulkan-image.cpp vulkan-render-context.cpp
			vulkan-renderpass.cpp vulkan-shader.cpp
			vulkan-swapchain.cpp vulkan-vertex-buffer.cpp
			vulkan-vertex-input-layout.cpp vulkan-vertex-shader.cpp)

target_compile_features(vulkania PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(vulkania PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(vulkania PRIVATE "$ENV{VULKAN_SDK}/Include")
target_include_directories(vulkania PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context/vulkania)
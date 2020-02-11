add_subdirectory(mesh)
add_subdirectory(render-context/opengl)
add_subdirectory(render-context/vulkan)
add_subdirectory(shader)

add_library(rendering ${DADENGINE_RENDERING_SRC} camera.cpp command-buffer.cpp renderer.cpp vertex-buffer.cpp)

target_include_directories(rendering PRIVATE 
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/light
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/mesh
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context/opengl
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context/vulkan
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/shader
        ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/texture
        ${CMAKE_SOURCE_DIR}/include/thirdparty
)
target_include_directories(rendering SYSTEM PRIVATE "$ENV{VULKAN_SDK}/Include")

add_subdirectory(Culling/)
add_subdirectory(Feature/)
add_subdirectory(Mesh/)
add_subdirectory(RenderContext/OpenGL)
add_subdirectory(RenderContext/Vulkania)
add_subdirectory(Shader/)

add_library(rendering CommandBuffer.cpp VertexBuffer.cpp)

target_include_directories(rendering PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering)
target_link_libraries(rendering culling feature mesh opengl vulkania shader)
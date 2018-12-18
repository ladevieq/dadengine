add_subdirectory(Culling/)
add_subdirectory(Feature/)
add_subdirectory(Mesh/)
add_subdirectory(RenderContext/)
add_subdirectory(Shader/)

add_library(rendering RenderContext/OpenGLWrapper.cpp CommandBuffer.cpp VertexBuffer.cpp)

target_link_libraries(rendering culling feature mesh opengl vulkania shader)
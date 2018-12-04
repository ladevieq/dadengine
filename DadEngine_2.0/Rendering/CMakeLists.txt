add_subdirectory(Culling/)
add_subdirectory(RenderContext/)

add_library(rendering Culling/Camera.cpp Culling/FramePacket.cpp Culling/ViewPacket.cpp RenderContext/OpenGLWrapper.cpp)

target_link_libraries(rendering culling opengl vulkania)
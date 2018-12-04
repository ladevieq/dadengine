add_subdirectory(OpenGL/)
add_subdirectory(Vulkania/)

add_library(rendercontext OpenGLWrapper.cpp)

target_link_libraries(rendercontext opengl vulkania)
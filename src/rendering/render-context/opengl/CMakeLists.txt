add_library(opengl opengl-command-buffer.cpp opengl-fragment-shader.cpp
	opengl-framebuffer.cpp opengl-geometry-shader.cpp
	opengl-render-command.cpp opengl-render-context.cpp
	opengl-shader.cpp opengl-vertex-buffer.cpp
	opengl-vertex-shader.cpp opengl-wrapper.cpp)

target_include_directories(opengl PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(opengl PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context/opengl)
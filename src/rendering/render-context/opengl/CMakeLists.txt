add_library(opengl opengl-command-buffer.cpp opengl-fragment-shader.cpp
	opengl-framebuffer.cpp opengl-geometry-shader.cpp
	opengl-render-command.cpp opengl-render-context.cpp
	opengl-shader.cpp opengl-vertex-buffer.cpp
	opengl-vertex-shader.cpp opengl-wrapper.cpp)

target_compile_features(opengl PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(opengl PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(opengl PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(opengl PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/render-context/opengl)
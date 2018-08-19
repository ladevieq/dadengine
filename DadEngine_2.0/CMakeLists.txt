# Minimum CMake Version required to build
cmake_minimum_required(VERSION 3.1)
project(DadEngine_2_0)

# Project version number
set (DadEngine_2_0_VERSION_MAJOR 2)
set (DadEngine_2_0_VERSION_MINOR 0)

# Required compiler properties
SET(CMAKE_C_COMPILER $ENV{EMSCRIPTEN}/emcc)
SET(CMAKE_CXX_COMPILER $ENV{EMSCRIPTEN}/em++)

set_property(TARGET PROPERTY CXX_STANDARD 17)
set_property(TARGET PROPERTY CXX_STANDARD_REQUIRED ON)

#Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADOPENGLES)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Include directories
include_directories("${PROJECT_SOURCE_DIR}/Core")
	include_directories("${PROJECT_SOURCE_DIR}/Core/Iterators")
	include_directories("${PROJECT_SOURCE_DIR}/Core/Memory")
	include_directories("${PROJECT_SOURCE_DIR}/Core/Platform")
		include_directories("${PROJECT_SOURCE_DIR}/Core/Platform/Windows")
	include_directories("${PROJECT_SOURCE_DIR}/Core/Serialization")

include_directories("${PROJECT_SOURCE_DIR}/Gameplay")

include_directories("${PROJECT_SOURCE_DIR}/Math")

include_directories("${PROJECT_SOURCE_DIR}/Rendering")
	include_directories("${PROJECT_SOURCE_DIR}/Rendering/Culling")
	include_directories("${PROJECT_SOURCE_DIR}/Rendering/Feature")
	include_directories("${PROJECT_SOURCE_DIR}/Rendering/Mesh")
	include_directories("${PROJECT_SOURCE_DIR}/Rendering/RenderContext")
		include_directories("${PROJECT_SOURCE_DIR}/Rendering/RenderContext/OpenGL")
		include_directories("${PROJECT_SOURCE_DIR}/Rendering/RenderContext/Vulkan")
	include_directories("${PROJECT_SOURCE_DIR}/Rendering/Shader")
	include_directories("${PROJECT_SOURCE_DIR}/Rendering/Texture")

include_directories("$ENV{VULKAN_SDK}/Include")

include_directories("$ENV{GLES_SDK}/include")

include_directories("$ENV{EMSCRIPTEN}/system/include")

# Add source files
file(GLOB_RECURSE SRC "*.cpp")

add_executable(DadEngine_2_0 ${SRC})

# Link libs
target_link_libraries(DadEngine_2_0 ${OPENGL_gl_LIBRARY})
target_link_libraries(DadEngine_2_0 ${Vulkan_LIBRARY}) 

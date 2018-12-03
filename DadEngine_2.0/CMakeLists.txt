# Minimum CMake Version required to build
cmake_minimum_required(VERSION 3.1)
project(DadEngine)

# Project version number
set (DadEngine_VERSION_MAJOR 0)
set (DadEngine_VERSION_MINOR 1)
set (DadEngine_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADOPENGL)

# Needed packages
# find_package(Vulkan)
# find_package(OpenGL REQUIRED)

# Include directories
# include_directories("$ENV{VULKAN_SDK}/Include")

# Add source files

# Link libs
# target_link_libraries(DadEngine ${OPENGL_gl_LIBRARY})
# if(Vulkan_FOUND)
	# target_link_libraries(DadEngine ${Vulkan_LIBRARY}) 
# endif()

add_subdirectory(Core/)

add_executable(DadEngine main.cpp)

target_link_libraries(DadEngine core)

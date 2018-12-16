# Minimum CMake Version required to build
cmake_minimum_required(VERSION 3.10)
project(DadEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADVULKAN -D_CRT_SECURE_NO_WARNINGS)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Include directories
include_directories("$ENV{VULKAN_SDK}/Include")

# Add source files
add_subdirectory(Core/)
add_subdirectory(Gameplay/)
add_subdirectory(Math/)
add_subdirectory(Rendering/)

add_executable(DadEngine WIN32 main.cpp)

# Link libs
target_link_libraries(DadEngine ${OPENGL_gl_LIBRARY})
if(Vulkan_FOUND)
	target_link_libraries(DadEngine ${Vulkan_LIBRARY}) 
endif()

target_link_libraries(DadEngine core gameplay math rendering)

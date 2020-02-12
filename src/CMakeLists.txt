# Platforms macros
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Add source files
# add_subdirectory(math/)
add_subdirectory(window/)

# Use c++ 17 flags and fix system includes with clang-cl.exe
IF (WIN32)
    # Use clang-cl.exe MSVC-like flags
    add_compile_options(--driver-mode=cl)
    add_compile_options(/std:c++17)
    set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-imsvc ")
ELSE()
    add_compile_options(-std=c++17)
ENDIF()

add_executable(dadengine main.cpp)

# Include directories
target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)

target_include_directories(dadengine SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)

# Link libs
# target_link_libraries(dadengine private ${opengl_gl_library})
# if(vulkan_found)
# 	target_link_libraries(dadengine private ${vulkan_library}) 
# endif()

target_link_libraries(dadengine PRIVATE window)

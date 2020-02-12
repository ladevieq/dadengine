# Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADOPENGL -D_CRT_SECURE_NO_WARNINGS)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Add source files
# add_subdirectory(math/)
add_subdirectory(window/)

add_executable(dadengine main.cpp)

# Include directories
target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)

target_include_directories(dadengine SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)

# Link libs
# target_link_libraries(dadengine private ${opengl_gl_library})
# if(vulkan_found)
# 	target_link_libraries(dadengine private ${vulkan_library}) 
# endif()

# target_link_libraries(dadengine PRIVATE core gameplay math rendering window)
target_link_libraries(dadengine PRIVATE window)

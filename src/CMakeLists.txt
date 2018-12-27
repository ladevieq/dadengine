#Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADVULKAN -D_CRT_SECURE_NO_WARNINGS)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Add source files
add_subdirectory(core/)
add_subdirectory(gameplay/)
add_subdirectory(math/)
add_subdirectory(rendering/)

add_executable(dadengine WIN32 main.cpp)

target_compile_features(dadengine PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(dadengine PROPERTIES CXX_EXTENSIONS OFF)

# Include directories
target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)

# Link libs
target_link_libraries(dadengine PRIVATE ${OPENGL_gl_LIBRARY})
if(Vulkan_FOUND)
	target_link_libraries(dadengine PRIVATE ${Vulkan_LIBRARY}) 
endif()

target_link_libraries(dadengine PRIVATE core gameplay math rendering)

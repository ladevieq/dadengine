#Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADVULKAN -D_CRT_SECURE_NO_WARNINGS)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Add source files
add_subdirectory(Core/)
add_subdirectory(Gameplay/)
add_subdirectory(Math/)
add_subdirectory(Rendering/)

add_executable(DadEngine WIN32 main.cpp)

# Include directories
target_include_directories(DadEngine PUBLIC "$ENV{VULKAN_SDK}/Include")
target_include_directories(DadEngine PUBLIC ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(DadEngine PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine)

# Link libs
target_link_libraries(DadEngine PRIVATE ${OPENGL_gl_LIBRARY})
if(Vulkan_FOUND)
	target_link_libraries(DadEngine PRIVATE ${Vulkan_LIBRARY}) 
endif()

target_link_libraries(DadEngine PRIVATE core gameplay math rendering)

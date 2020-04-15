add_library(renderer opengl-renderer.cpp vulkan-loader.cpp)

find_package(unofficial-vulkan-memory-allocator CONFIG REQUIRED)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/include/renderer)
target_include_directories(renderer SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})

target_link_libraries(renderer PRIVATE 
    unofficial::vulkan-memory-allocator::vulkan-memory-allocator
    ${OPENGL_LIBRARIES}
)

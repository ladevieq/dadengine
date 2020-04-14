add_library(renderer opengl-renderer.cpp vulkan-loader.cpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)
target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/renderer)
target_include_directories(renderer SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(renderer SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})

target_link_libraries(renderer PRIVATE ${OPENGL_LIBRARIES})

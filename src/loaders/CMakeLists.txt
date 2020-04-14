add_library(loaders gltf-loader.cpp)

target_include_directories(loaders PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)
target_include_directories(loaders PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/loaders)
target_include_directories(loaders SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(loaders SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})

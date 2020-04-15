add_library(loaders gltf-loader.cpp)

find_package(nlohmann_json CONFIG REQUIRED)

target_include_directories(loaders PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(loaders PRIVATE ${CMAKE_SOURCE_DIR}/include/loaders)
target_include_directories(loaders SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})

# TODO: Remove once the rendering api works
target_include_directories(loaders SYSTEM PRIVATE "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include")

target_link_libraries(loaders PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

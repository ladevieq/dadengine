add_library(model model.cpp)

target_include_directories(model PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(model PRIVATE ${CMAKE_SOURCE_DIR}/include/model)
target_include_directories(model SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})

# TODO: Remove once the rendering api works
target_include_directories(model SYSTEM PRIVATE "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include")

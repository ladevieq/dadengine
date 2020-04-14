add_library(model model.cpp)

target_include_directories(model PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)
target_include_directories(model PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/model)
target_include_directories(model SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(model SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})

add_library(quaternion quaternion.cpp)

target_include_directories(quaternion PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math/quaternion)
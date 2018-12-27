add_library(quaternion quaternion.cpp)

target_compile_features(quaternion PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(quaternion PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(quaternion PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math/quaternion)
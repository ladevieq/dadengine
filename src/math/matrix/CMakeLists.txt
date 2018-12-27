add_library(matrix matrix2x2.cpp matrix3x3.cpp matrix4x4.cpp)

target_compile_features(matrix PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(matrix PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(matrix PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math/matrix)
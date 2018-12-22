add_library(matrix matrix2x2.cpp matrix3x3.cpp matrix4x4.cpp)

target_include_directories(matrix PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math/matrix)
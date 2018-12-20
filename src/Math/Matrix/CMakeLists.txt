add_library(matrix Matrix2x2.cpp Matrix3x3.cpp Matrix4x4.cpp)

target_include_directories(matrix PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Math/Matrix)
add_library(vector vector2f.cpp vector3f.cpp vector4f.cpp)

target_include_directories(vector PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math/vector)
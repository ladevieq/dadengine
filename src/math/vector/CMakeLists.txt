add_library(vector vector2f.cpp vector3f.cpp vector4f.cpp)

target_compile_features(vector PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(vector PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(vector PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math/vector)
add_library(shader shader.cpp)

target_compile_features(shader PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(shader PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(shader PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/shader)
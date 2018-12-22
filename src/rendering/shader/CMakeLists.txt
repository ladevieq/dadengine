add_library(shader shader.cpp)

target_include_directories(shader PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/shader)
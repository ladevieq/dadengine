add_library(shader Shader.cpp)

target_include_directories(shader PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering/Shader)
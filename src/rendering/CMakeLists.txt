add_subdirectory(culling/)
add_subdirectory(feature/)
add_subdirectory(mesh/)
add_subdirectory(render-context/opengl)
add_subdirectory(render-context/vulkania)
add_subdirectory(shader/)

add_library(rendering command-buffer.cpp vertex-buffer.cpp)

target_include_directories(rendering PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering)
target_link_libraries(rendering culling feature mesh opengl vulkania shader)
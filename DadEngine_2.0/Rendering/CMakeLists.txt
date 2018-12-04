add_subdirectory(Culling/)
add_subdirectory(RenderContext/)

add_library(rendering)

target_link_libraries(rendering culling rendercontext)
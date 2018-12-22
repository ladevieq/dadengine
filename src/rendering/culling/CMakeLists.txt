add_library(culling camera.cpp frame-packet.cpp render-object.cpp view-packet.cpp)

target_include_directories(culling PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/culling)
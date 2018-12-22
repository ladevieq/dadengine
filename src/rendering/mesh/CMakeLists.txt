add_library(mesh raw-mesh.cpp vertex-factory.cpp vertex-input-layout.cpp)

target_include_directories(mesh PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/mesh)
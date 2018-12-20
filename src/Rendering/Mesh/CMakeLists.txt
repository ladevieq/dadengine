add_library(mesh RawMesh.cpp VertexFactory.cpp VertexInputLayout.cpp)

target_include_directories(mesh PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering/Mesh)
add_library(mesh raw-mesh.cpp vertex-factory.cpp vertex-input-layout.cpp)

target_compile_features(mesh PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(mesh PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(mesh PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/mesh)
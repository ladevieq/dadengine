add_library(culling camera.cpp frame-packet.cpp render-object.cpp view-packet.cpp)

target_compile_features(culling PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(culling PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(culling PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/culling)
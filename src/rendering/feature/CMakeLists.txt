add_library(feature static-mesh-rendering-feature.cpp)

target_include_directories(feature PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/feature)
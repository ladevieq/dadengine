add_library(feature static-mesh-rendering-feature.cpp)

target_compile_features(feature PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(feature PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(feature PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/rendering/feature)
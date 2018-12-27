add_library(serialization archive.cpp)

target_compile_features(serialization PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(serialization PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(serialization PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/serialization)
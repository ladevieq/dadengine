add_library(serialization archive.cpp)

target_include_directories(serialization PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/serialization)
add_library(memory memory-manager.cpp)

target_include_directories(memory PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/memory)
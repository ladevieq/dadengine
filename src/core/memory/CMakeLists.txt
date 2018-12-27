add_library(memory memory-manager.cpp)

target_compile_features(memory PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(memory PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(memory PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/memory)
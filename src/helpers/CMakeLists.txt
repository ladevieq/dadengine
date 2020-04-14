add_library(helpers file.cpp)

target_include_directories(helpers PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/helpers)

add_library(collection tarray.cpp tdictionary.cpp)

target_include_directories(collection PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/types/collection)
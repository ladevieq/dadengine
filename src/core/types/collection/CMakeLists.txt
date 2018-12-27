add_library(collection tarray.cpp tdictionary.cpp)

target_compile_features(collection PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(collection PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(collection PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/types/collection)
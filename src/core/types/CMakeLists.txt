add_subdirectory(collection/)

add_library(types string.cpp)

target_compile_features(types PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(types PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(types PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/types)
target_link_libraries(types collection)
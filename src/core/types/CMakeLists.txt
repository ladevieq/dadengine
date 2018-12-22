add_subdirectory(collection/)

add_library(types string.cpp)

target_include_directories(types PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/types)
target_link_libraries(types collection)
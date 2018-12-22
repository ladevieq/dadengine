add_subdirectory(matrix/)
add_subdirectory(quaternion/)
add_subdirectory(vector/)

add_library(math math-functions.cpp)

target_include_directories(math PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math)
target_link_libraries(math matrix quaternion vector)
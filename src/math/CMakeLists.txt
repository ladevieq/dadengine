add_subdirectory(matrix/)
add_subdirectory(quaternion/)
add_subdirectory(vector/)

add_library(math math-functions.cpp)

target_compile_features(math PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(math PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(math PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/math)
target_link_libraries(math matrix quaternion vector)
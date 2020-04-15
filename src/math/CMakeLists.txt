add_subdirectory(matrix/)
add_subdirectory(quaternion/)
add_subdirectory(vector/)

add_library(math ${DADENGINE_MATH_SRC})

target_include_directories(math PRIVATE
        ${CMAKE_SOURCE_DIR}/include/math
        ${CMAKE_SOURCE_DIR}/include/math/quaternion
        ${CMAKE_SOURCE_DIR}/include/math/vector
        ${CMAKE_SOURCE_DIR}/include/math/matrix
)

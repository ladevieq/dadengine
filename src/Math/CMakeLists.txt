include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Math)

add_subdirectory(Matrix/)
add_subdirectory(Quaternion/)
add_subdirectory(Vector/)

add_library(math MathFunctions.cpp)
target_link_libraries(math matrix quaternion vector)
add_subdirectory(Matrix/)
add_subdirectory(Quaternion/)
add_subdirectory(Vector/)

add_library(math MathFunctions.cpp)

target_include_directories(math PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Math)
target_link_libraries(math matrix quaternion vector)
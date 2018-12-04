add_subdirectory(Vector/)

add_library(math MathFunctions.cpp)
target_link_libraries(math vector)
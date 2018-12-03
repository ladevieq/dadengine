add_subdirectory(Iterators/)
add_subdirectory(Memory/)
add_subdirectory(Platform/)
add_subdirectory(Serialization/)

add_library(core Application.cpp Debug.cpp)
target_include_directories(core ${CMAKE_SOURCE_DIR}/Core/)
target_link_libraries(core iterators memory platform serialization)
add_subdirectory(Collection/)

add_library(types String.cpp)

target_include_directories(types PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Core/Types)
target_link_libraries(types collection)
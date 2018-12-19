include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Core/Types)

add_subdirectory(Collection/)

add_library(types String.cpp)
target_link_libraries(types collection)
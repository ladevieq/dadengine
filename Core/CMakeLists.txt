add_subdirectory(Memory/)
add_subdirectory(Platform/Windows/)

add_library(core Application.cpp Debug.cpp)
target_link_libraries(core memory windows)
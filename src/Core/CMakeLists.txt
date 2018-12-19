add_subdirectory(Memory/)
add_subdirectory(Platform/Windows/)
add_subdirectory(Serialization/)
add_subdirectory(Types/)

add_library(core Application.cpp Debug.cpp Profile.cpp)
target_link_libraries(core memory windows serialization types)
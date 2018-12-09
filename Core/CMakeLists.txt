add_subdirectory(Memory/)
add_subdirectory(Platform/Windows/)
add_subdirectory(Serialization/)
add_subdirectory(Types/Collection)

add_library(core Application.cpp Debug.cpp Profile.cpp)
target_link_libraries(core memory windows serialization collection)
add_subdirectory(memory/)
add_subdirectory(platform/windows)
add_subdirectory(serialization/)
add_subdirectory(types/)

add_library(core application.cpp debug.cpp profile.cpp)

target_include_directories(core PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core)
target_link_libraries(core memory windows serialization types)
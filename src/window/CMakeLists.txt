add_library(window application.cpp windows-window.cpp)

target_include_directories(window PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/window)

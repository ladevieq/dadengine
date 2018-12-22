add_library(windows windows-window.cpp windows-binary-file-io.cpp
	windows-text-file-io.cpp windows-file-system.cpp
	windows-memory.cpp windows-threads.cpp
	windows-timers.cpp)

target_include_directories(windows PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/platform/windows)
add_library(windows WindowsWindow.cpp WindowsBinaryFileIO.cpp
	WindowsTextFileIO.cpp WindowsFileSystem.cpp
	WindowsMemory.cpp WindowsThreads.cpp
	WindowsTimers.cpp)

target_include_directories(windows PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Core/Platform/Windows)
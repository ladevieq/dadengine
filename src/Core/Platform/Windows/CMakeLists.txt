include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Core/Platform/Windows)

add_library(windows WindowsWindow.cpp WindowsBinaryFileIO.cpp
	WindowsTextFileIO.cpp WindowsFileSystem.cpp
	WindowsMemory.cpp WindowsThreads.cpp
	WindowsTimers.cpp)
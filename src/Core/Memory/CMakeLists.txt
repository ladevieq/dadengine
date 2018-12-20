add_library(memory MemoryManager.cpp)

target_include_directories(memory PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Core/Memory)
add_library(serialization Archive.cpp)

target_include_directories(serialization PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Core/Serialization)
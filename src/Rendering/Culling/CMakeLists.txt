add_library(culling Camera.cpp FramePacket.cpp RenderObject.cpp ViewPacket.cpp)

target_include_directories(culling PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering/Culling)
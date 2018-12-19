include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Rendering/Culling)

add_library(culling Camera.cpp FramePacket.cpp RenderObject.cpp ViewPacket.cpp)
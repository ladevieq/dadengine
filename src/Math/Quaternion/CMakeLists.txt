add_library(quaternion Quaternion.cpp)

target_include_directories(quaternion PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Math/Quaternion)
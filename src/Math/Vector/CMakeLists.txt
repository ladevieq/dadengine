add_library(vector Vector2f.cpp Vector3f.cpp Vector4f.cpp)

target_include_directories(vector PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Math/Vector)
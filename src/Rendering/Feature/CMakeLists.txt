add_library(feature StaticMeshRenderingFeature.cpp)

target_include_directories(feature PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering/Feature)
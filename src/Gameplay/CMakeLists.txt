add_library(gameplay IComponent.cpp CameraManager.cpp InputManager.cpp Actor.cpp)

target_include_directories(gameplay PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Gameplay)
target_link_libraries(gameplay)
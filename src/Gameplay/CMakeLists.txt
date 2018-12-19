include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Gameplay)

add_library(gameplay IComponent.cpp CameraManager.cpp InputManager.cpp Actor.cpp)

target_link_libraries(gameplay)
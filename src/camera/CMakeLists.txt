add_library(camera camera.cpp)

target_include_directories(camera PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(camera PRIVATE ${CMAKE_SOURCE_DIR}/include/camera)
target_include_directories(camera PRIVATE ${CMAKE_SOURCE_DIR}/include/math)

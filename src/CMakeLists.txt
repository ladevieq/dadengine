add_definitions(-DNOMINMAX -DWINDOWS -DVULKAN -DVK_NO_PROTOTYPES)

find_package(Vulkan)
find_package(OpenGL REQUIRED)

add_subdirectory(math/)
add_subdirectory(window/)
add_subdirectory(loaders/)
add_subdirectory(helpers/)
add_subdirectory(model/)
add_subdirectory(camera/)
add_subdirectory(renderer/)

add_executable(dadengine main.cpp)

target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)
target_include_directories(dadengine SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)

target_link_libraries(dadengine PRIVATE ${OPENGL_LIBRARIES})

if(Vulkan_FOUND)
    target_include_directories(dadengine SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})
# target_link_libraries(dadengine private ${VULKAN_LIBRARY}) 
endif()

target_link_libraries(dadengine PRIVATE window math loaders renderer model helpers camera)

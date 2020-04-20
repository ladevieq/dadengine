add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES -DWINDOWS -DVULKAN -DVK_NO_PROTOTYPES)

find_package(OpenGL REQUIRED)
find_package(Vulkan)

add_subdirectory(math/)
add_subdirectory(window/)
add_subdirectory(loaders/)
add_subdirectory(helpers/)
add_subdirectory(model/)
add_subdirectory(camera/)
add_subdirectory(renderer/)

add_executable(dadengine main.cpp)

target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include/math)
target_include_directories(dadengine SYSTEM PRIVATE "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include")

if(Vulkan_FOUND)
    target_include_directories(dadengine SYSTEM PRIVATE ${Vulkan_INCLUDE_DIRS})
endif()

target_link_libraries(dadengine PRIVATE window math loaders renderer model helpers camera ${OPENGL_LIBRARIES})

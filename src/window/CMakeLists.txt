if (WIN32)
    add_library(window application.cpp windows-window.cpp)
else()
    find_package(XCB REQUIRED)
    add_library(window application.cpp x-window.cpp)
    target_link_libraries(window ${XCB_LIBRARIES})
endif()

target_include_directories(window PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/window)

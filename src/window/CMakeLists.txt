add_library(window application.cpp windows-window.cpp)

# target_compile_features(window PUBLIC cxx_std_17)

# Don't use compiler specific flags
# set_target_properties(window PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(window PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core)
target_include_directories(window PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/window)
target_link_libraries(window)
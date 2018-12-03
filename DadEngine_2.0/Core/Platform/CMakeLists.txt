add_subdirectory(Windows/)

add_library(platform)
target_link_libraries(platform windows)
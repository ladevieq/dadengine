add_library(gameplay icomponent.cpp camera-manager.cpp input-manager.cpp actor.cpp)

target_include_directories(gameplay PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/gameplay)
target_link_libraries(gameplay)
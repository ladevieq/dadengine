add_library(gameplay icomponent.cpp camera-manager.cpp input-manager.cpp actor.cpp)

target_compile_features(gameplay PUBLIC cxx_std_17)

# Don't use compiler specific flags
set_target_properties(gameplay PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(gameplay PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/gameplay)
target_link_libraries(gameplay)
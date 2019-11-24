add_subdirectory(memory/)
add_subdirectory(platform/windows)
add_subdirectory(serialization/)
add_subdirectory(types/)

add_library(core ${DADENGINE_CORE_SRC} debug.cpp profile.cpp)

# target_compile_features(core PUBLIC cxx_std_17)

# Don't use compiler specific flags
# set_target_properties(core PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(core PRIVATE 
        ${CMAKE_SOURCE_DIR}/include/dadengine/core
        ${CMAKE_SOURCE_DIR}/include/dadengine/core/types
        ${CMAKE_SOURCE_DIR}/include/dadengine/core/memory
        ${CMAKE_SOURCE_DIR}/include/dadengine/core/serialization
        ${CMAKE_SOURCE_DIR}/include/dadengine/core/platform/windows
)

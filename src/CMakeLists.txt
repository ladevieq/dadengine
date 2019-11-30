# Platforms macros
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR -DDADOPENGL -D_CRT_SECURE_NO_WARNINGS)

# Needed packages
find_package(Vulkan)
find_package(OpenGL REQUIRED)

# Add source files
add_subdirectory(core/)
add_subdirectory(math/)
# add_subdirectory(gameplay/)
add_subdirectory(rendering/)
add_subdirectory(window/)

add_executable(dadengine WIN32 main.cpp)

# target_compile_features(dadengine PUBLIC cxx_std_17)

# Don't use compiler specific flags
# set_target_properties(dadengine PROPERTIES CXX_EXTENSIONS OFF)

# Include directories
target_include_directories(dadengine PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine)

# Link libs
# target_link_libraries(dadengine private ${opengl_gl_library})
# if(vulkan_found)
# 	target_link_libraries(dadengine private ${vulkan_library}) 
# endif()

# target_link_libraries(dadengine PRIVATE core gameplay math rendering window)
target_link_libraries(dadengine PRIVATE core window)

macro (add_sources)
    file (RELATIVE_PATH _relPath "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()

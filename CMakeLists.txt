# Minimu CMake Version required to build
cmake_minimum_required(VERSION 3.10)

# All warnings and no c++ 98 compatibility
if (CLANG)
    add_compile_options(-fcolor-diagnostics -fansi-escape-codes)
endif ()

# Use c++ 17 flags and fix system includes with clang-cl.exe
IF (WIN32)
    # Use clang-cl.exe MSVC-like flags
    add_compile_options(--driver-mode=cl)
    add_compile_options(/std:c++17)
    set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-imsvc ")
ELSE()
    add_compile_options(-std=c++17)
ENDIF()

add_compile_options(-Wall -Wextra -Wno-c++98-compat -Wno-reserved-id-macro -Wno-comma)

# Enable test and define the needed scope to run ctest
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put binaries at the root of the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(dadengine VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src/)

# add_subdirectory(test/)

# add_subdirectory(doc/)

# Minimu CMake Version required to build
cmake_minimum_required(VERSION 3.10)

# All warnings and no c++ 98 compatibility
add_compile_options(-fcolor-diagnostics -fansi-escape-codes -Wall -Wextra -Wno-c++98-compat -Wno-reserved-id-macro -Wno-comma)

# Enable test and define the needed scope to run ctest
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put binaries at the root of the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CPPCHECK cppcheck)

add_compile_options(-fcolor-diagnostics -fansi-escape-codes -Wall -Wextra -Wno-c++98-compat -Wno-reserved-id-macro -Wno-comma)


project(dadengine VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src/)

add_subdirectory(test/)

# add_subdirectory(doc/)

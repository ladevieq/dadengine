cmake_minimum_required(VERSION 3.10)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
# set(CMAKE_CXX_CPPCHECK cppcheck)

add_compile_options(-fcolor-diagnostics -fansi-escape-codes -Wall -Wextra -Wno-c++98-compat -Wno-reserved-id-macro -Wno-comma)

enable_testing()

project(dadengine VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src/)

add_subdirectory(test/)

# add_subdirectory(doc/)

add_subdirectory(types/collection)

add_executable(core-tests ${DADENGINE_CORE_TEST_SRC} main.cpp)

target_include_directories(core-tests PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core)

target_link_libraries(core-tests core Catch2::Catch2)

# Allow ctest to register this executable as a test exe
catch_discover_tests(core-tests)

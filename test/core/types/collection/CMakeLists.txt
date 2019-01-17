add_executable(tarray-tests tarray-tests.cpp)

target_include_directories(tarray-tests PRIVATE ${CMAKE_SOURCE_DIR}/include/dadengine/core/types/collection/)
target_link_libraries(tarray-tests core Catch2::Catch2)

catch_discover_tests(tarray-tests)
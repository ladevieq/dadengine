find_path(CATCH_INCLUDE_DIR NAMES catch.hpp PATH_SUFFIXES catch2)

include_directories(${CATCH_INCLUDE_DIR})

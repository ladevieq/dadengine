#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "tarray.hpp"

using namespace DadEngine::Core;

TEST_CASE("Constructor", "[tarray]")
{
    SECTION("Constructing with normal value")
    {
        TArray<int> testArr = TArray<int>(6);

        REQUIRE(testArr.Size() == 6);
    }

	SECTION("Constructing a zero sized array")
    {
        TArray<int> testArr = TArray<int>(0);

        REQUIRE(testArr.Size() == 0);
    }
}
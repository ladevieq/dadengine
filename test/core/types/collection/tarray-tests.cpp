#include <catch2/catch.hpp>

#include "types/collection/tarray.hpp"

using namespace DadEngine;

TEST_CASE_METHOD(TArray<int>, "Constructing with normal value", "[constructor]")
{
    REQUIRE(TArray<int>{ 6 }.Size() == 6);
}

TEST_CASE_METHOD(TArray<int>, "Constructing a zero sized array", "[constructor]")
{
    REQUIRE(this->Size() == 0);
}

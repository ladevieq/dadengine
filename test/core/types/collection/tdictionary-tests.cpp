#include <catch2/catch.hpp>

#include "types/collection/tdictionary.hpp"

using namespace DadEngine;

using Bla = TDictionary<int, int>;

TEST_CASE_METHOD(Bla, "Constructor tdictionary", "[tdictionary]")
{
    REQUIRE(this->Data().size() == 0);
}

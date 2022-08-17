#include <catch2/catch_test_macros.hpp>

static int func(int a) {
    return a +1;
}

TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( func(0) == 0 );
}
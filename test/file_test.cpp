#include <catch2/catch_test_macros.hpp>
#include <file/file_util.h>

TEST_CASE( "file size", "[single-file]" ) {
    REQUIRE( plan9::file_util::get_size_from_file("./1.txt") == 17930 );
}
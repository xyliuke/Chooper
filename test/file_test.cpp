#include <catch2/catch_test_macros.hpp>
#include <file/file_util.h>

TEST_CASE( "file size", "[single-file]" ) {
    size_t s = plan9::file_util::get_size_from_file("/Users/liuke/01.jpg");
    REQUIRE( s == 1591731 );
}
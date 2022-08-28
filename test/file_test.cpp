#include <catch2/catch_test_macros.hpp>
#include <file/file_util.h>

TEST_CASE( "file size", "[single-file]" ) {
    size_t s = plan9::FileUtil::GetSize("/Users/liuke/01.jpg");
    REQUIRE( s == 1591731 );
}
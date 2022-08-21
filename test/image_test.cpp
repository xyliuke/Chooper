#include <catch2/catch_test_macros.hpp>
#include <image/image.h>


TEST_CASE( "image_size", "[single-file]" ) {
    auto img = new plan9::image("../../test/resource/2.jpg");
    auto buf = new unsigned char[1024 * 1024 * 30];
    size_t s = img->get_data(buf);
    REQUIRE( s == 3381090 );
}
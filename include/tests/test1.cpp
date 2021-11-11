#include "../etr.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"



TEST_CASE( "vector creation" ) {
  VEC<double> a = range(1, 3);
    REQUIRE( a[0] == 1 );
    REQUIRE( a[1] == 2 );
    REQUIRE( a[2] == 3 );
}


TEST_CASE( "vector subsetting" ) {
  VEC<double> a = range(1, 3);
    REQUIRE( subset(a, 2)[0] == 2.);
}

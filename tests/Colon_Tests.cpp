
#define STANDALONE_ETR
#include "../include/etr.hpp"

#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"

TEST_CASE("rep arithmetic arithmetic") {
  SECTION("integers") {
    etr::Vec<double> vec1 = etr::colon(-1, 10);
    REQUIRE(vec1[0] == -1);
    REQUIRE(vec1[1] == 0);
    REQUIRE(vec1[2] == 1);
    REQUIRE(vec1[3] == 2);
    REQUIRE(vec1[11] == 10);

    etr::Vec<double> vec2 = etr::colon(10, -2);
    REQUIRE(vec2[0] == 10);
    REQUIRE(vec2[1] == 9);
    REQUIRE(vec2[2] == 8);
    REQUIRE(vec2[3] == 7);
    REQUIRE(vec2[11] == -1);
    REQUIRE(vec2[12] == -2);

    etr::Vec<double> vec3 = etr::colon(10.25, -1.5);
    REQUIRE(vec3[0] == 10.25);
    REQUIRE(vec3[1] == 9.25);
    REQUIRE(vec3[2] == 8.25);
    REQUIRE(vec3[3] == 7.25);
    REQUIRE(vec3[11] == -0.75);

    etr::Vec<double> vec4 = etr::colon(1.25, 4.6);
    REQUIRE(vec4[0] == 1.25);
    REQUIRE(vec4[1] == 2.25);
    REQUIRE(vec4[2] == 3.25);
    REQUIRE(vec4[3] == 4.25);

    etr::Vec<double> vec5 = etr::colon(1.25, 5);
    REQUIRE(vec5[0] == 1.25);
    REQUIRE(vec5[1] == 2.25);
    REQUIRE(vec5[2] == 3.25);
    REQUIRE(vec5[3] == 4.25);

    etr::Vec<double> vec6 = etr::colon(1, 4.6);
    REQUIRE(vec6[0] == 1);
    REQUIRE(vec6[1] == 2);
    REQUIRE(vec6[2] == 3);
    REQUIRE(vec6[3] == 4);
  }
}

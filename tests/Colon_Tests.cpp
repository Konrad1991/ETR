
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

TEST_CASE("Vector & arithmetic") {
  SECTION("L vectors") {
    etr::Vec<double> v = etr::coca(1, 2, 3);
    etr::Vec<double> vec1 = etr::colon(v, 10);
    REQUIRE(vec1.size() == 10);
    etr::Vec<double> vec2 = etr::colon(v, 1);
    REQUIRE(vec2.size() == 1);
    REQUIRE(vec2[0] == 1);
    v[0] = 0;
    etr::Vec<double> vec3 = etr::colon(v, 0);
    REQUIRE(vec3.size() == 1);
    REQUIRE(vec3[0] == 0);

    REQUIRE(etr::colon(etr::coca(1, 2, 3), 7).size() == 7);
    REQUIRE(etr::colon(etr::coca(1, 2, 3), 1).size() == 1);
    REQUIRE(etr::colon(etr::coca(1, 2, 3), 1)[0] == 1);
    REQUIRE(etr::colon(etr::coca(0, 2, 3), 0)[0] == 0);
    REQUIRE(etr::colon(etr::coca(0, 2, 3), 0).size() == 1);
  }

  SECTION("R vectors") {
    REQUIRE(etr::colon(etr::coca(1, 2, 3) + 0, 7).size() == 7);
    REQUIRE(etr::colon(etr::coca(1, 2, 3) + 0, 1).size() == 1);
    REQUIRE(etr::colon(etr::coca(1, 2, 3) + 0, 1)[0] == 1);
    REQUIRE(etr::colon(etr::coca(0, 2, 3) + 0, 0)[0] == 0);
    REQUIRE(etr::colon(etr::coca(0, 2, 3) + 0, 0).size() == 1);
  }

  SECTION("vector with length 1") {
    REQUIRE(etr::colon(etr::coca(0) + 0, 0).size() == 1);
  }
}

TEST_CASE("arithmetic & vector") {
  SECTION("L vectors") {
    etr::Vec<double> v = etr::coca(1, 2, 3);
    etr::Vec<double> vec1 = etr::colon(10, v);
    REQUIRE(vec1.size() == 10);
    REQUIRE(vec1[0] == 10);
    REQUIRE(vec1[1] == 9);
    REQUIRE(vec1[2] == 8);
    REQUIRE(vec1[9] == 1);
  }

  SECTION("Empty vector") {
    etr::Vec<double> v; // issue: this is a fundamental difference to R. One
                        // cannot create an empty vector!
    etr::Vec<double> vec1 = etr::colon(10, v);
    REQUIRE(vec1.size() == 11);
  }

  SECTION("Single element vector") {
    etr::Vec<double> v = etr::coca(5);
    etr::Vec<double> vec1 = etr::colon(10, v);
    REQUIRE(vec1.size() == 6);
    REQUIRE(vec1[0] == 10);
    REQUIRE(vec1[5] == 5);
  }

  SECTION("Negative start value") {
    etr::Vec<double> v = etr::coca(1, 2, 3);
    etr::Vec<double> vec1 = etr::colon(-5, v);
    REQUIRE(vec1.size() == 7);
    REQUIRE(vec1[0] == -5);
    REQUIRE(vec1[1] == -4);
  }
}

TEST_CASE("vector & vector") {
  SECTION("Same type") {
    etr::Vec<double> v1 = etr::coca(1, 2, 3);
    etr::Vec<double> v2 = etr::coca(4, 5, 6);
    etr::Vec<double> result = etr::colon(v1, v2);
    REQUIRE(result.size() == 4);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 2);
    REQUIRE(result[2] == 3);
    REQUIRE(result[3] == 4);
  }

  SECTION("Different types") {
    etr::Vec<int> v1 = etr::coca(1, 2, 3);
    etr::Vec<double> v2 = etr::coca(4, 5, 6);
    etr::Vec<double> result = etr::colon(v1, v2);
    REQUIRE(result.size() == 4);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 2);
    REQUIRE(result[2] == 3);
    REQUIRE(result[3] == 4);
  }
}

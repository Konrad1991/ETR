
#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

void test_colon_arithmetic() {
  // NOTE: arithmetics
  {
    Vec<double> vec1 = colon(-1, 10);
    ass(vec1[0] == -1, "vec1[0] == -1");
    ass(vec1[1] == 0, "vec1[1] == 0");
    ass(vec1[2] == 1, "vec1[2] == 1");
    ass(vec1[3] == 2, "vec1[3] == 2");
    ass(vec1[4] == 3, "vec1[4] == 3");

    Vec<double> vec2 = colon(10, -2);
    ass(vec2[0] == 10, "vec1[0] == 10");
    ass(vec2[1] == 9, "vec1[1] == 9");
    ass(vec2[2] == 8, "vec1[2] == 8");
    ass(vec2[3] == 7, "vec1[3] == 7");
    ass(vec2[11] == -1, "vec1[11] == -1");
    ass(vec2[12] == -2, "vec1[12] == -2");

    etr::Vec<double> vec3 = etr::colon(10.25, -1.5);
    ass(vec3[0] == 10.25, "vec3[0] == 10.25");
    ass(vec3[1] == 9.25, "vec3[1] == 9.25");
    ass(vec3[2] == 8.25, "vec3[2] == 8.25");
    ass(vec3[3] == 7.25, "vec3[3] == 7.25");
    ass(vec3[11] == -0.75, "vec3[11] == -0.75");

    etr::Vec<double> vec4 = etr::colon(1.25, 4.6);
    ass(vec4[0] == 1.25, "vec4[0] == 1.25");
    ass(vec4[1] == 2.25, "vec4[1] == 2.25");
    ass(vec4[2] == 3.25, "vec4[2] == 3.25");
    ass(vec4[3] == 4.25, "vec4[3] == 4.25");

    etr::Vec<double> vec5 = etr::colon(1.25, 5);
    ass(vec5[0] == 1.25, "vec5[0] == 1.25");
    ass(vec5[1] == 2.25, "vec5[1] == 2.25");
    ass(vec5[2] == 3.25, "vec5[2] == 3.25");
    ass(vec5[3] == 4.25, "vec5[3] == 4.25");

    etr::Vec<double> vec6 = etr::colon(1, 4.6);
    ass(vec6[0] == 1, "vec6[0] == 1");
    ass(vec6[1] == 2, "vec6[1] == 2");
    ass(vec6[2] == 3, "vec6[2] == 3");
    ass(vec6[3] == 4, "vec6[3] == 4");
  }

  // NOTE: vectors and arithmetics
  {
    etr::Vec<double> v = etr::coca(1, 2, 3);
    etr::Vec<double> vec1 = etr::colon(v, 10);
    ass(vec1.size() == 10, "vec size = 10");
    etr::Vec<double> vec2 = etr::colon(v, 1);
    ass(vec2.size() == 1, "vec size = 1");
    ass(vec2[0] == 1, "vec2[0] == 1");
    v[0] = 0;
    etr::Vec<double> vec3 = etr::colon(v, 0);
    ass(vec3.size() == 1, "vec size == 1");
    ass(vec3[0] == 0, "vec3[0] == 0");
    ass(etr::colon(etr::coca(1, 2, 3), 7).size() == 7, "vec size == 7");
    ass(etr::colon(etr::coca(1, 2, 3), 1).size() == 1, "vec size == 1");
    ass(etr::colon(etr::coca(1, 2, 3), 1)[0] == 1, "vec[0] == 1 ");
    ass(etr::colon(etr::coca(0, 2, 3), 0)[0] == 0, "vec[0] == 0");
    ass(etr::colon(etr::coca(0, 2, 3), 0).size() == 1, "vec size == 1");
    ass(etr::colon(etr::coca(0) + 0, 0).size() == 1, "vec size == 1");
  }
}

int main() { test_colon_arithmetic(); }

/*


TEST_CASE("Vector & arithmetic") {
  SECTION("L vectors") {
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
*/

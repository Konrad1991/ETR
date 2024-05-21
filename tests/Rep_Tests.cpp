#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

void test_rep() {
  rep(1, 2);
  Vec<int> idx = coca(1, 2, 3);
  rep(1, idx);
  rep(1, coca(1, 2, 3));
}

int main(int argc, char *argv[]) {
  test_rep();
  return 0;
}

/*
TEST_CASE("rep arithmetic arithmetic") {
    SECTION("integers") {
        etr::Vec<double> vec1 = etr::rep(5, 3);
        REQUIRE(vec1.size() == 3);
        REQUIRE_THROWS_AS(etr::rep(-1, 0), std::exception);
        REQUIRE_THROWS_AS(etr::rep(-1, -1), std::exception);
    }
    SECTION("doubles") {
        etr::Vec<double> vec1 = etr::rep(5.0, 3.1);
        REQUIRE(vec1.size() == 3);
    }
    SECTION("bools") {
        etr::Vec<double> vec1 = etr::rep(5.0, true);
        REQUIRE(vec1.size() == 1);
        REQUIRE_THROWS_AS(etr::rep(0, false), std::exception);
    }
}

TEST_CASE("rep Vec arithmetic") {
    etr::Vec<double> v = etr::coca(1, 2, 3, 4);
    SECTION("integers") {
        etr::Vec<double> vec1 = etr::rep(v, 3);
        REQUIRE(vec1.size() == 12);
        REQUIRE_THROWS_AS(etr::rep(v, 0), std::exception);
        REQUIRE_THROWS_AS(etr::rep(v, -1), std::exception);
    }
    SECTION("doubles") {
        etr::Vec<double> vec1 = etr::rep(v, 4.1);
        REQUIRE(vec1.size() == 16);
        REQUIRE(vec1[4] == 1);
    }
    SECTION("bools") {
        etr::Vec<double> vec1 = etr::rep(v, true);
        REQUIRE(vec1.size() == 4);
        REQUIRE_THROWS_AS(etr::rep(v, false), std::exception);
    }
}


TEST_CASE("rep const Vec arithmetic") {
    SECTION("integers") {
        etr::Vec<double> vec1 = etr::rep(etr::coca(1, 2, 3, 4) + etr::coca(1,
2), 3); REQUIRE(vec1.size() == 12); REQUIRE_THROWS_AS(etr::rep(etr::coca(1) + 7,
0), std::exception); REQUIRE_THROWS_AS(etr::rep(etr::coca(1, 6, 6) +
etr::vector(20), -1), std::exception);
    }
    SECTION("doubles") {
        etr::Vec<double> vec1 = etr::rep(etr::coca(1, 2, 3, 4) + 4.5, 4.1);
        REQUIRE(vec1.size() == 16);
        REQUIRE(vec1[4] == 1 + 4.5);
    }
    SECTION("bools") {
        etr::Vec<double> vec1 = etr::rep(1.5 + etr::coca(1, 7, 8, 9), true);
        REQUIRE(vec1.size() == 4);
        REQUIRE_THROWS_AS(etr::rep(etr::coca(1) + 6, false), std::exception);
    }
}

TEST_CASE("rep (const) arithmetic vec") {
        etr::Vec<double> v = etr::vector(5);
        REQUIRE_THROWS_AS(etr::rep(5, v), std::exception);
        etr::Vec<double> correct = etr::coca(4);
        REQUIRE(etr::rep(5, correct).size() == 4);
        REQUIRE_THROWS_AS(etr::rep(5, etr::coca(-1)), std::exception);
        REQUIRE_THROWS_AS(etr::rep(5, etr::coca(0)), std::exception);
}


TEST_CASE("(const) vec & (const) vec") {
  etr::Vec<double> v1 = etr::coca(1, 2, 3, 4);
  etr::Vec<double> v2 = etr::coca(1, 2, 3, 4);
  etr::Vec<double> v3 = etr::coca(1, 2, 3, 4);
  etr::Vec<double> correctRepArg = etr::coca(4);

  REQUIRE_THROWS_AS(etr::rep(v1, v2), std::exception);
  REQUIRE_THROWS_AS(etr::rep(v1, v1 + v2), std::exception);
  REQUIRE_THROWS_AS(etr::rep(v1 + 3, v1 + v2), std::exception);
  REQUIRE_THROWS_AS(etr::rep(v1, etr::coca(-1)), std::exception);
  REQUIRE_THROWS_AS(etr::rep(v1, etr::coca(0)), std::exception);
  REQUIRE(etr::rep(v1, correctRepArg).size() == 16);
  REQUIRE(etr::rep(v1, etr::coca(5)).size() == 20);
  REQUIRE(etr::rep(v1 + v2, etr::coca(5)).size() == 20);
}
*/

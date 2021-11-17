#include "../include/etr.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "plus" ) {

  sexp s, v, m;
  s = 1;
  s = s + 3;
  REQUIRE(subset(s, 1)[0] == 4);

  v = s + vector(4, 4);
  REQUIRE(subset(v, 1)[0] == 8);
  REQUIRE(subset(v, 2)[0] == 8);
  REQUIRE(subset(v, 3)[0] == 8);
  REQUIRE(subset(v, 4)[0] == 8);

  v = vector(4, 4);
  v = v + 30;
  REQUIRE(subset(v, 1)[0] == 34);
  REQUIRE(subset(v, 2)[0] == 34);
  REQUIRE(subset(v, 3)[0] == 34);
  REQUIRE(subset(v, 4)[0] == 34);


  m = s + matrix(2, 2, 2);
  for(auto i: m) {
    REQUIRE(i == 6);
  }

  m = matrix(2, 2, 2);
  m = m + 40;
  for(auto i: m) {
    REQUIRE(i == 42);
  }

  m = v + m;
  for(auto i: m) {
    REQUIRE(i == 76);
  }

  m = m + v;
  for(auto i: m) {
    REQUIRE(i == 110);
  }

}



TEST_CASE( "minus" ) {

  sexp s, v, m;
  s = 1;
  s = s - 3;
  REQUIRE(subset(s, 1)[0] == -2);

  v = s - vector(4, 4);

  REQUIRE(subset(v, 1)[0] == -6);
  REQUIRE(subset(v, 2)[0] == -6);
  REQUIRE(subset(v, 3)[0] == -6);
  REQUIRE(subset(v, 4)[0] == -6);

  v = vector(4, 4);
  v = v - 30;
  REQUIRE(subset(v, 1)[0] == -26);
  REQUIRE(subset(v, 2)[0] == -26);
  REQUIRE(subset(v, 3)[0] == -26);
  REQUIRE(subset(v, 4)[0] == -26);

  m = s - matrix(2, 2, 2);
  for(auto i: m) {
    REQUIRE(i == -4);
  }

  m = matrix(2, 2, 2);
  m = m - 40;
  for(auto i: m) {
    REQUIRE(i == -38);
  }

  m = v - m;
  for(auto i: m) {
    REQUIRE(i == 12);
  }

  m = m - v;
  for(auto i: m) {
    REQUIRE(i == 38);
  }


}




TEST_CASE( "divide" ) {

  sexp s, v, m;
  s = 3;
  s = s / 3;
  REQUIRE(subset(s, 1)[0] == 1);

  v = s / vector(4, 4);
  REQUIRE(subset(v, 1)[0] == 0.25);
  REQUIRE(subset(v, 2)[0] == 0.25);
  REQUIRE(subset(v, 3)[0] == 0.25);
  REQUIRE(subset(v, 4)[0] == 0.25);

  v = vector(4, 4);
  v = v / 2;
  REQUIRE(subset(v, 1)[0] == 2);
  REQUIRE(subset(v, 2)[0] == 2);
  REQUIRE(subset(v, 3)[0] == 2);
  REQUIRE(subset(v, 4)[0] == 2);


  m = s / matrix(2, 2, 2);
  for(auto i: m) {
    REQUIRE(i == 0.5);
  }

  m = matrix(2, 2, 2);
  m = m / 40;
  for(auto i: m) {
    REQUIRE(i == 0.05);
  }


  m = v / m;
  for(auto i: m) {
    REQUIRE(i == 40);
  }

  m = m / v;
  for(auto i: m) {
    REQUIRE(i == 20);
  }

}



TEST_CASE( "multiply" ) {

  sexp s, v, m;
  s = 3;
  s = s * 3;
  REQUIRE(subset(s, 1)[0] == 9);

  v = s * vector(4, 4);
  REQUIRE(subset(v, 1)[0] == 36);
  REQUIRE(subset(v, 2)[0] == 36);
  REQUIRE(subset(v, 3)[0] == 36);
  REQUIRE(subset(v, 4)[0] == 36);


  v = vector(4, 4);
  v = v * 2;
  REQUIRE(subset(v, 1)[0] == 8);
  REQUIRE(subset(v, 2)[0] == 8);
  REQUIRE(subset(v, 3)[0] == 8);
  REQUIRE(subset(v, 4)[0] == 8);


  m = s * matrix(2, 2, 2);
  for(auto i: m) {
    REQUIRE(i == 18);
  }


  m = matrix(2, 2, 2);
  m = m * 40;
  for(auto i: m) {
    REQUIRE(i == 80);
  }


  m = v * m;
  for(auto i: m) {
    REQUIRE(i == 640);
  }

  m = m * v;
  for(auto i: m) {
    REQUIRE(i == 5120);
  }


}

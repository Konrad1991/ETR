#include "../include/etr.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "vector subsetting" ) {

  sexp a = range(1, 5);
  sexp b = coca(1, 3, 5);
  VEC<bool> bb(7);
  bb[0] = true;
  bb[1] = false;
  bb[2] = true;
  bb[3] = true;
  bb[4] = true;
  bb[5] = true;
  bb[6] = true;

  REQUIRE(subset(a, 1)[0] == 1.0);

  REQUIRE(subset(a, 1.1)[0] == 1.0);
  sexp result;
  result = subset(a, b);
  REQUIRE(result[0] == 1.0);
  REQUIRE(result[1] == 3.0);
  REQUIRE(result[2] == 5.0);

  result = subset(a, bb);
  REQUIRE(result[0] == 1.0);
  REQUIRE(result[1] == 3.0);
  REQUIRE(result[2] == 4.0);
  REQUIRE(result[3] == 5.0);
  REQUIRE(result[4] == 1.0);
  REQUIRE(result[5] == 2.0);

}

TEST_CASE( "matrix subsetting" ) {
  sexp a, r, c;
  VEC<bool> cb(5);
  VEC<bool> rb(6);

  a = matrix(colon(1, 15), 5, 3);
  r = coca(1, 2, 5);
  c = coca(1, 3, 1, 1);
  cb[0] = true;
  cb[1] = false;
  cb[2] = true;
  cb[3] = true;
  cb[4] = true;

  rb[0] = true;
  rb[1] = false;
  rb[2] = true;
  rb[3] = true;
  rb[4] = true;
  rb[5] = true;

  sexp result;

  result = subset(a, 1, 2);
  REQUIRE( result[0] == 6.0);
  result = subset(a, 5, 3.1);
  REQUIRE( result[0] == 15.0);
  result = subset(a, 2., 3.);
  REQUIRE( result[0] == 12.0);
  result = subset(a, 4., 1.);
  REQUIRE( result[0] == 4.0);

  result = subset(a, 1, true);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 6.0);
  REQUIRE( result[2] == 11.0);

  result = subset(a, 4, true);
  REQUIRE( result[0] == 4.0);
  REQUIRE( result[1] == 9.0);
  REQUIRE( result[2] == 14.0);


  result = subset(a, 1, nullptr);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 6.0);
  REQUIRE( result[2] == 11.0);

  result = subset(a, 1, c);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 11.0);
  REQUIRE( result[2] == 1.0);
  REQUIRE( result[3] == 1.0);

  result = subset(a, 5, c);
  REQUIRE( result[0] == 5.0);
  REQUIRE( result[1] == 15.0);
  REQUIRE( result[2] == 5.0);
  REQUIRE( result[3] == 5.0);

  result = subset(a, 1, cb);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 11.0);
  REQUIRE( result[2] == 1.0);
  REQUIRE( result[3] == 6.0);

  result = subset(a, true, 1);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 2.0);
  REQUIRE( result[2] == 3.0);
  REQUIRE( result[3] == 4.0);
  REQUIRE( result[4] == 5.0);

  result = subset(a, r, 2);
  REQUIRE( result[0] == 6.0);
  REQUIRE( result[1] == 7.0);
  REQUIRE( result[2] == 10.0);

  result = subset(a, r, 3);
  REQUIRE( result[0] == 11.0);
  REQUIRE( result[1] == 12.0);
  REQUIRE( result[2] == 15.0);

  result = subset(a, rb, 1);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 3.0);
  REQUIRE( result[2] == 4.0);
  REQUIRE( result[3] == 5.0);
  REQUIRE( result[4] == 1.0);


  result = subset(a, true, c);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 2.0);
  REQUIRE( result[2] == 3.0);
  REQUIRE( result[3] == 4.0);
  REQUIRE( result[4] == 5.0);
  REQUIRE( result[5] == 11.0);
  REQUIRE( result[6] == 12.0);
  REQUIRE( result[7] == 13.0);
  REQUIRE( result[8] == 14.0);
  REQUIRE( result[9] == 15.0);
  REQUIRE( result[10] == 1.0);
  REQUIRE( result[11] == 2.0);
  REQUIRE( result[12] == 3.0);
  REQUIRE( result[13] == 4.0);
  REQUIRE( result[14] == 5.0);
  REQUIRE( result[15] == 1.0);
  REQUIRE( result[16] == 2.0);
  REQUIRE( result[17] == 3.0);
  REQUIRE( result[18] == 4.0);
  REQUIRE( result[19] == 5.0);

  result = subset(a, true, cb);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 2.0);
  REQUIRE( result[2] == 3.0);
  REQUIRE( result[3] == 4.0);
  REQUIRE( result[4] == 5.0);
  REQUIRE( result[5] == 11.0);
  REQUIRE( result[6] == 12.0);
  REQUIRE( result[7] == 13.0);
  REQUIRE( result[8] == 14.0);
  REQUIRE( result[9] == 15.0);
  REQUIRE( result[10] == 1.0);
  REQUIRE( result[11] == 2.0);
  REQUIRE( result[12] == 3.0);
  REQUIRE( result[13] == 4.0);
  REQUIRE( result[14] == 5.0);
  REQUIRE( result[15] == 6.0);
  REQUIRE( result[16] == 7.0);
  REQUIRE( result[17] == 8.0);
  REQUIRE( result[18] == 9.0);
  REQUIRE( result[19] == 10.0);

  result = subset(a, r, true);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 2.0);
  REQUIRE( result[2] == 5.0);
  REQUIRE( result[3] == 6.0);
  REQUIRE( result[4] == 7.0);
  REQUIRE( result[5] == 10.0);
  REQUIRE( result[6] == 11.0);
  REQUIRE( result[7] == 12.0);
  REQUIRE( result[8] == 15.0);


  result = subset(a, rb, true);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 3.0);
  REQUIRE( result[2] == 4.0);
  REQUIRE( result[3] == 5.0);
  REQUIRE( result[4] == 1.0);
  REQUIRE( result[5] == 6.0);
  REQUIRE( result[6] == 8.0);
  REQUIRE( result[7] == 9.0);
  REQUIRE( result[8] == 10.0);
  REQUIRE( result[9] == 6.0);
  REQUIRE( result[10] == 11.0);
  REQUIRE( result[11] == 13.0);
  REQUIRE( result[12] == 14.0);
  REQUIRE( result[13] == 15.0);
  REQUIRE( result[14] == 11.0);

  result = subset(a, r, c);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 2.0);
  REQUIRE( result[2] == 5.0);
  REQUIRE( result[3] == 11.0);
  REQUIRE( result[4] == 12.0);
  REQUIRE( result[5] == 15.0);
  REQUIRE( result[6] == 1.0);
  REQUIRE( result[7] == 2.0);
  REQUIRE( result[8] == 5.0);
  REQUIRE( result[9] == 1.0);
  REQUIRE( result[10] == 2.0);
  REQUIRE( result[11] == 5.0);


  result = subset(a, r, cb);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 2.0);
  REQUIRE( result[2] == 5.0);
  REQUIRE( result[3] == 11.0);
  REQUIRE( result[4] == 12.0);
  REQUIRE( result[5] == 15.0);
  REQUIRE( result[6] == 1.0);
  REQUIRE( result[7] == 2.0);
  REQUIRE( result[8] == 5.0);
  REQUIRE( result[9] == 6.0);
  REQUIRE( result[10] == 7.0);
  REQUIRE( result[11] == 10.0);

  result = subset(a, rb, c);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 3.0);
  REQUIRE( result[2] == 4.0);
  REQUIRE( result[3] == 5.0);
  REQUIRE( result[4] == 1.0);
  REQUIRE( result[5] == 11.0);
  REQUIRE( result[6] == 13.0);
  REQUIRE( result[7] == 14.0);
  REQUIRE( result[8] == 15.0);
  REQUIRE( result[9] == 11.0);
  REQUIRE( result[10] == 1.0);
  REQUIRE( result[11] == 3.0);
  REQUIRE( result[12] == 4.0);
  REQUIRE( result[13] == 5.0);
  REQUIRE( result[14] == 1.0);
  REQUIRE( result[15] == 1.0);
  REQUIRE( result[16] == 3.0);
  REQUIRE( result[17] == 4.0);
  REQUIRE( result[18] == 5.0);
  REQUIRE( result[19] == 1.0);


  result = subset(a, rb, cb);
  REQUIRE( result[0] == 1.0);
  REQUIRE( result[1] == 3.0);
  REQUIRE( result[2] == 4.0);
  REQUIRE( result[3] == 5.0);
  REQUIRE( result[4] == 1.0);
  REQUIRE( result[5] == 11.0);
  REQUIRE( result[6] == 13.0);
  REQUIRE( result[7] == 14.0);
  REQUIRE( result[8] == 15.0);
  REQUIRE( result[9] == 11.0);
  REQUIRE( result[10] == 1.0);
  REQUIRE( result[11] == 3.0);
  REQUIRE( result[12] == 4.0);
  REQUIRE( result[13] == 5.0);
  REQUIRE( result[14] == 1.0);
  REQUIRE( result[15] == 6.0);
  REQUIRE( result[16] == 8.0);
  REQUIRE( result[17] == 9.0);
  REQUIRE( result[18] == 10.0);
  REQUIRE( result[19] == 6.0);




}

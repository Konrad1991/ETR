#include "../include/etr.hpp"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"



TEST_CASE( "stuff2" ) {



  void bs(sexp& arr) {
    sexp size = length(arr);
    sexp swapped = true;

    do {
      swapped = false;

      for(auto i: colon(1, size-1)) {

        if(subset(arr, i) > subset(arr, i + 1) ) {
            sexp temp = subset(arr, i);
            subassign(arr, i) = subset(arr, i + 1);
            subassign(arr, i + 1) = temp;
            swapped = true;
        }

      }
    } while(swapped);


  }



    sexp arr = coca(3, 2, 8, 1, 0);

    print(arr);

    bs(arr);

    print();

    print(arr);

}

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




TEST_CASE( "subassign vector" ) {

sexp a, pos, temp;

a = vector(colon(0, 9));
temp = a;

subassign(a, 1) = 100;
subassign(a, 2.5) = 200;
REQUIRE(subset(a, 1)[0] == 100.0);
REQUIRE(subset(a, 2.5)[0] == 200.0);
a = temp;

pos = coca(1, 6, 7, 2);
subassign(a, pos) = range(1, 4);
REQUIRE(subset(a, 1)[0] == 1.0);
REQUIRE(subset(a, 6)[0] == 2.0);
REQUIRE(subset(a, 7)[0] == 3.0);
REQUIRE(subset(a, 2)[0] == 4.0);
a = temp;

VEC<bool> pb(4);
pb[0] = true;
pb[1] = true;
pb[2] = false;
pb[3] = true;
subassign(a, pb) = range(1, 3);
REQUIRE(subset(a, 1)[0] == 1.0);
REQUIRE(subset(a, 2)[0] == 2.0);
REQUIRE(subset(a, 4)[0] == 3.0);
a = temp;


subassign(a, true) = -60;
for(auto i: a) {
  REQUIRE(i == -60);
}
subassign(a, nullptr) = -50;
for(auto i: a) {
  REQUIRE(i == -50);
}

}



TEST_CASE( "subassign matrix" ) {

  sexp a, r, c, temp;
  VEC<bool> cb(8);
  VEC<bool> rb(6);

  a = matrix(colon(0, 34), 5, 7);
  temp = a;
  r = coca(1, 2, 5);
  c = coca(1, 3, 2);
  cb[0] = true;
  cb[1] = true;
  cb[2] = true;
  cb[3] = true;
  cb[4] = false;
  cb[5] = false;
  cb[6] = false;
  cb[7] = true;

  rb[0] = true;
  rb[1] = false;
  rb[2] = true;
  rb[3] = true;
  rb[4] = true;
  rb[5] = true;

subassign(a, 1, 1) = 100;
subassign(a, 1, 2.5) = 200;
REQUIRE(subset(a, 1, 1)[0] == 100.0);
REQUIRE(subset(a, 1, 2.5)[0] == 200.0);

c = coca(1, 5);
subassign(a, 3, c) = coca(1000, 2000);
subassign(a, 4, cb) = coca(100, 200, 300, 400, 500);
REQUIRE(subset(a, 3, 1)[0] == 1000.0);
REQUIRE(subset(a, 3, 5)[0] == 2000.0);

REQUIRE(subset(a, 4, cb)[0] == 500.0);
REQUIRE(subset(a, 4, cb)[1] == 200.0);
REQUIRE(subset(a, 4, cb)[2] == 300.0);
REQUIRE(subset(a, 4, cb)[3] == 400.0);
REQUIRE(subset(a, 4, cb)[4] == 500.0);


a = temp;
subassign(a, true, 5) = coca(-1, -2, -3, -4, -5);
subassign(a, nullptr, 1) = coca(-1, -2, -3, -4, -5);
REQUIRE(subset(a, true, 5)[0] == -1);
REQUIRE(subset(a, true, 5)[1] == -2);
REQUIRE(subset(a, true, 5)[2] == -3);
REQUIRE(subset(a, true, 5)[3] == -4);
REQUIRE(subset(a, true, 5)[4] == -5);

REQUIRE(subset(a, true, 1)[0] == -1);
REQUIRE(subset(a, true, 1)[1] == -2);
REQUIRE(subset(a, true, 1)[2] == -3);
REQUIRE(subset(a, true, 1)[3] == -4);
REQUIRE(subset(a, true, 1)[4] == -5);
a = temp;

r = coca(1, 2, 3);
subassign(a, r, 2) = coca(1.5, 2.5, 3.5);
VEC<bool> rb_(6);
rb_[0] = true;
rb_[1] = true;
rb_[2] = true;
rb_[3] = false;
rb_[4] = false;
rb_[5] = true;
subassign(a, rb_, 3) = coca(1, 2, 3, 50);
REQUIRE(subset(a, rb_, 3)[0] == 50);
REQUIRE(subset(a, rb_, 3)[1] == 2);
REQUIRE(subset(a, rb_, 3)[2] == 3);
a = temp;

subassign(a, true, true) = -50;
for(auto i: a) {
  REQUIRE(i == -50);
}
subassign(a, true, nullptr) = -60;
for(auto i: a) {
  REQUIRE(i == -60);
}

a = temp;

c = coca(1, 5, 7);
subassign(a, true, c) = colon(101, 115);
REQUIRE(subset(a, true, c)[0] == 101.0);
REQUIRE(subset(a, true, c)[1] == 102.0);
REQUIRE(subset(a, true, c)[2] == 103.0);
REQUIRE(subset(a, true, c)[3] == 104.0);
REQUIRE(subset(a, true, c)[4] == 105.0);
REQUIRE(subset(a, true, c)[5] == 106.0);
REQUIRE(subset(a, true, c)[6] == 107.0);
REQUIRE(subset(a, true, c)[7] == 108.0);
REQUIRE(subset(a, true, c)[8] == 109.0);
REQUIRE(subset(a, true, c)[9] == 110.0);
REQUIRE(subset(a, true, c)[10] == 111.0);
REQUIRE(subset(a, true, c)[11] == 112.0);
REQUIRE(subset(a, true, c)[12] == 113.0);
REQUIRE(subset(a, true, c)[13] == 114.0);
REQUIRE(subset(a, true, c)[14] == 115.0);
a = temp;



VEC<bool> cb_(8);
cb_[0] = true;
cb_[1] = false;
cb_[2] = false;
cb_[3] = false;
cb_[4] = false;
cb_[5] = false;
cb_[6] = true;
cb_[7] = true;
subassign(a, true, cb_) = colon(91, 105);
REQUIRE(subset(a, 1, 1)[0] == 101.0);
REQUIRE(subset(a, 2, 1)[0] == 102.0);
REQUIRE(subset(a, 3, 1)[0] == 103.0);
REQUIRE(subset(a, 4, 1)[0] == 104.0);
REQUIRE(subset(a, 5, 1)[0] == 105.0);
REQUIRE(subset(a, 1, 7)[0] == 96.0);
REQUIRE(subset(a, 2, 7)[0] == 97.0);
REQUIRE(subset(a, 3, 7)[0] == 98.0);
REQUIRE(subset(a, 4, 7)[0] == 99.0);
REQUIRE(subset(a, 5, 7)[0] == 100.0);

a = temp;


subassign(a, nullptr, true) = -10;
for(auto i: a) {
  REQUIRE(i == -10);
}
a = temp;


r = coca(1, 5, 3);
subassign(a, r, true) = colon(1, 21);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 5, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 2)[0] == 4.0);
REQUIRE(subset(a, 5, 2)[0] == 5.0);
REQUIRE(subset(a, 3, 2)[0] == 6.0);
REQUIRE(subset(a, 1, 3)[0] == 7.0);
REQUIRE(subset(a, 5, 3)[0] == 8.0);
REQUIRE(subset(a, 3, 3)[0] == 9.0);
REQUIRE(subset(a, 1, 4)[0] == 10.0);
REQUIRE(subset(a, 5, 4)[0] == 11.0);
REQUIRE(subset(a, 3, 4)[0] == 12.0);
REQUIRE(subset(a, 1, 5)[0] == 13.0);
REQUIRE(subset(a, 5, 5)[0] == 14.0);
REQUIRE(subset(a, 3, 5)[0] == 15.0);
REQUIRE(subset(a, 1, 6)[0] == 16.0);
REQUIRE(subset(a, 5, 6)[0] == 17.0);
REQUIRE(subset(a, 3, 6)[0] == 18.0);
REQUIRE(subset(a, 1, 7)[0] == 19.0);
REQUIRE(subset(a, 5, 7)[0] == 20.0);
REQUIRE(subset(a, 3, 7)[0] == 21.0);
a = temp;


VEC<bool> temp_(2);
temp_[0] = true;
temp_[1] = true;
subassign(a, temp_, true) = range(1, 14);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 2, 1)[0] == 2.0);
REQUIRE(subset(a, 1, 2)[0] == 3.0);
REQUIRE(subset(a, 2, 2)[0] == 4.0);
REQUIRE(subset(a, 1, 3)[0] == 5.0);
REQUIRE(subset(a, 2, 3)[0] == 6.0);
REQUIRE(subset(a, 1, 4)[0] == 7.0);
REQUIRE(subset(a, 2, 4)[0] == 8.0);
REQUIRE(subset(a, 1, 5)[0] == 9.0);
REQUIRE(subset(a, 2, 5)[0] == 10.0);
REQUIRE(subset(a, 1, 6)[0] == 11.0);
REQUIRE(subset(a, 2, 6)[0] == 12.0);
REQUIRE(subset(a, 1, 7)[0] == 13.0);
REQUIRE(subset(a, 2, 7)[0] == 14.0);
a = temp;


subassign(a, nullptr, nullptr) = -20;
for(auto i: a) {
  REQUIRE(i == -20);
}
a = temp; print();


r = coca(1, 5, 3);
c = coca(1, 7, 5);
subassign(a, r, c) = range(1, 9);

REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 5, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 7)[0] == 4.0);
REQUIRE(subset(a, 5, 7)[0] == 5.0);
REQUIRE(subset(a, 3, 7)[0] == 6.0);
REQUIRE(subset(a, 1, 5)[0] == 7.0);
REQUIRE(subset(a, 5, 5)[0] == 8.0);
REQUIRE(subset(a, 3, 5)[0] == 9.0);
a = temp;


VEC<bool> temp2(4);
temp2[0] = true;
temp2[1] = true;
temp2[2] = false;
temp2[3] = true;
subassign(a, r, temp2) = colon(1, 9);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 5, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 2)[0] == 4.0);
REQUIRE(subset(a, 5, 2)[0] == 5.0);
REQUIRE(subset(a, 3, 2)[0] == 6.0);
REQUIRE(subset(a, 1, 4)[0] == 7.0);
REQUIRE(subset(a, 5, 4)[0] == 8.0);
REQUIRE(subset(a, 3, 4)[0] == 9.0);

a = temp;
c = coca(1, 7, 2);
subassign(a, temp2, c) = range(1, 9);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 2, 1)[0] == 2.0);
REQUIRE(subset(a, 4, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 7)[0] == 4.0);
REQUIRE(subset(a, 2, 7)[0] == 5.0);
REQUIRE(subset(a, 4, 7)[0] == 6.0);
REQUIRE(subset(a, 1, 2)[0] == 7.0);
REQUIRE(subset(a, 2, 2)[0] == 8.0);
REQUIRE(subset(a, 4, 2)[0] == 9.0);
a = temp;


VEC<bool> temp3(3);
temp3[0] = true;
temp3[1] = true;
temp3[2] = true;

VEC<bool> temp4(3);
temp4[0] = true;
temp4[1] = false;
temp4[2] = true;
subassign(a, temp3, temp4) = range(1, 6);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 2, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 3)[0] == 4.0);
REQUIRE(subset(a, 2, 3)[0] == 5.0);
REQUIRE(subset(a, 3, 3)[0] == 6.0);
print(sinus(0));

r == c;
r >= c;
r != c;
r > c;
r < c;
r <= c;


}




TEST_CASE( "stuff" ) {

  sexp a = coca(1,2, 3, 4);
  sexp b = coca(1, 2., 100.5, 4.000001);

  sexp vec1 = vector(4);
  sexp vec2 = vector(3.14, 4);
  sexp m1 = matrix(2, 5);
  sexp m2 = matrix(3.14, 5, 5);

  sexp vec3 = colon(1, 5);
  sexp vec4 = colon(1, 5.5);
  sexp vec5 = colon(1.5, 4);
  sexp vec6 = colon(vec3, 7);
  sexp temp1 = 9;
  sexp vec7 = colon(1, temp1);
  sexp temp2 = 1;
  sexp vec8 = colon(temp2, temp1);
  sexp vec9 = colon(temp2, 10);
  length(vec9);
  dim(m1);
  dim(1);
  dim(true);
  dim(3.14);


  VEC<bool> tb;
  print(a == b);
  print(a != b);
  print(a >= b);
  print(a <= b);
  print(a > b);
  print(a < b);

  tb = a < b;
  REQUIRE(tb[0] == true);



}

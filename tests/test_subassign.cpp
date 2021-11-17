#include "../include/etr.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

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


}

#include "etr.hpp"


int main() {

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

print(a);
subassign(a, 1, 1) = 100;
subassign(a, 1, 2.5) = 200;
a = temp; print();

subassign(a, 1, true) = range(1, 7);
subassign(a, 2, nullptr) = range(8, 14);
print(a);
a = temp; print();

c = coca(1, 5);
subassign(a, 3, c) = coca(1000, 2000);
subassign(a, 4, cb) = coca(100, 200, 300, 400, 500);
print(a);

a = temp; print();
subassign(a, true, 5) = coca(-1, -2, -3, -4, -5);
subassign(a, nullptr, 1) = coca(-1, -2, -3, -4, -5);
print(a);
a = temp; print();

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
print(a);
a = temp; print();

subassign(a, true, true) = -50;
print(a);
a = temp; print();

subassign(a, true, nullptr) = -60;
print(a);
a = temp; print();

c = coca(1, 5, 7);
subassign(a, true, c) = range(101, 115);
print(a);
a = temp; print();

VEC<bool> cb_(8);
cb_[0] = true;
cb_[1] = false;
cb_[2] = false;
cb_[3] = false;
cb_[4] = false;
cb_[5] = false;
cb_[6] = true;
cb_[7] = true;
subassign(a, true, cb_) = range(91, 105);
print(a);
a = temp; print();

subassign(a, nullptr, true) = -10;
print(a);
a = temp; print();

r = coca(1, 5, 3);
subassign(a, r, true) = range(1, 21);
print(a);
a = temp; print();

VEC<bool> temp_(2);
temp_[0] = true;
temp_[1] = true;
subassign(a, temp_, true) = range(1, 14);
print(a);
a = temp; print();

subassign(a, nullptr, nullptr) = -20;
print(a);
a = temp; print();

r = coca(1, 5, 3);
c = coca(1, 7, 5);
subassign(a, r, c) = range(1, 9);
print(a);
a = temp; print();


VEC<bool> temp2(4);
temp2[0] = true;
temp2[1] = true;
temp2[2] = false;
temp2[3] = true;
subassign(a, r, temp2) = range(1, 9);
print(a);
a = temp; print();
c = coca(1, 7, 2);
subassign(a, temp2, c) = range(1, 9);
print(a); a = temp; print();

VEC<bool> temp3(3);
temp3[0] = true;
temp3[1] = true;
temp3[2] = true;

VEC<bool> temp4(3);
temp4[0] = true;
temp4[1] = false;
temp4[2] = true;
subassign(a, temp3, temp4) = range(1, 6);
print(a);



}

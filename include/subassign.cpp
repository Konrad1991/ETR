#include "etr.hpp"


int main() {

sexp a, r, c, temp;
VEC<bool> cb(5);
VEC<bool> rb(6);

a = matrix(colon(1, 15), 5, 3);
temp = a;
r = coca(1, 2, 5);
c = coca(1, 3, 2);
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

print(a);
print();
subassign(a, 1, 2) = 100;
print(a);
a = temp;
print();
subassign(a, 2, nullptr) = 1000;
print(a);print();a = temp;
subassign(a, 1, c) = coca(3, 7, 90);
print(a);print();a = temp;

}

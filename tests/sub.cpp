#include "../include/etr.hpp"


int main() {
/*
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

print(a);
print();

print(subset(a, 1, 2));
print(subset(a, 5, 3.1));
print(subset(a, 2., 3));
print(subset(a, 4., 1.));


print();
print(subset(a, 1, true));
print(subset(a, 4, true));
print();



print(subset(a, 1, nullptr));
print("new");
print(subset(a, 1, c));
print();
print(subset(a, 5, c));




print();
print(a);
print();
print(subset(a, 1, cb));
print();
print(a);


print(subset(a, true, 1));
print();



print(subset(a, r, 2));
print(subset(a, r, 3));



print();
print(a);
print(subset(a, rb, 1));
print("new");


print(a);
print(subset(a, true, c));
print();
print(a);
print(subset(a, true, cb));

print();
print(a);
print();
print(subset(a, r, true));

print();
print(a);
print();
print(subset(a, rb, true));

print();
print(a);
print(subset(a, r, c));
print();
print(a);
print();
print(subset(a, r, cb));
*/

/*
print();
print(a);
print();
print(subset(a, rb, c));
print();
print(a);
print();
print(subset(a, rb, cb));

*/


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
print(a);
print();
print(subset(a, bb));

}

#include "etr.hpp"



int main() {

vec a = colon(1, 3);
vec b = colon(2, 4);

vec c;

c = a + b;

print(c);
print();
vec d = c(1, 2);

print(d);
print();
vec e = concatenate(1., 2., c); // does not work

vec f = colon(1, 10);

subset_self(f, 2, 3) = d; // does not work
print(f);


}

#include "etr.hpp"


int main() {

sexp a, b;
b = matrix(range(1, 15), 5, 3);

a = b;
a = 1;
print(a); print();


a = b;
a = coca(1, 2, 3);
print(a); print();

a = b;
a = matrix(range(1, 6), 2, 3);
print(a); print();


sexp c, d;
d = vector(5);
d = coca(1, 2, 3, 4, 5);
c = d;
print(d); print();

d = 1;
print(d); print();
d = c;

d = b;
print(d); print();

d = coca(1,2,3);
print(d); print();

}

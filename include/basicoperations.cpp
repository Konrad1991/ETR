#include "etr.hpp"


int main() {

sexp a = range(1, 15);
a = a + 100.;

print(a);

sexp b = matrix(a, 5, 3);
b = b + a;
print(b);

b = range(1, 20);
print(b);

b = matrix(a, 5, 3);

subassign(b, coca(1, 2, 3), 1) = 200;
print(b);


}

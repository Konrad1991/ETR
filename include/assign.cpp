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

}

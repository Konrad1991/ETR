#include "etr.hpp"


int main() {

  sexp a, b, c, d, e;

  a = matrix(2.3, 2, 2);
  print(a);
  print();
  b = vector(4., 4);
  a = a + b;
  print(a);

  print();
  c = coca(100., a, a, 1.);
  print(c);

  a = a + b;
  print(a);

  print();
  print(colon(1, 5));

  print(colon(1.1, 5.5));
}

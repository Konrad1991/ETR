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

  print(colon(1, 5.5));

  print();
  print(coca(1., 2.));

  print();
  print(subset(a, true));

  VEC<bool> subbbool(4);
  subbbool[0] = true;
  subbbool[1] = true;
  subbbool[2] = false;
  subbbool[3] = true;

  print();
  print(b);
  print();
  print(subset(b, subbbool));
  print();

  VEC<bool> two(2);
  two[0] = true;
  two[1] = false;

  VEC<double> subass(1);
  subass[0] = 1.;
  subassign(a, subass, true) = 4.5;
  print(a);
  print(subset(a, two, true));

}

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

  print();
  print(subset(a, 1, true));
  print();
  print(subset(a, 2, true));

  print();
  print(subset(a, true, false));
  print(subset(a, false, true));
  print(subset(a, false, false));
  print(subset(a, true, true));

  print();
  print(subset(a, true, 1));
  print();
  print(subset(a, true, 2));
  print();

  a[0] = 1.;
  a[1] = 2.;
  a[2] = 3.;
  a[3] = 4.;
  print(a);
  print(subset(a, true, two));
  print();
  print(subset(a, two, true));
  print();
  two[0] = false;
  two[1] = true;
  print(a);
  print(subset(a, true, two));
  print();
  print(subset(a, two, true));
  print();
  print();
  print();
  print(a);
  print();
  print(subset(a, two, 1));
  print(subset(a, two, 2));
  print();
  print();
  print();
  print(a);
  c = coca(1., 2.);
  print(subset(a, c, 1));
  print(subset(a, c, 2));
  print(subset(a, coca(1., 2.), 1));
  print();
  print();
  print();




}

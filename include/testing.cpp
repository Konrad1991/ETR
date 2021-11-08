#include "etr.hpp"


int main() {

  sexp a, b, c, d, e;

  a = matrix(2.3, 2, 2);
  print(a);
  print();
  b = vector(4., 4);
  a = a + b;
  print(a);


  print(dim(a));

  print(length(b));
}

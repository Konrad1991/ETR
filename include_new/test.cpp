#include "etr.hpp"

using namespace etr;

int main() {

  sexp a = coca(1, 2, 3, 4);

  sexp b = vector(5, 8);

  sexp c = coca(1, 2);
  c(1) = a(1) + b(1);

  print(c);

  c(1) = c(1) + c(1);

  print(c);

  a(1) = c(1) + c(1);
  print();
  print(a);
}

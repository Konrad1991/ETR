#include "etr.hpp"

using namespace etr;


int main() {

  sexp a;

  sexp b = coca(1, 2, 3);

  a = b + b * b - 2;

  for_(a, [&](auto i) { print(i);});
}

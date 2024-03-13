#include "../include/etr.hpp"
using namespace etr;

int main() {
  sexp v1 = coca(1, 2, 3);
  sexp v2;
  v1 = sinus(v1);
  print(v1);
}

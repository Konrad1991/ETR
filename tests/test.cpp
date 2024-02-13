#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;

int main() {
  sexp a = coca(1, 2, 3);
  print(a);
  
  sexp b = matrix(colon(1, 16), 4, 4);
  print(b);

  print(b(1));
 
  b(3) = 4.5;

  print(b);

  print();
  b(a, 4) = 3.14;
  print(b);
}

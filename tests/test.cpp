#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {

  sexp a = vector(1.9);
  print(a);
  printType(vector(2));
  subset(vector(3), 3);
}


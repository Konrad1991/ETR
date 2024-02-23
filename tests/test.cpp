#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {
  sexp a = vector(1.9);
  subset(vector(3), 3);
  Vec<double> v = vector(10);
  print(v);
  
}


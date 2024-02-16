#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {
  Vec<double> a = coca(1, 2.2, 3);
  Vec<int> b = coca(1, 2.2, 3);
  print(a);
  print(b);
  
  Vec<double> c = a / b;
  Vec<int> d = a / b;
  auto e = a / b;

  print(c);
  print(d);

  printAST(e);
}

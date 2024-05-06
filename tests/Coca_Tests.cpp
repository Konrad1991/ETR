#define STANDALONE_ETR

#include "../include/etr.hpp"
using namespace etr;

int main() {
  Vec<double> a = colon(5, 3);
  auto v1 = coca(1.2, 3.4, 5.6);
  auto v2 = coca(1, 2, 3, 4);
  auto v3 = coca(a, true, a, 100);
  auto v4 = coca(true, false, true);

  printTAST<decltype(v1)>();
  printTAST<decltype(v2)>();
  printTAST<decltype(v3)>();
  printTAST<decltype(v4)>();
}

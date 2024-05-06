#define STANDALONE_ETR

#include "../include/etr.hpp"
using namespace etr;
// TODO: implement tests
int main() {
  Vec<double> a = colon(5, 3);
  auto v1 = coca(1.2, 3.4, 5.6);
  auto v2 = coca(1, 2, 3, 4);
  auto v3 = coca(a, true, a, 100);
  auto v4 = coca(true, false, true);

  print(v1);
  printTAST<decltype(v1)>();
  print(v2);
  printTAST<decltype(v2)>();
  print(v3);
  printTAST<decltype(v3)>();
  print(v4);
  printTAST<decltype(v4)>();
}

#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

int main(int argc, char *argv[]) {

  auto res1 = matrix(1, 3, 3);
  print(res1);
  auto res2 = matrix(coca(1, 2, 3, 4.2), 2, 2);
  print(res2);

  auto sub = subset(res1, 1);
  printTAST<decltype(subset(res1, res1))>();
  print(res1(3));
  print(subset(res1, 3));
  /*
    matrix(coca(1), 1, 1);
    matrix(coca(1) + 1, 1, 1);

    Vec<double> v = coca(1, 2, 3);
    matrix(v, 2, 3);
    matrix(v * v, 2, 3);
  */
  return 0;
}

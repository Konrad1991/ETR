#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

int main(int argc, char *argv[]) {
  Vec<double> v = coca(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  print(subset(v / v, coca(1, 2, 3) + 1));
  return 0;
}

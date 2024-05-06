#define STANDALONE_ETR

#include "../include/etr.hpp"
using namespace etr;

int main(int argc, char *argv[]) {
  Vec<double> v = vector(3);
  v[0] = NA;
  v[1] = Inf;
  print(v);
  isNA(v);
  print(isNA(v));
  print(isInf(v));
  print(isNA(NA));
  return 0;
}

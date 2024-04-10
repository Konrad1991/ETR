
#define STANDALONE_ETR
#include "../include/etr.hpp"

using namespace etr;

int main(int argc, char *argv[]) {
  Vec<double> v1 = rep(1, 3);
  print(v1);
  /*
  Vec<double> v2 = rep(v1, 3);
  print(v2);
  Vec<double> v3 = rep(v1 + v1, 4);
  print(v3);
  Vec<double> v4 = rep(v1 + 3.0, 4);
  print(v4);
  */
}

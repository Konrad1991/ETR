#define STANDALONE_ETR

#include "../include/etr.hpp"
using namespace etr;

int main(int argc, char *argv[]) {
  Vec<double> v = vector(3);
  etr::print(v);
  return 0;
}

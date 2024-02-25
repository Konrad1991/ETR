#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {
  Vec<double> a = coca(1, 2, 3);
  Vec<int> b = coca(1, 2, 3);
  print(a);
  print(b);
  print(a + 0.0);
  print(b + 0.0);
}


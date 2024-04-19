#include <cstddef>
#include <iterator>
#define STANDALONE_ETR
#include <iostream>

#include "../include/etr.hpp"
using namespace etr;

int main(int argc, char *argv[]) {
  auto f = [&](const Vec<double> &v, std::size_t i) {
    Vec<double> m1 = matrix(v, i);
    print(m1);
    std::cout << std::endl;
  };

  f(coca(1, 2, 3, 4), 4);
  f(coca(1, 2, 3), 4);
  f(coca(1, 2, 3), 6);
  f(coca(1, 2, 3, 4, 5, 6, 7, 8), 4);
  f(coca(1, 2, 3, 4, 5, 6, 7, 8), 5);

  return 0;
}

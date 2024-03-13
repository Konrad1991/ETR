#include "../include/etr.hpp"
using namespace etr;

int main() {
  auto v = vector(10);
  printTAST<decltype(v)>();
}

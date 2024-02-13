#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;


int main() {
  sexp a = coca(1, 2, 3);
  print(a);
}

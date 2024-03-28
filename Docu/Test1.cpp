#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

int main() {
  Vec<double, Buffer<double> > v1;
  Vec<double, Buffer<double> > v2;

  AllVars<2, 0, 0> av(0);
  av.initBuffer(&v1, &v2);
  Vec<double, VarPointer<decltype(av), 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1>, VariableTypeTrait> vp2(av);

  v1 = coca(1, 2, 3, 4); // [1, 2, 3, 4]
  v2 = colon(2, 5); // [2, 3, 4, 5]

  eval<decltype(vp1 * vp2)>(av);
}


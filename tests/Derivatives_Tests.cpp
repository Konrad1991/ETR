#include <utility>
#define STANDALONE_ETR

// -O2 speed up!

#include "../include/etr.hpp"
using namespace etr;

namespace CN {
template <typename T> inline auto constantNr0(T &av) {
  av.varConstants[0] = coca(1, 2, 3);
  return Vec<double, VarPointer<decltype(av), 0, -1>, ConstantTypeTrait>(av);
}
template <typename T> inline auto constantNr1(T &av) {
  av.varConstants[1] = coca(4, 5, 6);
  return Vec<double, VarPointer<decltype(av), 1, -1>, ConstantTypeTrait>(av);
}
} // namespace CN

/*
TODO:
Initiliase constants with only numbers
Initiliase constants which require variables
Assign constants to variables
Use constants in expressions
*/

int main() {
  etr::AllVars<2, 0, 0, 2> av(1, 0);
  // TODO: approach does not work if variables are used to
  // calculate something
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

  assign<decltype(CN::constantNr0(av))>(av, vp1, CN::constantNr0(av));
  assign<decltype(CN::constantNr1(av))>(av, vp2, CN::constantNr1(av));

  assign<decltype(vp2 * vp1 * vp2)>(av, vp2);
  // f = b^2*a; df/db = a'*b + b'*a = b'*a = 2*b*a = 8, 20, 36
  for (size_t i = 0; i < vp2.d.getSize(av); i++) {
    std::cout << vp2.d.getDeriv(av, i) << std::endl;
  }
  print(av.varBuffer[1]); // 16, 50, 108

  assign<decltype(vp1 + vp2)>(av, vp2);
  // f = a + b; df/db = b' = 8, 20, 36
  for (size_t i = 0; i < vp2.d.getSize(av); i++) {
    std::cout << vp2.d.getDeriv(av, i) << std::endl;
  }
  print(av.varBuffer[1]); // 17, 52, 111
}

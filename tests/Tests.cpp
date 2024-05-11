#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

template <typename T> void printVarPointer(T &v) {
  std::cout << v.d.I << std::endl;
  std::cout << v.d.TIdx << std::endl;
  std::cout << v.d.AllVarsRef.varBuffer[0] << std::endl;
}

int main(int argc, char *argv[]) {
  etr::AllVars<2, 0, 0, 4> av(0, 0); // deriv with respect tp variable 1 = vp1
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);
  vp1 << coca<0>(av, 1, 2, 3);
  vp2 << coca<1>(av, 4, 5, 6) * vp1;

  print(vp1, av);
  print(vp2, av);

  auto deriv1 = get_deriv<2>(vp1);
  print(deriv1, av);

  auto deriv2 = get_deriv<3>(vp2);
  print(deriv2, av);

  return 0;
}

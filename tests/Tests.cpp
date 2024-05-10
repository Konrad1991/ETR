#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

template <typename T> void printVarPointer(T &v) {
  std::cout << v.d.I << std::endl;
  std::cout << v.d.TIdx << std::endl;
  std::cout << v.d.AllVarsRef.varBuffer[0] << std::endl;
}

int main(int argc, char *argv[]) {
  etr::AllVars<2, 0, 0, 2> av(0, 0);
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);
  vp1 << coca<0>(av, 1, 2, 3);
  vp2 << coca<1>(av, 4, 5, 6) * vp1;

  print(vp1, av);
  print(vp2, av);
  for (size_t i = 0; i < vp2.d.getSize(av); i++) {
    std::cout << vp2.d.getDeriv(av, i) << std::endl;
  }
  for (size_t i = 0; i < vp1.d.getSize(av); i++) {
    std::cout << vp1.d.getDeriv(av, i) << std::endl;
  }

  return 0;
}

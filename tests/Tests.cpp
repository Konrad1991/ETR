#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

int main(int argc, char *argv[]) {
  etr::AllVars<2, 0, 0, 2> av(0, 0);
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);
  vp1 << coca<0>(av, 1, 2, 3);
  vp2 << coca<1>(av, 4, 5, 6) * vp1;

  print(vp1, av);
  print(vp2, av);

  Vec<double> deriv_vp1 = get_derivs(vp1);
  print(deriv_vp1);
  Vec<double> deriv_vp2 = get_derivs(vp2);
  print(deriv_vp2);

  return 0;
}

#define STANDALONE_ETR

// -O2 speed up!

#include "../include/etr.hpp"
using namespace etr;

int main() {
  // TODO: it is not necesary to declare first a,b and than vp1 and vp2
  // One could directly work with Vec, double, VarPointer...>
  // Change AllVars so that it does not use references but it is more like a
  // general storage of all vairables Thereby, only one additional variable is
  // created which is pretty cool
  etr::AllVars<2, 0, 0> av(1, 0);
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

  // Aim: assign<decltype(etr::coca(1, 2, 3))>(av, vp1);
  av.varBuffer[0] = coca(1, 2, 3);
  av.varBuffer[1] = coca(4, 5, 6);

  // assign<decltype(vp2 * vp2)>(av, vp2); // f = b^2; df/db = 2*b = 8, 10, 12
  // for(size_t i = 0; i < vp2.d.getSize(av); i++) {
  //   std::cout << vp2.d.getDeriv(av, i) << std::endl;
  // }
  // print(av.varBuffer[1]); // 16, 25, 36

  // assign<decltype(vp1 + vp2)>(av, vp2); // f = a + b; df/db = 1 = 1, 1, 1
  // for(size_t i = 0; i < vp2.d.getSize(av); i++) {
  //   std::cout << vp2.d.getDeriv(av, i) << std::endl;
  // }
  // print(av.varBuffer[1]);  // 5, 7, 9

  // assign<decltype(vp1 + vp2 * vp1)>(av, vp2); // f = a + b*a; df/db = a'*b +
  // b'*a = b'*a = 1*a = 1, 2, 3 for(size_t i = 0; i < vp2.d.getSize(av); i++) {
  //   std::cout << vp2.d.getDeriv(av, i) << std::endl;
  // }
  // print(av.varBuffer[1]);  // 5, 12, 21

  // assign<decltype(vp1 + vp2*vp1*vp2)>(av, vp2); // f = a + b^2*a; df/db =
  // a'*b + b'*a = b'*a = 2*b*a = 8, 20, 36 for(size_t i = 0; i <
  // vp2.d.getSize(av); i++) {
  //   std::cout << vp2.d.getDeriv(av, i) << std::endl;
  // }
  // print(av.varBuffer[1]);  // 17, 52, 111

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

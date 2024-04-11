#define STANDALONE_ETR

// -O2 speed up!

#include "../include/etr.hpp"
using namespace etr;

namespace ConstantsEtr {
const double pi = 3.14;
}


int main() {
  Vec<double> a, b;
  etr::AllVars<2, 0, 0> av(1, 0);
  av.initBuffer(&a, &b);
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

  a = etr::coca(1, 2, 3);
  b = etr::coca(4, 5, 6);

  //assign<decltype(vp2 * vp2)>(av, vp2); // f = b^2; df/db = 2*b = 8, 10, 12
  //for(size_t i = 0; i < vp2.d.getSize(av); i++) {
  //  std::cout << vp2.d.getDeriv(av, i) << std::endl;
  //}
  //print(b); // 16, 25, 36

  //assign<decltype(vp1 + vp2)>(av, vp2); // f = a + b; df/db = 1 = 1, 1, 1
  //for(size_t i = 0; i < vp2.d.getSize(av); i++) {
  //  std::cout << vp2.d.getDeriv(av, i) << std::endl;
  //}
  //print(b); // 5, 7, 9

  //assign<decltype(vp1 + vp2 * vp1)>(av, vp2); // f = a + b*a; df/db = a'*b + b'*a = b'*a = 1*a = 1, 2, 3
  //for(size_t i = 0; i < vp2.d.getSize(av); i++) {
  //  std::cout << vp2.d.getDeriv(av, i) << std::endl;
  //}
  //print(b); // 5, 12, 21

  assign<decltype(vp1 + vp2*vp1*vp2)>(av, vp2); // f = a + b^2*a; df/db = a'*b + b'*a = b'*a = 2*b*a = 8, 20, 36
  for(size_t i = 0; i < vp2.d.getSize(av); i++) {
    std::cout << vp2.d.getDeriv(av, i) << std::endl;
  }
  print(b); // 17, 52, 111
}

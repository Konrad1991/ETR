#include <ios>
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
How to handle function arguments?
How to handle constants such as subset
*/

int main() {
  // NOTE: Derivatives Test Nr.1
  {
    etr::AllVars<2, 0, 0, 2> av(1, 0);
    Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
    Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

    assign<decltype(CN::constantNr0(av))>(av, vp1, CN::constantNr0(av));
    assign<decltype(CN::constantNr1(av))>(av, vp2, CN::constantNr1(av));

    // f = vp2 * vp1 * c(1, 2, 3) = 4, 20, 54; df/dvp2 = vp1 * c(1, 2, 3) = 1,
    // 4,
    // 9
    assign<decltype(vp2 * vp1 * CN::constantNr0(av))>(av, vp2,
                                                      CN::constantNr0(av));
    for (size_t i = 0; i < vp2.d.getSize(av); i++) {
      std::cout << vp2.d.getDeriv(av, i) << std::endl;
    }
    print(av.varBuffer[1]);

    /*
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
    */
  }
  // NOTE: Derivatives Test Nr.2
  {
    std::cout << "block Nr. 2" << std::endl;
    etr::AllVars<2, 0, 0, 4> av(0, 0); // deriv with respect tp variable 1 = vp1
    Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
    Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

    vp1 << coca<0>(av, 1, 2, 3); // vp1 = c(1, 2, 3); dexpr1/dvp1 = 1, 1, 1
    vp2 << coca<1>(av, 4, 5, 6) *
               vp1; // vp2 = c(4, 5, 6)*vp1 = 4, 10, 18; dexpr2/dvp1 = 4, 5, 6

    vp1 << vp2 + vp2; // vp1 = 8, 20, 36; dexpr3/dvp1 = 8, 10, 12
    print(vp1, av);
    print(vp2, av);

    Vec<double> deriv_vp1 = get_derivs(vp1);
    print(deriv_vp1);
    Vec<double> deriv_vp2 = get_derivs(vp2);
    print(deriv_vp2);

    vp1 = 100; // TODO: the scalar value 100 has to be encapsulated into a
               // specific class
    print(vp1, av);
  }
}

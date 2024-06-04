#define STANDALONE_ETR

// -O2 speed up!

#include "../include/etr.hpp"
using namespace etr;

int main() {
  // NOTE: block Nr.1
  {
    std::cout << "general tests" << std::endl;
    etr::AllVars<2, 0, 0, 2> av(0, 0); // deriv with respect tp variable 1 = vp1
    Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
    Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);

    vp1 = coca<0>(av, 1, 2, 3); // vp1 = c(1, 2, 3); dexpr1/dvp1 = 1, 1, 1
    vp2 = coca<1>(av, 4, 5, 6) *
          vp1; // vp2 = c(4, 5, 6)*vp1 = 4, 10, 18; dexpr2/dvp1 = 4, 5, 6

    vp1 = vp2 + vp2; // vp1 = 8, 20, 36; dexpr3/dvp1 = 8, 10, 12
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
  // NOTE: test minus
  {
    std::cout << "test minus" << std::endl;
    AllVars<2, 0, 0, 3> av(0, 0);
    Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> a(av);
    Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> b(av);

    std::cout << "\n"
              << "a = c(1, 2, 3, 4)"
              << "\n"
              << "b = c(4, 5, 6, 7)" << std::endl;
    a = coca<0>(av, 1, 2, 3, 4);
    b = coca<1>(av, 4, 5, 6, 7);
    print(a, av);
    print(b, av);
    print(get_derivs(a));
    print(get_derivs(b));

    std::cout << "\n"
              << "a = a - b"
              << "\n"
              << "b = a * a" << std::endl;
    a = a - b;
    b = a * a;
    print(a, av);
    print(b, av);
    print(get_derivs(a));
    print(get_derivs(b));

    std::cout << "\n"
              << "a = b" << std::endl;
    a = b;
    print(a, av);
    print(b, av);
    print(get_derivs(a));
    print(get_derivs(b));

    std::cout << "\n"
              << "a = a / b" << std::endl;
    a = a / scalarDeriv<3>(av, 3.14);
    print(a, av);
    print(b, av);
    print(get_derivs(a));
    print(get_derivs(b));
  }
}

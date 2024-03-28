#define STANDALONE_ETR

#include "../include/etr.hpp"
using namespace etr;

int main() {
    Vec<double> a, b;
    double c = 3.14;
    etr::AllVars<2, 0, 0> av(1);
    av.initBuffer(&a, &b);
    Vec<double, VarPointer<decltype(av), 0>, VariableTypeTrait> vp1(av);
    Vec<double, VarPointer<decltype(av), 1>, VariableTypeTrait> vp2(av);

    a = etr::coca(1, 2, 3);
    b = etr::coca(4, 5, 6);
    
    eval<decltype(vp2 * vp2)>(av); // f = b^2; df/db = 2*b = 8, 10, 12
    eval<decltype(vp1 + vp2)>(av); // f = a + b; df/db = 1 = 1, 1, 1
    eval<decltype(vp1 + vp2*vp1)>(av); // f = a + b*a; df/db = a'*b + b'*a = b'*a = 1*a = 1, 2, 3
    eval<decltype(vp1 + vp2*vp1*vp2)>(av); // f = a + b^2*a; df/db = a'*b + b'*a = b'*a = 2*b*a = 8, 20, 36

    // f = 3.14*b
    //eval<decltype(vp1 * b)>(av);

    // how to handle: arithmetic vars, r vectors and constants?
}

/*
Plan:
remove defineMatrix function
calc defineMatrix one time if it is needed in the BinaryOperation itself!
*/


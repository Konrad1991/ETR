#define STANDALONE_ETR

// -O2 speed up!

#include "../include/etr.hpp"
using namespace etr;

namespace ConstantsEtr {
const double pi = 3.14;
}

int main() {
  Vec<double> a, b;
  etr::AllVars<2, 0, 0> av(1);
  av.initBuffer(&a, &b);
  Vec<double, VarPointer<decltype(av), 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1>, VariableTypeTrait> vp2(av);

  a = etr::coca(1, 2, 3);
  b = etr::coca(4, 5, 6);
  // eval<decltype(vp2 * vp2)>(av); // f = b^2; df/db = 2*b = 8, 10, 12
  // eval<decltype(vp1 + vp2)>(av); // f = a + b; df/db = 1 = 1, 1, 1
  eval<decltype(vp1 + vp2 * vp1)>(
      av); // f = a + b*a; df/db = a'*b + b'*a = b'*a = 1*a = 1, 2, 3
  // eval<decltype(vp1 + vp2*vp1*vp2)>(av); // f = a + b^2*a; df/db = a'*b +
  // b'*a = b'*a = 2*b*a = 8, 20, 36

  // f = 3.14*b
  // eval<decltype(vp1 * b)>(av);
}

/*
how to handle: arithmetic vars, r vectors and constants?

arithmetic variables have to be stored in

template<typename T>
struct ArithmeticVar {
    T val;
    T Deriv = 0;
    ...
}

r vectors have to be handled in the same way as normal vectors.
But they are not of type Vec<VarPointer> but rather Vec<Buffer>.

- define own helper function. For example instead of vector(size), vector(size,
AllVars&)
    * Than the new vector function defines a own variable in a std::vector where
it can points to

- Can i define several AllVars instances independently. Crucial for parallel
functions

*/

/*
complicated type reflecting derivative
VariableType
VarPointer
AllVars array


- 3 different arrays holding VecBuffer, VecBorrow, VecBorrowSEXP
- VarPointer should hold an index and a type. A seperate index for each type!
- Thereby the correct array could be chosen in AllVars at compile time
- Furthermore I could construct constants with an Index and a type
    * probably it is necessary that these values are created at compile time
    * Than it is also required that the index and the type is passed to the
instance of AllVars
*/

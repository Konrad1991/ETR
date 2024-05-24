#include <stdexcept>
#include <type_traits>
#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

void test_arithmetic() {
  // NOTE: test unary minus trigo etc.
  {
    std::string s = "ArithmeticTests: ";
    Vec<double> a = coca(1, 2, 3);
    Vec<double> b = coca(4, 5, 6);
    Vec<double> c;
    print(-a);
    print(sinus(a));    // 0.8414710 0.9092974 0.1411200
    print(asinus(a));   // 1.570796      NaN      NaN
    print(sinush(a));   //  1.175201  3.626860 10.017875
    print(cosinus(a));  // 0.5403023 -0.4161468 -0.9899925
    print(acosinus(a)); // 0, NaN  NaN
    print(cosinush(a)); //  1.543081  3.762196 10.067662
    print(tangens(a));  //  1.5574077 -2.1850399 -0.1425465
    print(atangens(a)); //  0.7853982 1.1071487 1.2490458
    print(tangensh(a)); // 0.7615942 0.9640276 0.9950548
    print(ln(a));       // 0.0000000 0.6931472 1.0986123
    print(sqroot(a));   // 1.000000 1.414214 1.732051
    print(exp(a));      //   2.718282  7.389056 20.085537
  }
}

int main(int argc, char *argv[]) {
  test_arithmetic();
  return 0;
}

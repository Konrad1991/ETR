#include "RNG.hpp"
#include <iomanip>    

// https://gist.github.com/mclements/3668c89d73e4504f323ca57a71c65602

int main() {
  std::cout << std::fixed << std::setprecision(6);
  RNG_R::MersenneTwister ms(1234);
  for(int i = 1; i < 2; i++) {
    std::cout << ms() << ", \t";
    if(i % 10 == 0) std::cout << std::endl;
  }
}




/*
#define MATHLIB_STANDALONE 1
#include <Rmath.h>
#include <stdio.h>
typedef enum {
    BUGGY_KINDERMAN_RAMAGE,
    AHRENS_DIETER,
    BOX_MULLER,
    USER_NORM,
    INVERSION,
    KINDERMAN_RAMAGE
} N01type;
int main(int argc, char** argv) {
    qnorm(0.7, 0.0, 1.0, 0, 0);
    printf("*** loaded '%s'\n", argv[0]);
    set_seed(123, 456);
    N01_kind = AHRENS_DIETER;
    printf("one normal %f\n", norm_rand());
    set_seed(123, 456);
    N01_kind = BOX_MULLER;
    printf("normal via BM %f\n", norm_rand());
}
*/

/*
#include <stdio.h>
#include "Rmath.h"

int main() {
  set_seed(1234, 5678);
  double res = runifOwn(0.0, 1.0);

  printf("runif %lf\n", res);
  return 0;
}
*/

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

int
main(int argc, char** argv)
{
/* something to force the library to be included */
    qnorm(0.7, 0.0, 1.0, 0, 0);
    printf("*** loaded '%s'\n", argv[0]);
    set_seed(123, 456);
    N01_kind = AHRENS_DIETER;
    printf("one normal %f\n", norm_rand());
    set_seed(123, 456);
    N01_kind = BOX_MULLER;
    printf("normal via BM %f\n", norm_rand());
    
    return 0;
}

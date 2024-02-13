#include <stdio.h>
#include "Rmath.h"

int main() {
  double shape1, shape2, prob;

  printf("Enter first shape parameter: ");
  scanf("%lf",&shape1);

  printf("Enter second shape parameter: ");
  scanf("%lf",&shape2);

  printf("Enter probability level: ");
  scanf("%lf",&prob);

  printf("Critical value is %lf\n",qbeta(prob,shape1,shape2,1,0));

  printf("R_pow %lf\n", R_pow(2.0, 2.0));
  return 0;
}
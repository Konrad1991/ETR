#include "testheader.hpp"

void trigono() {
  print("exp");
  sexp a = vector(5, 2);
  print(a^3);
  print(exp(2, 3));
  print(exp(a, 3));

  print("sinus");
  print(sinus(0));
  a = vector(3.14, 2);
  print(sinus(a));

  print("sinush");
  print(sinush(0));
  a = vector(2, 2);
  print(sinush(a));

  print("asinus");
  print(asinus(0));
  a = vector(1, 2);
  print(asinus(a));

  print("cosinus");
  print(cosinus(0));
  print(cosinus(coca(3.14, 3.14)));

  print("cosinush");
  print(cosinush(0));
  print(cosinush(coca(-2, 2)));

  print("acosinus");
  print(acosinus(0));
  print(acosinus(coca(1, -1)));

  print("tangens");
  print(tangens(0));
  print(tangens(a));

  print("tangensh");
  print(tangensh(0));
  print(tangensh(a));

  print("atangens");
  print(atangens(0));
  print(atangens(a));

  print("log");
  print(ln(1));
  print(ln(coca(0, 1, 2)) );


}

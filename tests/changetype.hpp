#include "testheader.hpp"

void testchange() {
  // assignment of objects
  sexp s;
  s = 1;
  print(s);

  sexp v;
  v = colon(1, 4);
  print(v);

  sexp m;
  m = matrix(3, 5, 2);
  print(m);

  print();
  sexp sc = 1.5;
  print(sc);


  sexp v2 = vector(1, 4);
  print(v2);

  sexp m2 = matrix(v2, 2, 2);
  print(m2);
  print();

  s = v2;
  print(s);
  sc = m2;
  print(sc);
  print();
  v = 1;
  print(v);
  v2 = m2;
  print(v2);
  print();

  m = 2;
  print(m);
  m2 = vector(1, 5);
  print(m2);

  // assignment of result of operation
  sexp scal1, scal2;
  scal1 = 1;
  scal2 = scal1 + 3;
  print();
  print(scal2);
  print();

  sexp vc1, vc2;
  vc1 = vector(3, 5);
  vc2 = vc1 + 3;
  print(vc2);
  print();

  sexp mt1, mt2;
  mt1 = matrix(3, 2, 5);
  mt2 = mt1 + 3;
  print(mt2);
  print();



  /*
  sexp scal3;
  scal3 = 1;
  sexp scal4 = scal3 + 1;
  print(scal4);
  print();

  sexp vc3;
  vc3 = vector(3, 5);
  sexp vc4 = vc3 + 3;
  print(vc4);

  sexp mt3;
  mt3 = matrix(3, 5, 5);
  sexp mt4 = mt3 + 3;
  print(mt4);
  */


  sexp scal3;
  scal3 = 1;
  scal3 = colon(1, 5) + vector(3, 5);
  print(scal3);
  print();

  sexp scal4;
  scal4 = 1;
  scal4 = matrix(3, 5, 5) + matrix(4, 5, 5);
  print(scal4);
  print();

  sexp vc3 = vector(3, 5);
  sexp temp;
  temp = 1;
  vc3 = temp + 3.5;
  print(vc3);
  print();
  sexp vc4 = vector(3, 5);
  vc4 = matrix(3, 5, 5) / 2;
  print(vc4);
  print();

  sexp mt3 = matrix(3, 2, 5);
  mt3 = temp*5;
  print(mt3);
  print();
  sexp mt4 = matrix(3, 2, 5);
  mt4 = colon(1, 4) * colon(5, 8);
  print(mt4);

}

#include "etr.hpp"


void test_vec() {
  vec a = colon(1, 3);
  vec b = colon(2, 4);

  vec c;

  c = a + b;

  print(c);
  print();
  vec d = c(1, 2);

  print(d);
  print();

  vec e = colon(1, 10);

  self(e, 2, 3) = 1.0;
  self(e, 4, 6) = b + a;
  self(e, 1, 3) = b;
  self(e, 1, 3) = b + 100.;
  e(1) = 1000.;

  print(e);
}


int main() {


  mat m1(4,4,2.0);
  mat m2(4, 4, 3.);

  mat m3;

  m3 = m1 + m2;

  print(m3);

  m3 = m3 + 100.;

  print(m3);


  m3(1, 1) = m3(1) -100.;
  print();
  print(m3);
  print();
  vec v(16, 200.);
  m3 = 100000. + m3 + v -3.14 + v/2.;
  print(m3);







}

#include "testheader.hpp"

void testplus() {


  sexp s, v, m;
  s = 1;
  s = s + 3;

  v = s + vector(4, 4);
  print(v);

  v = vector(4, 4);
  print(v);
  print();
  v = v + 30;
  print(v);
  print();

  m = s + matrix(2, 2, 2);
  m = matrix(2, 2, 2);
  m = m + 40;
  print(m);
  print();

  m = v + m;
  print(m);
  print();


  m = m + v;
  print(m);
  print();
}

void testminus() {

  sexp s, v, m;
  s = 1;
  s = s - 3;
  print(s);
  print();

  //v = s - vector(4, 4);
  v = vector(4, 4);
  print(v);
  print();
  v = v - 30;
  print(v);
  print();

  //m = s + matrix(2, 2, 2);
  m = matrix(2, 2, 2);
  m = m - 40;
  print(m);
  print();

  m = v - m;
  print(m);
  print();


  m = m - v;
  print(m);
  print();

}


void testtimes() {
  sexp s, v, m;
  s = 1;
  s = s * 3;
  print(s);
  print();

  //v = s + vector(4, 4);
  v = vector(4, 4);
  print(v);
  print();
  v = v * 30;
  print(v);
  print();

  //m = s + matrix(2, 2, 2);
  m = matrix(2, 2, 2);
  m = m * 40;
  print(m);
  print();

  m = v * m;
  print(m);
  print();


  m = m * v;
  print(m);
  print();

}


void testdiv() {

  sexp s, v, m;
  s = 1;
  s = s / 3;
  print(s);
  print();

  //v = s + vector(4, 4);
  v = vector(4, 4);
  print(v);
  print();
  v = v / 30;
  print(v);
  print();

  //m = s + matrix(2, 2, 2);
  m = matrix(2, 2, 2);
  m = m / 40;
  print(m);
  print();

  m = v / m;
  print(m);
  print();


  m = m / v;
  print(m);
  print();
  
}

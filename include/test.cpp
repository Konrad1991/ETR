#include "etr.hpp"



int main() {

  sexp a = coca(1, 2, 3);
  sexp b = coca(1, 2, 4);


  sexp c = a == b;
  print(c);
  print("==");
  print(a == b);
  print(">=");
  print(a >= b);
  print("<=");
  print(a <= b);
  print("<");
  print(a < b);
  print(">");
  print(a > b);
  print("!=");
  print(a != b);

  sexp d = coca(1, 2, 3, 4);
  sexp e = coca(1, 4);


  print("==");
  print(d == e);
  print(">=");
  print(e >= d);


  if(a == b) {
    print(a==b);
    print(1);
    print(4.5);
  }

  print(d);
  print(coca(1,2,d));

}

#include "etr.hpp"


int main() {
  sexp v = colon(1, 6);
  print(v);
  print();

  print("bool");
  print("true: ");
  print(subset(v, true));
  print("false: ");
  print(subset(v, false));
  print();

  print("integer or double");
  print(subset(v, 1));
  print(subset(v, 5.5));
  print();

  print("nothing (nullptr):");
  print(subset(v, nullptr));
  print();

  sexp positions = coca(1, 6, 2, 3);
  print("other vec:");
  print(subset(v, positions));
  print();

  VEC<bool> vec_bool(4); // output e.g. of comparison of two vectors not implemented yet
  vec_bool[0] = true;
  vec_bool[1] = false;
  vec_bool[2] = true;
  vec_bool[3] = true;
  print("bool vec:");
  print(subset(v, vec_bool));
  print();

}

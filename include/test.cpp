#include "etr.hpp"


int main() {
  sexp m = matrix(colon(1, 15), 5, 3);
  print(m);
  print();

  print("bool");
  print("true, true: ");
  print(subset(m, true, true));
  print("false, true: ");
  print(subset(m, false, true));
  print();

  print("integer or double");
  print(subset(m, 1, 1));
  print(subset(m, 5.5, 2));
  print();

  print("nothing (nullptr):");
  print(subset(m, nullptr, nullptr));
  print();

  sexp positions1 = coca(1, 5, 2, 3);
  sexp positions2 = coca(1, 3, 2, 3);
  print("other vecs:");
  print(subset(m, positions1, positions2));
  print();

  VEC<bool> vec_bool1(3); // output e.g. of comparison of two mectors not implemented yet
  vec_bool1[0] = true;
  vec_bool1[1] = false;
  vec_bool1[2] = true;

  VEC<bool> vec_bool2(4); // output e.g. of comparison of two mectors not implemented yet
  vec_bool2[0] = true;
  vec_bool2[1] = true;
  vec_bool2[2] = false;
  vec_bool2[3] = true;
  print("bool vec:");
  print(subset(m, vec_bool1, vec_bool2));
  print();

}

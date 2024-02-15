#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {
  sexp a = coca(1, 2.2, 3);
  //print(a);
  
  sexp b = matrix(colon(1, 16), 4, 4);
  //print(b);

  //print(b(1));
 
  b(3) = 4.5;

  //print(b);

  print();
  b(a, 4) = 3.14;
  //print(b);

  Vec<int> test = coca(1, 2.2, 4);
  //print(test);
  //printAST(test);

  sexp res = a / test;
  print(res);
  //printAST(res);

  Vec<int> res2 = a / test;
  print(res2);
  //printAST(res2);

  std::cout << std::setprecision(20);
  Vec<long double> a1 = 3.14159265358979323846;
  Vec<double> a2 = 3.14159265358979323846;

  long double d1 = 3.0;
  double d2 = 3.0;

  long double resa1 = a1 / d1;
  double resa2 = a2 / d2;

  std::cout << resa1 << " " << resa2 << std::endl;

}

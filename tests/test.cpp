#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {
  sexp a = coca(1, 2.2, 3);
  print(a);
  
  sexp b = matrix(colon(1, 16), 4, 4);
  print(b);

  print(b(1));
 
  b(3) = 4.5;

  print(b);

  print();
  b(a, 4) = 3.14;
  print(b);

  Vec<int> test = coca(1, 2.2, 4);
  print(test);
  printAST(test);

  sexp res = a / test;
  print(res);
  printAST(res);

  Vec<int> res2 = a / test;
  print(res2);
  printAST(res2);

  /*
  std::cout << std::setprecision(20);
  Vec<long double> a1 = 3.14159265358979323846;
  Vec<double> a2 = 3.14159265358979323846;

  long double d1 = 3.0;
  double d2 = 3.0;

  long double resa1 = a1 / d1;
  double resa2 = a2 / d2;

  std::cout << resa1 << " " << resa2 << std::endl;
  */
  size_t size = 3; 
  double* ptr = new double[size];
  
  BorrowPtr v_borrow(ptr, size);
  v_borrow = colon(1, 3);
  print(v_borrow);
  
  ptr[0] = 3.14;
  print(v_borrow);

  std::cout << ptr[0] << " " << ptr[1] << " " << ptr[2] << std::endl;

  delete[] ptr;

  {

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

  auto a_is_b = a == b;
  printAST(a_is_b);
  print(a_is_b);
  if(a(1)) {
    print(a==b);
    print(1);
    print(4.5);
  }

  print(d);
  print(coca(1,2,d));
  }

     sexp v = colon(1, 2);
    print(length(v));

    sexp m = matrix(5, 2);
    print(length(m));
    print(dim(m));

    printType(v);
    printT<sexp>();
    printAST(v + v*2.0);
    printTAST<decltype(v - v*v)>();


  { 
sexp t = colon(1, 8);
sexp p = coca(1, 2, 3, 4, 5, 6, 7, 8);

sexp res = cmr(1, t, p);
print(res);

res = cmr(1.5, t, p);
print(res);

res = cmr(2.5, t, p);
print(res);

res = cmr(4, t, p);
print(res);

res = cmr(5, t, p);
print(res);

res = cmr(5.5, t, p);
print(res);

res = cmr(7.5, t, p);
print(res);

res = cmr(7.99, t, p);
print(res);
print();
res = cmr(8, t, p);
print(res);

print();
res = cmr(9, t, p);
print(res);

print();
res = cmr(-1, t, p);
print(res);
  }
}

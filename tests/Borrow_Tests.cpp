#include <cstddef>
#include <stdexcept>
#include <type_traits>
#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

void test_borrow() {
  // NOTE: test nothing allocated
  {
    std::string s = "BorrowTestsNotAllocated: ";
    Borrow<double> bs;
    try {
      bs[0];
    } catch (std::runtime_error &e) {
      std::string expected = "No memory was allocated";
      ass(e.what() == expected, s + "nothing allocated");
    }
    ass(bs.size() == 0, s + "size");
    ass(bs.capacity == 0, s + "capacity");
    ass(bs.im() == false, s + "im");
    ass(bs.nc() == 0, s + "nc");
    ass(bs.nr() == 0, s + "nr");
    ass(bs.allocated == false, s + "allocated");
  }
  // NOTE: allocating something with a large size so that size and capacity
  // differ
  {
    std::string s = "BorrowTestsAllocated: ";
    int size = 100;
    double *ptr = new double[size];
    Borrow<double> bs(ptr, size);
    ass(bs.size() == size, s + "size");
    ass(bs.capacity == size, s + "capacity");
    bs[bs.size() - 1] = 3.14;
    ass(bs[bs.size() - 1] == 3.14, s + "last element");
    delete[] ptr;
  }
  // NOTE: allocating something with a small size so that size and capacity do
  // not differ
  {
    std::string s = "BorrowTestsAllocated: ";
    int size = 3;
    double *ptr = new double[size];
    Borrow<double> bs(ptr, size);
    ass(bs.size() == size, s + "size");
    ass(bs.capacity == size, s + "capacity");
    bs[bs.size() - 1] = 3.14;
    ass(bs[bs.size() - 1] == 3.14, s + "last element");
    ass(bs.size() == size, s + "size");
    delete[] ptr;
  }
  // NOTE: test resize
  {
    std::string s = "BorrowResizing: ";
    double *ptr = new double[10];
    Borrow<double> v(ptr, 10);
    v.resize(5);
    ass(v.size() == 5, s + "size");
    v[v.sz - 1] = 4.5;
    ass(v[v.sz - 1] == 4.5, s + "last element");

    v.resize(7);
    ass(v.size() == 7, s + "size");
    v[v.sz - 1] = 400.5;
    ass(v[v.sz - 1] == 400.5, s + "last element");

    try {
      v.resize(1000);
    } catch (std::runtime_error &e) {
      std::string expected =
          "Cannot resize Borrow element above size of borrowed object";
      ass(e.what() == expected, s + "resize above size of borrowed object");
    }
    delete[] ptr;
  }

  // NOTE: test init
  {
    std::string s = "BorrowInit: ";
    Borrow<double> v;
    double *ptr = new double[10];
    v.init(ptr, 10);
    ass(v.size() == 10, s + "size");
    v[v.sz - 1] = 4.5;
    ass(v[v.sz - 1] == 4.5, s + "last element");
    delete[] ptr;
  }

  // NOTE: test fill scalar
  {
    std::string s = "BorrowFill: ";
    double *ptr = new double[10];
    Borrow<double> v(ptr, 10);
    v.fill(3.4);
    for (size_t i = 0; i < v.size(); i++) {
      ass(v[i] == 3.4, s + "[" + std::to_string(i) + "]");
    }
    delete[] ptr;
  }
  // NOTE: test fill with Vector
  {
    std::string s = "BorrowFill: ";
    double *ptr = new double[10];
    Borrow<double> v(ptr, 10);
    v.fill(coca(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    for (size_t i = 0; i < v.size(); i++) {
      ass(v[i] == static_cast<double>(i + 1),
          s + "[" + std::to_string(i) + "]");
    }
    delete[] ptr;
  }
  // NOTE: test Borrow with other functions
  {
    // TODO: add more tests
    std::string s = "BorrowWithOtherFcts: ";
    double *ptr = new double[10];
    BorrowPtr bp(ptr, 10);
    Vec<double> res = coca(1, 2, 3, bp);
    ass(res.size() == 13, s + "coca");
    delete[] ptr;
  }
}

int main(int argc, char *argv[]) {
  //test_borrow();
  Vec<double> ret; // TODO: check that a subset is only made using an allocated object
  ret = etr::vector_numeric(etr::i2d(20));
  //printTAST<decltype(subset(ret, 1))>();
  ret(1) = 2; 
  ret(2) = true;
  ret(3) = 3.14;

  // TODO: int works. Implement the same call stack for double and bool
  // TODO: this is a problam. Check that each class: Buffer, Borrow,
  // BorrowSEXP etc. can be assigned with the result of anither class
  print(ret);

  sexp b;
  b = coca(i2d(1), i2d(5));
  auto test = subset(colon(1, 6) + 0, b);
  printTAST<decltype(test)>();
  printTAST<decltype(test.d)>();

  sexp c;
  c = subset(matrix(colon(1, 25), 5, 5), b, b);
  print(c);
  b = subset((colon(i2d(1), i2d(6)) + i2d(0)), b);
  print(b);

   b = subset((colon(i2d(1), i2d(6)) + i2d(1)),b + b);

  return 0;
}

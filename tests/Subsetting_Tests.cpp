#include <stdexcept>
#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

/*
// NOTE: compilation fails as desired
void test_scalar_subsetting() {
  bool b = true;
  int i = 10;
  double d = 3.14;
  subset(b, 1);
  subset(b, 1, 1);
  subset(i, 1);
  subset(i, 1, 1);
  subset(d, 1);
  subset(d, 1, 1);
}
*/

void test_vector_subsetting() {
  Vec<double> v = colon(1, 16);
  // NOTE: boolsubsetting
  {
    ass(v(true).size() == 16, "vec size == 16");
    bool b = true;
    ass(v(b).size() == 16, "vec size == 16");
    try {
      v(false);
    } catch (std::runtime_error &e) {
      std::string expect = "Variable[FALSE] subsetting is not supported. Sorry";
      ass(expect == e.what(), "Variable[FALSE] results in runtime error");
    }
    try {
      b = false;
      v(b);
    } catch (std::runtime_error &e) {
      std::string expect = "Variable[FALSE] subsetting is not supported. Sorry";
      ass(expect == e.what(), "Variable[FALSE] results in runtime error");
    }
  }
  // NOTE: int subsetting
  {
    try {
      v(-1);
    } catch (std::runtime_error &e) {
      std::string expect = "Invalid index argc";
      ass(expect == e.what(), "Invalid index argument");
    }
    ass(v(1).size() == 1, "vec(1).size() == 1");
    ass(v(1)[0] == 1, "vec[1] == 1");
    ass(v(16)[0] == 16, "vec[16] == 16");
    int i = 1;
    ass(v(i).size() == 1, "vec(1).size() == 1");
    ass(v(i)[0] == 1, "vec[1] == 1");
    i = 16;
    ass(v(i)[0] == 16, "vec[16] == 16");
  }
  // NOTE: double subsetting
  {
    try {
      v(-1.0);
    } catch (std::runtime_error &e) {
      std::string expect = "invalid index argument";
      ass(expect == e.what(), "invalid index argument");
    }

    ass(v(1.0).size() == 1, "vec(1).size() == 1");
    ass(v(1.0)[0] == 1, "vec[1] == 1");
    ass(v(16.0)[0] == 16, "vec[16] == 16");
    double d = 1.0;
    ass(v(d).size() == 1, "vec(1).size() == 1");
    ass(v(d)[0] == 1, "vec[1] == 1");
    d = 16;
    ass(v(d)[0] == 16, "vec[16] == 16");

    ass(v(1.1).size() == 1, "vec(1).size() == 1");
    ass(v(1.1)[0] == 1, "vec[1] == 1");
    ass(v(16.1)[0] == 16, "vec[16] == 16");
    d = 1.1;
    ass(v(d).size() == 1, "vec(1).size() == 1");
    ass(v(d)[0] == 1, "vec[1] == 1");
    d = 16;
    ass(v(d)[0] == 16, "vec[16] == 16");
  }
  // NOTE: vector double/int
  {
    int size = 3;
    double *d = new double[size];
    Vec<double, Borrow<double>> b(d, size);
    b = coca(1, 2, 3);
    Vec<double> idx = coca(1, 4, 7);
    v(idx);
    v(coca(1, 2, 3));
    v(v(1));
    v(coca(1, 2, 3) + 1);
    v(idx + 1);
    v(b);
    delete[] d;
  }
}

int main(int argc, char *argv[]) {
  test_vector_subsetting();
  return 0;
}

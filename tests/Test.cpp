#include <iostream>
#include <ostream>

class Foo {
public:
  bool InUsage = false;
  int attr = 0;

  Foo(int i) : attr(i){};
  Foo() : attr(0){};

  template <typename T> Foo &operator=(const T &&otherFoo) {
    if (InUsage) {
      std::cout << "test" << std::endl;
      int temp = otherFoo[0];
      attr = temp;
    } else {
      attr = otherFoo[0];
    }
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Foo &f) {
    os << f.attr << std::endl;
    return os;
  }
};

template <typename T> class Bar {
public:
  const T &obj;

  Bar(T &&obj_) : obj(obj_) { obj_.InUsage = true; };
  Bar(T &obj_) : obj(obj_) { obj_.InUsage = true; };

  int operator[](size_t i) { return obj.attr + 1 + obj.attr; }
};

int main() {
  Foo f1;
  Bar b(f1);
  Foo f2(3);
  f1 = f2;
  std::cout << f1 << std::endl;
  return 0;
}

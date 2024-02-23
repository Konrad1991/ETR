#include <iostream>
#include <type_traits>

void bar(const double& a) {
  constexpr bool b = std::is_object_v<decltype(a)>;
  // constexpr bool b = std::is_rvalue_reference_v<decltype(a)>;
  std::cout << std::boolalpha << b << std::endl;
  // std::cout << std::boolalpha << std::is_trivially_assignable_v<decltype(a), double> << std::endl;
  // std::cout << std::boolalpha << std::is_literal_type_v<decltype(a)> << std::endl;
}

void foo(const double& a) {
    std::cout << "found r value reference" << std::endl;
}

void foo(double& a) {
  if constexpr (std::is_lvalue_reference<decltype(a)>::value) {
    std::cout << "found l value reference" << std::endl;
  } else {
    std::cout << "found r value reference" << std::endl;
  }
}

int main() {
  foo(1.3); // should print found r value
  double a = 1.3;
  foo(a); // should print found l value 

  bar(1.3);
  bar(a);
}

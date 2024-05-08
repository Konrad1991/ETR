#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

/*
1. define namespace Constants
2. put functions into struct
3. define function which returns struct wrapped in Vec or maybe also return only
naked struct
4. replace constant with function from Nr.3
*/

namespace Constants {

template <typename Func> struct ConstantClass {
  static constexpr Func func{};

  template <typename... Args> static constexpr auto getVal(Args &&...args) {
    return func(args...);
  }

  static constexpr auto getDeriv() { return 0; }

  using RetType = double;
  using TypeTrait = RetType;
  using CaseTrait = RetType;
};

template <auto Value> struct ConstantClassValue {
  static constexpr auto getVal() { return Value; }

  static constexpr auto getDeriv() { return 0; }

  using RetType = std::decay_t<decltype(Value)>;
  using TypeTrait = RetType;
  using CaseTrait = RetType;
};

inline auto cons1() {
  auto myFunction = []() { return 10.5; };
  return Vec<decltype(myFunction()),
             Constants::ConstantClass<decltype(myFunction)>>{};
}

// NOTE: this mechanism has to be exploited in the same way for functions such
// as vector, coca, etc.
template <auto Value> inline auto makeConstantClassValue() {
  return Vec<decltype(Value), ConstantClassValue<Value>>{};
}

template <auto Value> inline auto constVec() {
  auto vecFct = []() { return etr::vector(Value); };
  return Vec<decltype(vecFct()), Constants::ConstantClass<decltype(vecFct)>>{};
}

template <typename Value, typename T> inline auto constVec(T &av) {
  auto vecFct = [](auto av) {
    using constType = ExtractDType<Value>::type;
    double *ptr;
    constType::getPtr(av, &ptr);
    return etr::vector(*ptr);
  };
  return Vec<decltype(vecFct(av)),
             Constants::ConstantClass<decltype(vecFct)>>{};
}
} // namespace Constants

int main() {
  Vec<double> v = coca(1, 2, 3);
  printTAST<decltype(Constants::cons1())>();
  printTAST<decltype(v + Constants::cons1())>();
  using constantType = ExtractDType<decltype(Constants::cons1())>::type;
  printTAST<constantType>();
  std::cout << constantType::getVal() << std::endl;

  printTAST<decltype(Constants::makeConstantClassValue<20.5>())>();
  using constantTypeVal =
      ExtractDType<decltype(Constants::makeConstantClassValue<20.5>())>::type;
  printTAST<constantTypeVal>();
  std::cout << constantTypeVal::getVal() << std::endl;

  printTAST<decltype(Constants::constVec<3>())>();
  using constantTypeVec = ExtractedTypeD<decltype(Constants::constVec<3>())>;
  printTAST<constantTypeVec>();
  std::cout << constantTypeVec::getVal() << std::endl;

  Vec<double> a, b;

  AllVars<2, 0, 0> av(1, 0);
  av.initBuffer(&a, &b);
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);
  a = etr::coca(4, 2, 3);
  b = etr::coca(4, 5, 6);

  printTAST<decltype(Constants::constVec<decltype(vp1)>(av))>();
  using constTypeVec =
      ExtractTypeD<decltype(Constants::constVec<decltype(vp1)>(av))>::type;
  std::cout << constTypeVec::getVal(av) << std::endl;
}

#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

/*
1. Declare a std::array<etr::Vec<double>> Constants  in AllVars
2. Fill it at the beginning. Maybe fill as much as possible at compile time
3.
- declare constants as variables
  e.g. Vec<double, VarPointer<decltype(av), -1,
  0>, VariableTypeTrait> cp1
- declare constants as variables in own namespace
- declare lambda functions in namespace Constants which return the specific
  entries
4. write something like vp1*vp2*cp1
*/

/*
1. define namespace Constants
2. put functions into struct
3. define function which returns struct wrapped in Vec or maybe also return only
naked struct
4. replace constant with function from Nr.3
*/

namespace Constants {

// Bind function in class object
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

inline auto cons1() {
  auto myFunction = []() { return 10.5; };
  return Vec<decltype(myFunction()),
             Constants::ConstantClass<decltype(myFunction)>>{};
}

// Bind value in class object
template <auto Value> struct ConstantClassValue {
  static constexpr auto getVal() { return Value; }

  static constexpr auto getDeriv() { return 0; }

  using RetType = std::decay_t<decltype(Value)>;
  using TypeTrait = RetType;
  using CaseTrait = RetType;
};

// create vector object based on const value which is known at compile time
template <auto Value> inline auto constVec() {
  auto vecFct = []() { return etr::vector(Value); };
  return Vec<decltype(vecFct()), Constants::ConstantClass<decltype(vecFct)>>{};
}

template <auto Value> inline auto makeConstantClassValue() {
  return Vec<decltype(Value), ConstantClassValue<Value>>{};
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

// TODO: works but is not lazy has to be fixed
// TODO: has to return a lazy type object.
// Maybe it is possible to create a Vec<double, VarPointer....>
template <typename L, int Idx = 0, int TypeIdx = 0>
inline auto constVec1(L &av) {
  if constexpr (TypeIdx == 0) {
    return etr::vector(*av.varBuffer[Idx]->d.p);
  }
}

// for vector technically one can always return 0 for getVal
// How to handle this case efficiently for e.g. coca

} // namespace Constants

int main() {
  // example of a hardcoded lambda function bound in a class object
  Vec<double> v = coca(1, 2, 3);
  // printTAST<decltype(Constants::cons1())>();
  // printTAST<decltype(v + Constants::cons1())>();
  using constantType = ExtractDType<decltype(Constants::cons1())>::type;
  // printTAST<constantType>();
  std::cout << "harcoded lambda: " << constantType::getVal() << std::endl;

  // example of binding a constant value
  // printTAST<decltype(Constants::makeConstantClassValue<20.5>())>();
  using constantTypeVal =
      ExtractDType<decltype(Constants::makeConstantClassValue<20.5>())>::type;
  // printTAST<constantTypeVal>();
  std::cout << "hard coded compile time double: " << constantTypeVal::getVal()
            << std::endl;

  // example of creating a vector using a constant value known at compile time
  // printTAST<decltype(Constants::constVec<3>())>();
  using constantTypeVec = ExtractedTypeD<decltype(Constants::constVec<3>())>;
  // printTAST<constantTypeVec>();
  std::cout << "creating vector based on hardcoded int: "
            << constantTypeVec::getVal() << std::endl;

  // example of creating a vector object based on a type
  Vec<double> a, b;
  AllVars<2, 0, 0> av(1, 0);
  av.initBuffer(&a, &b);
  Vec<double, VarPointer<decltype(av), 0, 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1, 0>, VariableTypeTrait> vp2(av);
  a = etr::coca(4, 2, 3);
  b = etr::coca(4, 5, 6);
  // printTAST<decltype(Constants::constVec<decltype(vp1)>(av))>();
  using constTypeVec =
      ExtractTypeD<decltype(Constants::constVec<decltype(vp1)>(av))>::type;
  std::cout << "creating vector based on type: " << constTypeVec::getVal(av)
            << std::endl;

  std::cout << "creating a vector based on a hardcoded function: "
            << Constants::constVec1(av) << std::endl;
}

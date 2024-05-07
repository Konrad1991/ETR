#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

/*
1. define namespace Constants
2. put functions into struct
3. define function which returns struct wrapped in Vec or maybe also return only naked struct
4. replace constant with function from Nr.3
*/

namespace Constants {

template <typename Func>
struct ConstantClass {
  static constexpr Func func{};

  static constexpr auto getVal() {
    return func();
  }

  static constexpr auto getDeriv() {
    return 0; 
  }

  using RetType = double;
  using TypeTrait = RetType;
  using CaseTrait = RetType;
};

template <auto Value>
struct ConstantClassValue {
    static constexpr auto getVal() {
        return Value;
    }

    static constexpr auto getDeriv() {
        return 0; 
    }

    using RetType = std::decay_t<decltype(Value)>;
    using TypeTrait = RetType;
    using CaseTrait = RetType;
};


inline auto cons1() {
  auto myFunction = []() { return 10.5; };
  return Vec<decltype(myFunction()), Constants::ConstantClass<decltype(myFunction)> >{};
}

template <auto Value>
inline auto makeConstantClassValue() {
    return Vec<decltype(Value), ConstantClassValue<Value> >{};
}

}

int main() {
  Vec<double> v = coca(1, 2, 3);
  printTAST<decltype(Constants::cons1())>();
  printTAST<decltype(v + Constants::cons1())>();
  using constantType = ExtractDType<decltype(Constants::cons1())>::type;
  printTAST<constantType>();
  std::cout << constantType::getVal() << std::endl;

  printTAST<decltype(Constants::makeConstantClassValue<20.5>())>();
  using constantTypeVal = ExtractDType<decltype(Constants::makeConstantClassValue<20.5>())>::type;
  printTAST<constantTypeVal>();
  std::cout << constantTypeVal::getVal() << std::endl;
  
}

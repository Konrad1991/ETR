#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;

#include <iostream>
#include <functional>

// All constants handled as Vec<double, Buffer, ConstantTrait>

struct ConstantTrait {};

template<template<typename...> class Func, typename Trait = ConstantTrait >
struct FctInClass {
    template<typename... TArgs>
    static auto funcPtr(TArgs&&... args) {
        return Func<TArgs...>::func(std::forward<TArgs>(args)...);
    }
    template<typename... TArgs>
    constexpr auto callFunction(TArgs&&... args) const {
        return funcPtr(std::forward<TArgs>(args)...);
    }
};

template<typename T>
struct TemplatedFunc {
    static inline auto func(T arg) {
        return etr::vector(arg);
    }
};

int main() {

  Vec<double> length = coca(2);
  
  constexpr FctInClass<TemplatedFunc> f;
  Vec<double> res = f.callFunction(length); 
  print(res);

  Vec<double> a, b;
  etr::AllVars<2, 0, 0> av(1);
  av.initBuffer(&a, &b);
  Vec<double, VarPointer<decltype(av), 0>, VariableTypeTrait> vp1(av);
  Vec<double, VarPointer<decltype(av), 1>, VariableTypeTrait> vp2(av);
  a = etr::coca(1, 2, 3);
  b = etr::coca(4, 5, 6);
  eval<decltype(vp1 + vp2 * vp1)>(av);

  f.callFunction(3) + a;
  
}

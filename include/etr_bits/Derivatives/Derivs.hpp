#ifndef DERIVS_ETR_H
#define DERIVS_ETR_H

#include "../Core.hpp"
#include "../BinaryCalculations.hpp"
#include "../UnaryCalculations.hpp"
#include "AllVars.hpp"
#include "VarPointer.hpp"
#include "DerivTypes.hpp"

namespace etr {

template <typename T>
  requires IsVarPointer<T>
inline constexpr auto walkT() -> VariableType<T>;

template <typename T>
  requires IsMultiplication<T>
inline constexpr auto walkT();

template <typename T>
  requires IsAddition<T>
inline constexpr auto walkT();


template <typename T> inline constexpr auto walkT() {
  using cleanType = std::remove_const_t<std::remove_reference_t<T>>;
  using tD = ExtractedDType<cleanType>;
  constexpr auto res = walkT<tD>();
  static_assert(!IsVec<decltype(res)>,
                "Cannot create derivative expression tree");
  return VariableType<decltype(res)>();
}

template<typename T>
  requires std::is_arithmetic_v<T>
inline constexpr auto walkT() {
  
}

template <typename T>
  requires IsVarPointer<T>
inline constexpr auto walkT() -> VariableType<T> {
  static_assert(!IsVec<T>, "Cannot create derivative expression tree");
  return VariableType<T>();
}

template <typename TRaw>
  requires IsMultiplication<TRaw>
inline constexpr auto walkT() {
  using T = std::remove_const_t<std::remove_reference_t<TRaw>>;
  constexpr auto L = produceVariableType<typename T::typeTraitL>();
  constexpr auto R = produceVariableType<typename T::typeTraitR>();
  constexpr auto LDeriv = walkT<typename T::typeTraitL>();
  constexpr auto RDeriv = walkT<typename T::typeTraitR>();
  return produceQuarternyType<decltype(L), decltype(R), decltype(LDeriv),
                              decltype(RDeriv), QuarternaryTrait,
                              TimesDerivTrait>();
}

template <typename T>
  requires IsAddition<T>
inline constexpr auto walkT() {
  constexpr auto LDeriv = walkT<typename T::typeTraitL>();
  constexpr auto RDeriv = walkT<typename T::typeTraitR>();
  return produceBinaryType<decltype(LDeriv), decltype(RDeriv), BinaryTrait,
                           PlusDerivTrait>();
}

template <typename T>
  requires IsSinus<T>
inline constexpr auto walkT() {
  constexpr auto obj = walkT<typename T::typeTraitObj>();
  return produceUnaryType<decltype(obj), UnaryTrait,
                          SinusDerivTrait>(); // issue: has to be a binary type.
                                              // Change behaviour of binary type
                                              // by using Traits
}

template <typename T>
  requires(IsVec<T> && !IsVariable<T>)
inline constexpr auto walkT() {
  using tD = ExtractedTypeD<T>;
  constexpr auto res = walkT<tD>();
  return res;
}

template <typename T, typename AV>
  requires(IsVec<T> && !IsVariable<T>)
inline void eval(AV &av) {
  using tD = ExtractedTypeD<T>;
  //printTAST<tD>();
  constexpr auto res = walkT<tD>();
  //std::cout << "final result " << std::endl;
  //printTAST<decltype(res)>();

  for (size_t i = 0; i < res.getSize(av); i++) {
    std::cout << "val = " << res.getVal(av, i)
              << " deriv = " << res.getDeriv(av, i) << std::endl;
  }
}

} // namespace etr

#endif

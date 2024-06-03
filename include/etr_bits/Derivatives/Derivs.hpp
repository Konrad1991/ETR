#ifndef DERIVS_ETR_H
#define DERIVS_ETR_H

#include "../BinaryCalculations.hpp"
#include "../Core.hpp"
#include "../UnaryCalculations.hpp"
#include "AllVars.hpp"
#include "DerivTypes.hpp"
#include "VarPointer.hpp"
#include "getDerivs.hpp"

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

template <typename T>
  requires IsVarPointer<T>
inline constexpr auto walkT() -> VariableType<T> {
  static_assert(!IsVec<T>, "Cannot create derivative expression tree");
  return VariableType<T>();
}

template <typename T>
  requires IsConstant<T>
inline constexpr auto walkT() {
  return Constants<typename T::Type, T::I, ConstantTypeTrait>{};
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
  return produceUnaryType<decltype(obj), UnaryTrait, SinusDerivTrait>();
}

template <typename T>
  requires(IsVec<T> && !IsVariable<T>)
inline constexpr auto walkT() {
  using tD = ExtractedTypeD<T>;
  constexpr auto res = walkT<tD>();
  return res;
}

} // namespace etr

#endif

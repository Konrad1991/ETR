#ifndef TYPES_ETR_H
#define TYPES_ETR_H

#include "Header.hpp"

namespace etr {
template <typename T, typename BaseTrait = BaseStoreTrait> struct BaseStore;
template <typename T = double, typename BorrowSEXPTrait = BorrowSEXPTrait>
struct BorrowSEXP;
template <typename T, typename BorrowTrait = BorrowTrait> struct Borrow;
template <typename T, typename SubsetTrait = SubsetTrait> struct Subset;
template <typename T, typename Trait = BufferTrait,
          typename CTrait = VariableTrait>
struct Buffer;
template <typename T, typename R = Buffer<T>, typename Trait = VectorTrait>
struct Vec;
template <typename L, typename R, typename Trait = BinaryTrait,
          typename CTrait = BinaryTrait>
struct BinaryOperation;
template <typename I, typename Trait = UnaryTrait, typename CTrait = UnaryTrait>
struct UnaryOperation;

template <typename L, typename R, typename Trait = BinaryTrait,
          typename CTrait = BinaryTrait>
struct BinaryOperationDeriv;

template <typename T> struct ExtractDataType;
template <typename T, typename R, typename Trait>
struct ExtractDataType<Vec<T, R, Trait>> {
  using RetType = T;
};
template <typename T, typename R, typename Trait>
struct ExtractDataType<const Vec<T, R, Trait>> {
  using RetType = T const;
};
template <typename T>
using ExtractedTypeData = typename ExtractDataType<T>::RetType;

template <typename T> struct ExtractDataType;
template <typename T, typename R, typename Trait>
struct ExtractDataType<Buffer<T, R, Trait>> {
  using RetType = T;
};
template <typename T, typename R, typename Trait>
struct ExtractDataType<const Buffer<T, R, Trait>> {
  using RetType = T const;
};

template <typename Trait = DoubleTrait> struct doubleWrapper {
  using TypeTrait = Trait;
  using Type = DoubleTrait;
  BaseType d;
};

template <typename T>
  requires std::is_same_v<T, double>
constexpr doubleWrapper<DoubleTrait> convert(const T &obj) {
  return doubleWrapper<DoubleTrait>(obj);
}

template <typename T>
  requires std::is_same_v<T, int>
constexpr doubleWrapper<IntTrait> convert(const T &obj) {
  return doubleWrapper<IntTrait>(obj);
}

template <typename T>
  requires std::is_same_v<T, bool>
constexpr doubleWrapper<BoolTrait> convert(const T &obj) {
  return doubleWrapper<BoolTrait>(obj);
}

template <typename T> constexpr T convert(const T &obj) {
  return obj;
  // return std::forward(obj);
}


template <typename L, typename R, typename LDeriv, typename RDeriv,
          typename Trait, typename OpTrait>
struct QuarternyType;

template <typename LDeriv, typename RDeriv, typename Trait, typename OpTrait>
struct BinaryType;

template <typename Deriv, typename Trait, typename OpTrait> struct UnaryType;

template <typename T, typename Trait = VariableTypeTrait> struct VariableType;

template <typename T, int Idx, typename Trait = VarPointerTrait>
struct VarPointer;

template <int NBuffer_, int NBorrow_, int NBorrowSEXP_> struct AllVars;

} // namespace etr

#endif
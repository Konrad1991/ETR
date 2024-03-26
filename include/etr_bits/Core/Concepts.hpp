#ifndef CONCEPTS_ETR_H
#define CONCEPTS_ETR_H

#include "Header.hpp"

namespace etr {
template <typename T>
concept isBID = requires {
  requires std::is_same_v<T, bool> || std::is_same_v<T, int> ||
               std::is_same_v<T, double>;
};

template <typename R>
concept IsVecDouble = requires {
  typename R::TypeTrait;
  typename R::Type;
  requires std::is_same_v<typename R::TypeTrait, VectorTrait>;
  requires std::is_same_v<typename R::Type, BaseType>;
};

template <typename R>
concept IsVecBool = requires {
  typename R::TypeTrait;
  typename R::Type;
  requires std::is_same_v<typename R::TypeTrait, VectorTrait>;
  requires std::is_same_v<typename R::Type, bool>;
};

template <typename T>
concept UnaryOrBinaryOperation = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
               typename std::remove_reference<decltype(t)>::type::CaseTrait,
               UnaryTrait>::value ||
               std::is_same<
                   typename std::remove_reference<decltype(t)>::type::CaseTrait,
                   BinaryTrait>::value;
};

template <typename T>
concept IsUnary = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      UnaryTrait>::value;
};

template <typename T>
concept IsBinary = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      BinaryTrait>::value;
};

template <typename T>
concept NotOperation = !requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
               typename std::remove_reference<decltype(t)>::type::CaseTrait,
               UnaryTrait>::value ||
               std::is_same<
                   typename std::remove_reference<decltype(t)>::type::CaseTrait,
                   BinaryTrait>::value ||
               std::is_same<
                   typename std::remove_reference<decltype(t)>::type::CaseTrait,
                   RBufTrait>::value;
};

template <typename T>
concept Operation = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
               typename std::remove_reference<decltype(t)>::type::CaseTrait,
               UnaryTrait>::value ||
               std::is_same<
                   typename std::remove_reference<decltype(t)>::type::CaseTrait,
                   BinaryTrait>::value ||
               std::is_same<
                   typename std::remove_reference<decltype(t)>::type::CaseTrait,
                   RBufTrait>::value;
};

template <typename T>
concept IsRVec = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      RVecTrait>::value;
};

template <typename T>
concept IsRBuf = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      RBufTrait>::value;
};

template <typename T>
concept IsVariable = requires {
  typename T::CaseTrait;
  requires std::is_same_v<typename T::CaseTrait, VariableTrait>;
};

template <typename R>
concept IsVec = requires {
  typename R::TypeTrait;
  requires std::is_same_v<typename R::TypeTrait, VectorTrait>;
};

template <typename R>
concept IsVecLorRorCalc = requires {
  typename R::TypeTrait;
  requires std::is_same_v<typename R::TypeTrait, VectorTrait> ||
               std::is_same_v<typename R::TypeTrait, RVecTrait> ||
               std::is_same_v<typename R::TypeTrait, UnaryTrait> ||
               std::is_same_v<typename R::TypeTrait, BinaryTrait>;
};

template <typename T>
concept IsMultiplication = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  typename std::remove_reference<decltype(t)>::type::TypeTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      BinaryTrait>::value;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::TypeTrait,
      TimesTrait>::value;
};

/*
template <typename T>
concept IsAddition = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  typename std::remove_reference<decltype(t)>::type::TypeTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      BinaryTrait>::value;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::TypeTrait,
      PlusTrait>::value;
};
*/

template <typename T>
concept IsSinus = requires(T t) {
  typename std::remove_reference<decltype(t)>::type::CaseTrait;
  typename std::remove_reference<decltype(t)>::type::TypeTrait;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::CaseTrait,
      UnaryTrait>::value;
  requires std::is_same<
      typename std::remove_reference<decltype(t)>::type::TypeTrait,
      SinusTrait>::value;
};

/*
issue:
Extract type for Buffer, Borrow, BorrowSEXP, BinaryOp, UnaryOp
For all the different types.
Use ExtractDataType for all of these cases.
Use RetType everywhere. Check that it is declared as using RetType = ...
everywhere
*/

template <typename T>
auto extractRetType(const T &instance) ->
    typename T::RetType { // issue: finish work. This can be used to handle also
                          // int and bool for all unary/binary operations
  using ret = typename T::RetType;
  return instance.getRetType();
}

} // namespace etr

#endif
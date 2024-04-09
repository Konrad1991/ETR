#ifndef COLON_ETR_H
#define COLON_ETR_H

/*
        Var1       Var2
1 arithmetic arithmetic
2        Vec arithmetic
3  const Vec arithmetic
4 arithmetic        Vec
5        Vec        Vec
6  const Vec        Vec
7 arithmetic  const Vec
8        Vec  const Vec
9  const Vec  const Vec

const Vec is an Operation
issue: long double change to BaseType?
*/

#include "AllocationUtils.hpp"
#include <type_traits>

namespace etr {

inline auto colonInt(long long start, long long end) {
  if (start < end) {
    size_t length = convertSize(end - start + 1);
    Vec<double, Buffer<double, RBufTrait>, RVecTrait> ret(SI{length});
    for (size_t i = 0; i < ret.size(); i++) {
      ret[i] = start;
      start++;
    }
    return ret;
  }
  size_t length = convertSize(start - end + 1);
  Vec<double, Buffer<double, RBufTrait>, RVecTrait> ret(SI{length});
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = start;
    start--;
  }
  return ret;
}

inline auto colonFloat(long double start, long double end) {
  if (start < end) {
    size_t length = convertSize(end - start + 1);
    Vec<double, Buffer<double, RBufTrait>, RVecTrait> ret(SI{length});
    size_t counter = 0;
    while (start <= end) {
      ret[counter] = start;
      start++;
      counter++;
    }
    return ret;
  }
  size_t length = convertSize(start - end + 1);
  Vec<double, Buffer<double, RBufTrait>, RVecTrait> ret(SI{length});
  size_t counter = 0;
  while (end <= start) {
    ret[counter] = start;
    start--;
    counter++;
  }
  return ret;
}

template <typename A, typename O>
  requires std::is_arithmetic_v<A> && std::is_arithmetic_v<O>
inline auto colon(A start, O end) {
  if constexpr (std::is_integral_v<A> && std::is_integral_v<O>) {
    return colonInt(start, end);
  } else if constexpr (std::is_floating_point_v<A> &&
                       std::is_floating_point_v<O>) {
    return colonFloat(start, end);
  } else if constexpr (std::is_integral_v<A> && std::is_floating_point_v<O>) {
    return colonFloat(static_cast<long double>(start), end);
  } else if constexpr (std::is_floating_point_v<A> && std::is_integral_v<O>) {
    return colonFloat(start, static_cast<long double>(end));
  }
}

/*
template <typename A, typename O>
  requires IsVec<A> && IsVec<O>
inline auto colon(const A &start, const O &end) {
  using typeTraitA =
      std::remove_reference<decltype(convert(start))>::type::TypeTrait;
  using typeTraitO =
      std::remove_reference<decltype(convert(end))>::type::TypeTrait;
  using isVecA = std::is_same<typeTraitA, VectorTrait>;
  using isVecO = std::is_same<typeTraitO, VectorTrait>;
  double s = 0.0;
  double e = 0.0;
  if constexpr (isVecA::value && isVecO::value) {
    ass(start.size() == 1,
        "Element 'from' passed to colon has more than one argument");
    ass(end.size() == 1,
        "Element 'to' passed to colon has more than one argument");
    s = start[0];
    e = end[0];
  } else if constexpr (!isVecA::value && isVecO::value) {
    ass(end.size() == 1,
        "Element 'to' passed to colon has more than one argument");
    s = static_cast<BaseType>(start);
    e = end[0];
  } else if constexpr (isVecA::value && !isVecO::value) {
    ass(start.size() == 1,
        "Element 'from' passed to colon has more than one argument");
    s = start[0];
    e = static_cast<BaseType>(end);
  } else {
    s = static_cast<BaseType>(start);
    e = static_cast<BaseType>(end);
  }
  Vec<BaseType> ret(SI{static_cast<size_t>(e - s + 1)});
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = s + static_cast<BaseType>(i);
  }
  return ret;
}
*/

} // namespace etr

#endif

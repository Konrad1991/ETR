#ifndef COLON_ETR_H
#define COLON_ETR_H

#include "AllocationUtils.hpp"

namespace etr {
template <typename A, typename O>
inline Vec<double> colon(const A &start, const O &end) {
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

} // namespace etr

#endif
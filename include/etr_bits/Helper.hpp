#ifndef HELPER_ETR_H
#define HELPER_ETR_H

#include "BufferVector.hpp"
#include "Core.hpp"

namespace etr {

#ifdef STANDALONE_ETR

template <typename T> bool ISNA(T inp) { return std::isnan(inp); }

template <typename T> bool R_FINITE(T inp) { return !std::isinf(inp); }

#endif

template <typename T, typename R> inline Vec<bool> isNA(Vec<T, R> &inp) {
  Vec<bool> res(inp.size());
  for (size_t i = 0; i < res.size(); i++) {
    res[i] = ISNA(inp[i]);
  }
  return res;
}

template <typename T, typename R, typename Trait>
inline Vec<bool> isNA(Vec<T, R, Trait> &inp) {
  Vec<bool> res(inp.size());
  for (size_t i = 0; i < res.size(); i++) {
    res[i] = ISNA(inp[i]);
  }
  return res;
}

template <typename T, typename R> inline Vec<bool> isNA(const Vec<T, R> &&inp) {
  Vec<bool> res(inp.size());
  for (size_t i = 0; i < res.size(); i++) {
    res[i] = ISNA(inp[i]);
  }
  return res;
}

template <typename T, typename R, typename Trait>
inline Vec<bool> isNA(const Vec<T, R, Trait> &&inp) {
  Vec<bool> res(inp.size());
  for (size_t i = 0; i < res.size(); i++) {
    res[i] = ISNA(inp[i]);
  }
  return res;
}

inline Vec<BaseType> isInfinite(const Vec<BaseType> &inp) {
  Vec<BaseType> res(inp.size());
  for (size_t i = 0; i < res.size(); i++) {
    res[i] = (!R_FINITE(inp[i]) && !ISNA(inp[i]));
  }
  return res;
}

inline int length(double inp) { return 1; }

inline int length(int inp) { return 1; }

inline int length(bool inp) { return 1; }

inline int length(const Vec<BaseType> &inp) { return inp.size(); }

template <typename L, typename R> inline int length(const Vec<L, R> &inp) {
  return inp.size();
}

inline Vec<BaseType> dim(const Vec<BaseType> &inp) {
  using typeTraitInp = std::remove_reference<decltype(inp)>::type::TypeTrait;
  using isVec = std::is_same<typeTraitInp, VectorTrait>;
  static_assert(isVec::value, "dim can only be called with matrix");
  ass(inp.im(), "dim can only be called with matrix");
  Vec<BaseType> ret(SI(2));
  ret[0] = inp.nr();
  ret[1] = inp.nc();
  return ret;
}

} // namespace etr
#endif

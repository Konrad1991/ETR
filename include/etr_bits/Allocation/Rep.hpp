#ifndef REP_ETR_H
#define REP_ETR_H

#include "AllocationUtils.hpp"

namespace etr {
template <typename L, typename R>
  requires std::is_arithmetic_v<L> && std::is_arithmetic_v<R>
inline Vec<L, Buffer<L, BufferTrait, RBufTrait>, RVecTrait> rep(L inp, R s) {
  size_t length = convertSize(s);
  Vec<L> ret(length);
  ret.fill(inp);
  return ret;
}

template <typename L, typename R>
  requires IsVec<L> && std::is_arithmetic_v<R>
inline auto rep(L &inp, R s) {
  size_t length = convertSize(s) * inp.size();
  using DataType = ExtractDataType<L>::type;
  Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> ret(
      length);
  size_t counter = 0;
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = inp[counter];
    counter++;
    if (counter >= inp.size())
      counter = 0;
  }
  return ret;
}

template <typename L, typename R>
  requires Operation<L> && std::is_arithmetic_v<R>
inline auto rep(const L &inp, R s) {
  size_t length = convertSize(s) * inp.size();
  using DataType = ExtractDataType<L>::type;
  Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> ret(
      length);
  size_t counter = 0;
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = inp[counter];
    counter++;
    if (counter >= inp.size())
      counter = 0;
  }
  return ret;
}

template <typename L, typename R>
  requires std::is_arithmetic_v<L> && IsVec<R>
inline auto rep(L inp, R &s) {
  size_t length = convertSize(s);
  Vec<L> ret(length);
  ret.fill(inp);
  return ret;
}

template <typename L, typename R>
  requires IsVec<L> && IsVec<R>
inline auto rep(L &inp, R &s) {
  size_t length = convertSize(s) * inp.size();
  using DataType = ExtractDataType<L>::type;
  Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> ret(
      length);
  size_t counter = 0;
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = inp[counter];
    counter++;
    if (counter >= inp.size())
      counter = 0;
  }
  return ret;
}

template <typename L, typename R>
  requires Operation<L> && IsVec<R>
inline auto rep(const L &inp, R &s) {
  size_t length = convertSize(s) * inp.size();
  using DataType = ExtractDataType<L>::type;
  Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> ret(
      length);
  size_t counter = 0;
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = inp[counter];
    counter++;
    if (counter >= inp.size())
      counter = 0;
  }
  return ret;
}

template <typename L, typename R>
  requires std::is_arithmetic_v<L> && Operation<R>
inline auto rep(L inp, const R &s) {
  size_t length = convertSize(s);
  Vec<L> ret(length);
  ret.fill(inp);
  return ret;
}

template <typename L, typename R>
  requires IsVec<L> && Operation<R>
inline auto rep(L &inp, const R &s) {
  size_t length = convertSize(s) * inp.size();
  using DataType = ExtractDataType<L>::type;
  Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> ret(
      length);
  size_t counter = 0;
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = inp[counter];
    counter++;
    if (counter >= inp.size())
      counter = 0;
  }
  return ret;
}

template <typename L, typename R>
  requires Operation<L> && Operation<R>
inline auto rep(const L &inp, const R &s) {
  size_t length = convertSize(s) * inp.size();
  using DataType = ExtractDataType<L>::type;
  Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> ret(
      length);
  size_t counter = 0;
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = inp[counter];
    counter++;
    if (counter >= inp.size())
      counter = 0;
  }
  return ret;
}
} // namespace etr

#endif
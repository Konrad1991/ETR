#ifndef ALLOCATION_ETR_H
#define ALLOCATION_ETR_H

#include "BufferVector.hpp"
#include "Core.hpp"

namespace etr {

inline auto produceRVec(size_t s) {
  ass(s > 0, "invalid length argument");
  return Vec<BaseType, Buffer<BaseType, BufferTrait, RBufTrait>, RVecTrait>(SI{s});
}

template <typename T> inline auto vector(const T &inp) {
  if constexpr (std::is_same_v<T, size_t>) {
    return produceRVec(inp);
  } else if constexpr (std::is_floating_point_v<T>) {
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    return produceRVec(static_cast<size_t>(inp));
  } else if constexpr (std::is_integral_v<T>) {
    return produceRVec(static_cast<size_t>(inp));
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1, "invalid length argument");
    return produceRVec(static_cast<size_t>(inp[0]));
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in vector");
  }
}

template <typename T> inline auto vector(T &inp) {
  if constexpr (std::is_same_v<T, size_t>) {
    return produceRVec(inp);
  } else if constexpr (std::is_floating_point_v<T>) {
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    return produceRVec(static_cast<size_t>(inp));
  } else if constexpr (std::is_integral_v<T>) {
    return produceRVec(static_cast<size_t>(inp));
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1, "invalid length argument");
    return produceRVec(static_cast<size_t>(inp[0]));
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in vector");
  }
}

template <typename T> inline size_t convertSize(const T &inp) {
  if constexpr (std::is_same_v<T, size_t>) {
    ass(inp >= 1, "invalid times argument");
    return std::forward(inp);
  } else if constexpr (std::is_floating_point_v<T>) {
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    ass(inp >= 1.0, "invalid times argument");
    return static_cast<size_t>(inp);
  } else if constexpr (std::is_integral_v<T>) {
    ass(inp >= 1, "invalid times argument");
    return static_cast<size_t>(inp);
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1 && inp[0] >= 1, "invalid times argument");
    return static_cast<size_t>(inp[0]);
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in rep");
  }
}

/*
        Var1       Var2
1 arithmetic arithmetic  done
2        Vec arithmetic  done
3  Operation arithmetic  done
4 arithmetic        Vec  done
5        Vec        Vec  done
6  Operation        Vec  done
7 arithmetic  Operation  done
8        Vec  Operation
9  Operation  Operation

In Operation also Rvecs are included
*/

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

inline Vec<BaseType> matrix(int nrows, int ncols) {
  return Vec<BaseType>(nrows, ncols);
}

template <typename V, typename R, typename C>
inline Vec<BaseType> matrix(const V &inp, const R &nrows, const C &ncols) {
  if constexpr (std::is_arithmetic_v<R> && std::is_arithmetic_v<C>) {
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<size_t>(nrows), static_cast<size_t>(ncols));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<size_t>(nrows) * static_cast<size_t>(ncols)) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<size_t>(nrows), static_cast<size_t>(ncols));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  } else if constexpr (!std::is_arithmetic_v<R> && std::is_arithmetic_v<C>) {
    ass(nrows.size() == 1, "invalid length argument for rows");
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<size_t>(nrows[0]),
                        static_cast<size_t>(ncols));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<size_t>(nrows[0]) * static_cast<size_t>(ncols)) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<size_t>(nrows[0]),
                        static_cast<size_t>(ncols));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  } else if constexpr (std::is_arithmetic_v<R> && !std::is_arithmetic_v<C>) {
    ass(ncols.size() == 1, "invalid length argument for cols");
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<size_t>(nrows),
                        static_cast<size_t>(ncols[0]));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<size_t>(nrows) * static_cast<size_t>(ncols[0])) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<size_t>(nrows),
                        static_cast<size_t>(ncols[0]));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  } else {
    ass(nrows.size() == 1, "invalid length argument for rows");
    ass(ncols.size() == 1, "invalid length argument for cols");
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<size_t>(nrows[0]),
                        static_cast<size_t>(ncols[0]));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<size_t>(nrows[0]) * static_cast<size_t>(ncols[0])) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<size_t>(nrows[0]),
                        static_cast<size_t>(ncols[0]));
      for (size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  }
}

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
  Vec<BaseType> ret(static_cast<size_t>(e - s + 1));
  for (size_t i = 0; i < ret.size(); i++) {
    ret[i] = s + static_cast<BaseType>(i);
  }
  return ret;
}

} // namespace etr

#endif
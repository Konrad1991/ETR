#ifndef MATRIX_ETR_H
#define MATRIX_ETR_H

#include "AllocationUtils.hpp"
#include <cstddef>

namespace etr {

/*
 TODO: all cases whith data, ncols
*/

/*
TODO: all cases with data, nrows
TODO: missing tests
arithmetic
Vec
const Vec
*/

template <typename T>
  requires std::is_arithmetic_v<T>
inline auto matrix(T val) {
  auto vec = createRVec(1);
  vec.d.mp.setMatrix(true, 1, 1);
  vec[0] = val;
  return vec;
}

template <typename T>
  requires IsVec<T>
inline auto matrix(T &val) {
  auto vec = createRVec(val.size());
  vec.d.mp.setMatrix(true, val.size(), 1);
  vec.fill(val);
  return vec;
}

template <typename T>
  requires IsVec<T>
inline auto matrix(const T &val) {
  auto vec = createRVec(val.size());
  vec.d.mp.setMatrix(true, val.size(), 1);
  vec.fill(val);
  return vec;
}
/*
TODO: Matrix missing tests
        Var1       Var2
1 arithmetic arithmetic done
2        Vec arithmetic done
3  const Vec arithmetic done
4 arithmetic        Vec done
5        Vec        Vec done
6  const Vec        Vec done
7 arithmetic  const Vec done
8        Vec  const Vec done
9  const Vec  const Vec done
const Vec is an Operation
*/

// TODO: this changes the behaviour of the matrix function in ast2ast/ETR
// therefore the documentation has to be updated

// NOTE: the second argument is always handled as constant object. As only the
// first element is used and the remaining elements are ignored. Therefore, this
// simplification is added as it is unlikely that large vectors are used as a
// second argument.

// TODO: Check whether an l vector is copied when passed as const Vec&

// TODO: add here the warning messages as in R
template <typename L, typename R>
  requires IsVec<L> && std::is_arithmetic_v<R>
inline auto matrix(const L &inp, R nrows) {
  using DataType = ExtractDataType<L>::RetType;
  if (inp.size() == nrows) {
    std::size_t size = convertSize(nrows);
    Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
        SI{size});
    for (std::size_t i = 0; i < res.size(); i++) {
      res[i] = inp[i];
    }
    res.d.mp.setMatrix(true, size, 1);
    return res;
  } else if (inp.size() < nrows) {
    ass(nrows > 0, "data is too long");
    std::size_t size = convertSize(nrows);
    Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
        SI{size});
    for (std::size_t i = 0; i < res.size(); i++) {
      res[i] = inp[i % inp.size()];
    }
    res.d.mp.setMatrix(true, nrows, 1);
    return res;
  } else {
    if (inp.size() % nrows == 0) {
      std::size_t size = convertSize(inp.size());
      Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
          SI{size});
      for (std::size_t i = 0; i < res.size(); i++) {
        res[i] = inp[i];
      }
      res.d.mp.setMatrix(true, nrows, static_cast<std::size_t>(inp.size() / nrows));
      return res;
    } else {
      std::size_t size = convertSize(inp.size() + (inp.size() % nrows) - 1);
      Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
          SI{size});
      for (std::size_t i = 0; i < res.size(); i++) {
        res[i] = inp[i % inp.size()];
      }
      res.d.mp.setMatrix(true, nrows, static_cast<std::size_t>(size / nrows));
      return res;
    }
  }
}

template <typename L, typename R>
  requires std::is_arithmetic_v<L> && std::is_arithmetic_v<R>
inline auto matrix(L inp, R nrows) {
  ass(nrows > 0, "data is too long");
  auto res = createRVec(nrows);
  res.fill(inp);
  res.d.mp.setMatrix(true, nrows, 1);
  return res;
}

// TODO: add warning that only first element is used
template <typename L, typename R>
  requires std::is_arithmetic_v<L> && IsVec<R>
inline auto matrix(L inp, const R &nrows) {
  return matrix(inp, convertSize(nrows[0]));
}

template <typename L, typename R>
  requires IsVec<L> && IsVec<R>
inline auto matrix(const L &inp, const R &nrows) {
  using DataType = ExtractDataType<L>::RetType;
  if (inp.size() == convertSize(nrows[0])) {
    std::size_t size = convertSize(nrows[0]);
    Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
        SI{size});
    for (std::size_t i = 0; i < res.size(); i++) {
      res[i] = inp[i];
    }
    res.d.mp.setMatrix(true, size, 1);
    return res;
  } else if (inp.size() < convertSize(nrows[0])) {
    std::size_t size = convertSize(nrows[0]);
    Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
        SI{size});
    for (std::size_t i = 0; i < res.size(); i++) {
      res[i] = inp[i % inp.size()];
    }
    res.d.mp.setMatrix(true, size, 1);
    return res;
  } else {
    if (inp.size() % nrows == 0) {
      std::size_t size = convertSize(inp.size());
      Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
          SI{size});
      for (std::size_t i = 0; i < res.size(); i++) {
        res[i] = inp[i];
      }
      res.d.mp.setMatrix(true, nrows, static_cast<std::size_t>(inp.size() / nrows));
      return res;
    } else {
      std::size_t size = convertSize(inp.size() + (inp.size() % nrows[0]) - 1);
      Vec<DataType, Buffer<DataType, BufferTrait, RBufTrait>, RVecTrait> res(
          SI{size});
      for (std::size_t i = 0; i < res.size(); i++) {
        res[i] = inp[i % inp.size()];
      }
      res.d.mp.setMatrix(true, nrows, static_cast<std::size_t>(size / nrows[0]));
      return res;
    }
  }
}

/*
TODO: Matrix missing implementation with 3 args
       Var1     Var2     Var3
1       vec      vec      vec
2     arith      vec      vec
3  constVec      vec      vec
4       vec    arith      vec
5     arith    arith      vec
6  constVec    arith      vec
7       vec constVec      vec
8     arith constVec      vec
9  constVec constVec      vec
10      vec      vec    arith
11    arith      vec    arith
12 constVec      vec    arith
13      vec    arith    arith
14    arith    arith    arith
15 constVec    arith    arith
16      vec constVec    arith
17    arith constVec    arith
18 constVec constVec    arith
19      vec      vec constVec
20    arith      vec constVec
21 constVec      vec constVec
22      vec    arith constVec
23    arith    arith constVec
24 constVec    arith constVec
25      vec constVec constVec
26    arith constVec constVec
27 constVec constVec constVec
*/

template <typename V, typename R, typename C>
inline Vec<BaseType> matrix(const V &inp, const R &nrows, const C &ncols) {
  if constexpr (std::is_arithmetic_v<R> && std::is_arithmetic_v<C>) {
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<std::size_t>(nrows), static_cast<std::size_t>(ncols));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<std::size_t>(nrows) * static_cast<std::size_t>(ncols)) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<std::size_t>(nrows), static_cast<std::size_t>(ncols));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  } else if constexpr (!std::is_arithmetic_v<R> && std::is_arithmetic_v<C>) {
    ass(nrows.size() == 1, "invalid length argument for rows");
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<std::size_t>(nrows[0]),
                        static_cast<std::size_t>(ncols));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<std::size_t>(nrows[0]) * static_cast<std::size_t>(ncols)) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<std::size_t>(nrows[0]),
                        static_cast<std::size_t>(ncols));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  } else if constexpr (std::is_arithmetic_v<R> && !std::is_arithmetic_v<C>) {
    ass(ncols.size() == 1, "invalid length argument for cols");
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<std::size_t>(nrows),
                        static_cast<std::size_t>(ncols[0]));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<std::size_t>(nrows) * static_cast<std::size_t>(ncols[0])) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<std::size_t>(nrows),
                        static_cast<std::size_t>(ncols[0]));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  } else {
    ass(nrows.size() == 1, "invalid length argument for rows");
    ass(ncols.size() == 1, "invalid length argument for cols");
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType> ret(static_cast<std::size_t>(nrows[0]),
                        static_cast<std::size_t>(ncols[0]));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = static_cast<BaseType>(inp);
      return ret;
    } else {
      ass((static_cast<std::size_t>(nrows[0]) * static_cast<std::size_t>(ncols[0])) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<std::size_t>(nrows[0]),
                        static_cast<std::size_t>(ncols[0]));
      for (std::size_t i = 0; i < ret.size(); i++)
        ret[i] = inp[i];
      return ret;
    }
  }
}

} // namespace etr

#endif

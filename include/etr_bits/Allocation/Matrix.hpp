#ifndef MATRIX_ETR_H
#define MATRIX_ETR_H

#include "AllocationUtils.hpp"

namespace etr {

/*
arithmetic
Vec
const Vec
*/

template<typename T>
  requires std::is_arithmetic_v<T>
inline auto matrix(T val) {
  auto vec = createRVec(1);
  vec.d.mp.setMatrix(true, 1, 1); 
  vec[0] = val;
  return vec;
}

template<typename T>
  requires IsVec<T>
inline auto matrix(T& val) {
  auto vec = createRVec(val.size());
  vec.d.mp.setMatrix(true, val.size(), 1); 
  vec.fill(val);
  return vec;
}

template<typename T>
  requires IsVec<T>
inline auto matrix(const T& val) {
  auto vec = createRVec(val.size());
  vec.d.mp.setMatrix(true, val.size(), 1); 
  vec.fill(val);
  return vec;
}
/*
        Var1       Var2
1 arithmetic arithmetic done
2        Vec arithmetic
3  const Vec arithmetic
4 arithmetic        Vec
5        Vec        Vec
6  const Vec        Vec
7 arithmetic  const Vec
8        Vec  const Vec
9  const Vec  const Vec

const Vec is an Operation
*/

template<typename L, typename R>
  requires std::is_arithmetic_v<L> && std::is_arithmetic_v<R>
inline auto matrix(L nrows, R ncols) {
  return createRVec(nrows * ncols);
}

/*
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

} // namespace etr

#endif

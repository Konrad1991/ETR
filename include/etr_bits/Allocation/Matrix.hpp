#ifndef MATRIX_ETR_H
#define MATRIX_ETR_H

#include "AllocationUtils.hpp"
#include <cstddef>

namespace etr {

// NOTE: the matrix calls with only one or two arguments are "filled up" with
// the default values at the R level

// NOTE: the second argument is always handled as constant object. As only the
// first element is used and the remaining elements are ignored. Therefore, this
// simplification is added as it is unlikely that large vectors are used as a
// second argument.

/*
TODO: Matrix missing implementation with 3 args
   Var1  Var2  Var3
1 arith arith arith done
2   vec arith arith done
3 arith   vec arith
4   vec   vec arith
5 arith arith   vec
6   vec arith   vec
7 arith   vec   vec
8   vec   vec   vec
*/

template <typename V, typename R, typename C>
  requires(std::is_arithmetic_v<R> && std::is_arithmetic_v<C>)
inline auto matrix(V &&inp, R &&nrows, C &&ncols) {
  if constexpr (std::is_arithmetic_v<V>) {
    Vec<BaseType, Buffer<BaseType, BufferTrait, RBufTrait>, RVecTrait> ret(
        convertSize(nrows), convertSize(ncols));
    ret.d.fill(inp);
    return ret;
  } else {
    ass((static_cast<std::size_t>(nrows) * static_cast<std::size_t>(ncols)) ==
            inp.size(),
        "data length is not a sub-multiple or multiple of the number of "
        "rows");
    Vec<BaseType, Buffer<BaseType, BufferTrait, RBufTrait>, RVecTrait> ret(
        convertSize(nrows), convertSize(ncols));
    ret.d.fill(inp);
    return ret;
  }
}

template <typename V, typename R, typename C>
inline Vec<BaseType> matrix_old(V &&inp, R &&nrows, C &&ncols) {
  if constexpr (std::is_arithmetic_v<R> && std::is_arithmetic_v<C>) {
    if constexpr (std::is_arithmetic_v<V>) {
      Vec<BaseType, Buffer<BaseType, BufferTrait, RBufTrait>, RVecTrait> ret(
          static_cast<std::size_t>(nrows), static_cast<std::size_t>(ncols));
      ret.d.fill(inp);
      return ret;
    } else {
      ass((static_cast<std::size_t>(nrows) * static_cast<std::size_t>(ncols)) ==
              inp.size(),
          "data length is not a sub-multiple or multiple of the number of "
          "rows");
      Vec<BaseType> ret(static_cast<std::size_t>(nrows),
                        static_cast<std::size_t>(ncols));
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
      ass((static_cast<std::size_t>(nrows[0]) *
           static_cast<std::size_t>(ncols)) == inp.size(),
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
      ass((static_cast<std::size_t>(nrows) *
           static_cast<std::size_t>(ncols[0])) == inp.size(),
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
      ass((static_cast<std::size_t>(nrows[0]) *
           static_cast<std::size_t>(ncols[0])) == inp.size(),
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

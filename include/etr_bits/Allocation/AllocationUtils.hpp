#ifndef ALLOCATION_UTILS_ETR_H
#define ALLOCATION_UTILS_ETR_H

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
#include "../BufferVector.hpp"
#include "../Core.hpp"
#include "availableHeapSize.hpp"

namespace etr {

template <typename T> inline size_t convertSize(const T &inp) {
  if constexpr (std::is_same_v<T, size_t>) {
    ass(inp >= 1, "invalid times argument");
    return inp;
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

template <typename T> inline auto createLVec(T s) {
  size_t size = convertSize(s);
  // issue: check which version is better
  // ass(size > 0 && size < ((getTotalSystemMemory()/sizeof(BaseType)) / 3),
  // "invalid length argument");
  ass(size > 0, "invalid length argument");
  return Vec<BaseType, Buffer<BaseType, BufferTrait, RBufTrait>, RVecTrait>(
      SI{size});
}

template <typename T> inline auto createRVec(T s) {
  size_t size = convertSize(s);
  // issue: check which version is better
  // ass(size > 0 && size < ((getTotalSystemMemory()/sizeof(BaseType)) / 3),
  // "invalid length argument");
  ass(size > 0, "invalid length argument");
  return Vec<BaseType, Buffer<BaseType, BufferTrait, RBufTrait>, RVecTrait>(
      SI{size});
}

} // namespace etr

#endif

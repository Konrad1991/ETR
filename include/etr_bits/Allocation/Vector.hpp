#ifndef VECTOR_ETR_H
#define VECTOR_ETR_H

#include "AllocationUtils.hpp"

namespace etr {
template <typename T> inline auto vector(const T &inp) {
  if constexpr (std::is_same_v<T, size_t>) {
    return createRVec(inp);
  } else if constexpr (std::is_floating_point_v<T>) {
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    return createRVec(inp);
  } else if constexpr (std::is_integral_v<T>) {
    return createRVec(inp);
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1, "invalid length argument");
    return createRVec(inp[0]);
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in vector");
  }
}

template <typename T> inline auto vector(T &inp) {
  if constexpr (std::is_same_v<T, size_t>) {
    return createRVec(inp);
  } else if constexpr (std::is_floating_point_v<T>) {
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    return createRVec(inp);
  } else if constexpr (std::is_integral_v<T>) {
    return createRVec(inp);
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1, "invalid length argument");
    return createRVec(inp[0]);
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in vector");
  }
}
} // namespace etr

#endif

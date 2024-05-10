#ifndef VECTOR_ETR_H
#define VECTOR_ETR_H

#include "AllocationUtils.hpp"

// TODO: implement vecotr_integer, vector_logical and vector_numeric

namespace etr {
template <typename T> inline auto vector(const T &inp) {
  if constexpr (std::is_same_v<T, std::size_t>) {
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
  if constexpr (std::is_same_v<T, std::size_t>) {
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

template <int Idx, typename AV, typename T>
inline auto vector(AV &av, const T &inp) {
  if constexpr (std::is_same_v<T, std::size_t>) {
    av.varConstants[Idx].resize(convertSize(inp));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else if constexpr (std::is_floating_point_v<T>) {
    av.varConstants[Idx].resize(convertSize(inp));
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    av.varConstants[Idx].resize(convertSize(inp));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else if constexpr (std::is_integral_v<T>) {
    av.varConstants[Idx].resize(convertSize(inp));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1, "invalid length argument");
    av.varConstants[Idx].resize(convertSize(inp[0]));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in vector");
  }
}

template <int Idx, typename AV, typename T> inline auto vector(AV &av, T &inp) {
  if constexpr (std::is_same_v<T, std::size_t>) {
    av.varConstants[Idx].resize(convertSize(inp));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else if constexpr (std::is_floating_point_v<T>) {
    av.varConstants[Idx].resize(convertSize(inp));
    warn(isDoubleInt(inp),
         "The provided size is a floating-point number with non-zero decimal "
         "places. It has been floored to the nearest integer.");
    av.varConstants[Idx].resize(convertSize(inp));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else if constexpr (std::is_integral_v<T>) {
    av.varConstants[Idx].resize(convertSize(inp));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else if constexpr (IsVecLorRorCalc<T>) {
    ass(inp.size() == 1, "invalid length argument");
    av.varConstants[Idx].resize(convertSize(inp[0]));
    Vec<BaseType, VarPointer<decltype(av), Idx, -1>, VariableTypeTrait> ret(av);
    return ret;
  } else {
    static_assert(sizeof(T) == 0, "Unsupported type in vector");
  }
}
} // namespace etr

#endif

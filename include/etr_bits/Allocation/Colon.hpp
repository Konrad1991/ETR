#ifndef COLON_ETR_H
#define COLON_ETR_H

/*
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

#include "AllocationUtils.hpp"
#include <type_traits>

namespace etr {

template <typename T> inline auto colonInternal(T start, T end) {
  if (start < end) {
    std::size_t length = convertSize(end - start + 1);
    Vec<T, Buffer<T, RBufTrait>, RVecTrait> ret(SI{length});
    std::size_t counter = 0;
    while (start <= end) {
      ret[counter] = start;
      start++;
      counter++;
    }
    return ret;
  }
  std::size_t length = convertSize(start - end + 1);
  Vec<T, Buffer<T, RBufTrait>, RVecTrait> ret(SI{length});
  std::size_t counter = 0;
  while (end <= start) {
    ret[counter] = start;
    start--;
    counter++;
  }
  return ret;
}

template <typename A, typename O>
  requires std::is_arithmetic_v<A> && std::is_arithmetic_v<O>
inline auto colon(A start, O end) {
  using DataType = std::common_type<A, O>::type;
  if constexpr (std::is_same_v<A, DataType> && std::is_same_v<O, DataType>) {
    return colonInternal(start, end);
  } else if constexpr (!std::is_same_v<A, DataType> &&
                       std::is_same_v<O, DataType>) {
    return colonInternal(static_cast<DataType>(start), end);
  } else if constexpr (std::is_same_v<A, DataType> &&
                       !std::is_same_v<O, DataType>) {
    return colonInternal(start, static_cast<DataType>(end));
  }
}

template <typename A, typename O>
  requires IsVec<A> && std::is_arithmetic_v<O>
inline auto colon(A &start, O end) {
  warn(start.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeA = ExtractDataType<A>::RetType;
  using DataType = std::common_type<DataTypeA, O>::type;
  if constexpr (std::is_same_v<DataTypeA, DataType> &&
                std::is_same_v<O, DataType>) {
    return colonInternal(start[0], end);
  } else if constexpr (!std::is_same_v<DataTypeA, DataType> &&
                       std::is_same_v<O, DataType>) {
    return colonInternal(static_cast<DataType>(start[0]), end);
  } else if constexpr (std::is_same_v<DataTypeA, DataType> &&
                       !std::is_same_v<O, DataType>) {
    return colonInternal(start[0], static_cast<DataType>(end));
  }
}

template <typename A, typename O>
  requires IsVec<A> && std::is_arithmetic_v<O>
inline auto colon(const A &start, O end) {
  warn(start.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeA = ExtractDataType<A>::RetType;
  using DataType = std::common_type<DataTypeA, O>::type;
  if constexpr (std::is_same_v<DataTypeA, DataType> &&
                std::is_same_v<O, DataType>) {
    return colonInternal(start[0], end);
  } else if constexpr (!std::is_same_v<DataTypeA, DataType> &&
                       std::is_same_v<O, DataType>) {
    return colonInternal(static_cast<DataType>(start[0]), end);
  } else if constexpr (std::is_same_v<DataTypeA, DataType> &&
                       !std::is_same_v<O, DataType>) {
    return colonInternal(start[0], static_cast<DataType>(end));
  }
}

template <typename A, typename O>
  requires std::is_arithmetic_v<A> && IsVec<O>
inline auto colon(A start, O& end) {
  warn(end.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeO = ExtractDataType<O>::RetType;
  using DataType = std::common_type<A, DataTypeO>::type;
  if constexpr (std::is_same_v<A, DataType> &&
                std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start, end[0]);
  } else if constexpr (!std::is_same_v<A, DataType> &&
                       std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(static_cast<DataType>(start), end[0]);
  } else if constexpr (std::is_same_v<A, DataType> &&
                       !std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start, static_cast<DataType>(end[0]));
  }
}

template <typename A, typename O>
  requires std::is_arithmetic_v<A> && IsVec<O>
inline auto colon(A start, const O& end) {
  warn(end.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeO = ExtractDataType<O>::RetType;
  using DataType = std::common_type<A, DataTypeO>::type;
  if constexpr (std::is_same_v<A, DataType> &&
                std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start, end[0]);
  } else if constexpr (!std::is_same_v<A, DataType> &&
                       std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(static_cast<DataType>(start), end[0]);
  } else if constexpr (std::is_same_v<A, DataType> &&
                       !std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start, static_cast<DataType>(end[0]));
  }
}

template <typename A, typename O>
  requires IsVec<A> && IsVec<O>
inline auto colon(A& start, O& end) {
  warn(end.size() == 1,
       "expression has more than one element only the first is used");
  warn(start.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeA = ExtractDataType<A>::RetType;
  using DataTypeO = ExtractDataType<O>::RetType;
  using DataType = std::common_type<DataTypeA, DataTypeO>::type;
  if constexpr (std::is_same_v<DataTypeA, DataType> &&
                std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], end[0]);
  } else if constexpr (!std::is_same_v<DataTypeA, DataType> &&
                       std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(static_cast<DataType>(start[0]), end[0]);
  } else if constexpr (std::is_same_v<DataTypeA, DataType> &&
                       !std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], static_cast<DataType>(end[0]));
  }
}

template <typename A, typename O>
  requires IsVec<A> && IsVec<O>
inline auto colon(const A& start, O& end) {
  warn(end.size() == 1,
       "expression has more than one element only the first is used");
  warn(start.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeA = ExtractDataType<A>::RetType;
  using DataTypeO = ExtractDataType<O>::RetType;
  using DataType = std::common_type<DataTypeA, DataTypeO>::type;
  if constexpr (std::is_same_v<DataTypeA, DataType> &&
                std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], end[0]);
  } else if constexpr (!std::is_same_v<DataTypeA, DataType> &&
                       std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(static_cast<DataType>(start[0]), end[0]);
  } else if constexpr (std::is_same_v<DataTypeA, DataType> &&
                       !std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], static_cast<DataType>(end[0]));
  }
}

template <typename A, typename O>
  requires IsVec<A> && IsVec<O>
inline auto colon(A& start, const O& end) {
  warn(end.size() == 1,
       "expression has more than one element only the first is used");
  warn(start.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeA = ExtractDataType<A>::RetType;
  using DataTypeO = ExtractDataType<O>::RetType;
  using DataType = std::common_type<DataTypeA, DataTypeO>::type;
  if constexpr (std::is_same_v<DataTypeA, DataType> &&
                std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], end[0]);
  } else if constexpr (!std::is_same_v<DataTypeA, DataType> &&
                       std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(static_cast<DataType>(start[0]), end[0]);
  } else if constexpr (std::is_same_v<DataTypeA, DataType> &&
                       !std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], static_cast<DataType>(end[0]));
  }
}

template <typename A, typename O>
  requires IsVec<A> && IsVec<O>
inline auto colon(const A& start, const O& end) {
  warn(end.size() == 1,
       "expression has more than one element only the first is used");
  warn(start.size() == 1,
       "expression has more than one element only the first is used");
  using DataTypeA = ExtractDataType<A>::RetType;
  using DataTypeO = ExtractDataType<O>::RetType;
  using DataType = std::common_type<DataTypeA, DataTypeO>::type;
  if constexpr (std::is_same_v<DataTypeA, DataType> &&
                std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], end[0]);
  } else if constexpr (!std::is_same_v<DataTypeA, DataType> &&
                       std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(static_cast<DataType>(start[0]), end[0]);
  } else if constexpr (std::is_same_v<DataTypeA, DataType> &&
                       !std::is_same_v<DataTypeO, DataType>) {
    return colonInternal(start[0], static_cast<DataType>(end[0]));
  }
}

} // namespace etr

#endif

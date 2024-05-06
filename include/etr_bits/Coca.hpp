#ifndef COCA_ETR_H
#define COCA_ETR_H

#include "BufferVector.hpp"
#include "Core.hpp"
#include "Core/Reflection.hpp"
#include <type_traits>

namespace etr {

inline auto determine_type(const auto &rest) {
  using restType = std::remove_reference<decltype(rest)>::type;
  if constexpr (std::is_arithmetic_v<restType>) {
    return typename std::remove_reference<decltype(rest)>::type{};
  } else {
    using tD = ExtractedTypeD<restType>;
    return typename ExtractDataType<tD>::RetType{};
  }
};

inline auto determine_type(const auto &first, const auto &rest) {
  using firstType = std::remove_reference<decltype(first)>::type;
  using restType = std::remove_reference<decltype(rest)>::type;
  if constexpr (std::is_arithmetic_v<firstType> &&
                std::is_arithmetic_v<restType>) {
    return typename std::common_type<firstType, restType>::type{};
  } else if constexpr (!std::is_arithmetic_v<firstType> &&
                       std::is_arithmetic_v<restType>) {
    using tD = ExtractedTypeD<firstType>;
    using firstInner = ExtractDataType<tD>::RetType;
    return typename std::common_type<firstInner, restType>::type{};
  } else if constexpr (std::is_arithmetic_v<firstType> &&
                       !std::is_arithmetic_v<restType>) {
    using tD = ExtractedTypeD<restType>;
    using restInner = ExtractDataType<tD>::RetType;
    return typename std::common_type<firstType, restInner>::type{};
  } else if constexpr (!std::is_arithmetic_v<firstType> &&
                       !std::is_arithmetic_v<restType>) {
    using tD1 = ExtractedTypeD<firstType>;
    using firstInner = ExtractDataType<tD1>::RetType;
    using tD2 = ExtractedTypeD<restType>;
    using restInner = ExtractDataType<tD2>::RetType;
    return typename std::common_type<firstInner, restInner>::type{};
  }
}

inline auto determine_type(const auto &first, const auto &...rest) {
  using firstType = std::remove_reference<decltype(first)>::type;
  using restType = decltype(determine_type(rest...));
  return restType{};
}

// NOTE: isnt it possible to use the function etr::c instead of etr::coca

template <class F, class... Args> inline F forEachArg(F f, Args &&...args) {
  (f(std::forward<Args>(args)), ...);
  return f;
}

template <typename... Args> inline auto coca(Args &&...args) {
  using cType = decltype(determine_type(args...));
  int size = 0;
  forEachArg(
      [&](auto arg) {
        if constexpr (std::is_arithmetic_v<decltype(arg)>) {
          size++;
        } else {
          size += arg.size();
        }
      },
      args...);

  Vec<cType, Buffer<cType, BufferTrait, RBufTrait>, RVecTrait> ret(SI{size});
  std::size_t index = 0;

  forEachArg(
      [&](auto arg) {
        if constexpr (std::is_arithmetic_v<decltype(arg)>) {
          if constexpr (std::is_same_v<decltype(arg), cType>) {
            ret[index] = arg;
          } else {
            ret[index] = static_cast<cType>(arg);
          }
          index++;
        } else {
          using tD = ExtractedTypeD<decltype(arg)>;
          using InnerType = ExtractDataType<tD>::RetType;
          if constexpr (std::is_same_v<InnerType, cType>) {
            for (int i = 0; i < arg.size(); i++) {
              ret[index + i] = arg[i];
            }
          } else {
            for (int i = 0; i < arg.size(); i++) {
              ret[index + i] = static_cast<cType>(arg[i]);
            }
          }
          index += arg.size();
        }
      },
      args...);
  return ret;
}

} // namespace etr

#endif

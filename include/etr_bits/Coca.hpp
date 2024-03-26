#ifndef COCA_ETR_H
#define COCA_ETR_H

#include "BufferVector.hpp"
#include "Core.hpp"

namespace etr {

template <class F, class... Args> inline F forEachArg(F f, Args &&...args) {
  (f(std::forward<Args>(args)), ...);
  return f;
}

template <typename... Args> inline Vec<BaseType> coca(Args &&...args) {
  int size = 0;
  forEachArg(
      [&](auto arg) {
        if constexpr (std::is_same<decltype(arg), int>::value) {
          size++;
        } else if constexpr (std::is_same<decltype(arg), double>::value) {
          size++;
        } else if constexpr (std::is_same<decltype(arg), bool>::value) {
          size++;
        } else {
          size += arg.size();
        }
      },
      args...);

  Vec<BaseType> ret(SI{size});
  size_t index = 0;

  forEachArg(
      [&](auto arg) {
        if constexpr (std::is_same<decltype(arg), int>::value) {
          ret[index] = static_cast<BaseType>(arg);
          index++;
        } else if constexpr (std::is_same<decltype(arg), double>::value) {
          ret[index] = arg;
          index++;
        } else if constexpr (std::is_same<decltype(arg), bool>::value) {
          ret[index] = static_cast<BaseType>(arg);
          ;
          index++;
        } else {
          for (int i = 0; i < arg.size(); i++) {
            ret[index + i] = arg[i];
          }
          index += arg.size();
        }
      },
      args...);
  return ret;
}

} // namespace etr

#endif
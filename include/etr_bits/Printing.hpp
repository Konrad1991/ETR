#ifndef PRINT_ETR_H
#define PRINT_ETR_H

#include "BufferVector.hpp"
#include "Core.hpp"

namespace etr {
#ifdef STANDALONE_ETR
#define PRINT_STREAM std::cout
#else
#define PRINT_STREAM PRINT_STREAM
#endif

inline void print() { PRINT_STREAM << std::endl; }

template <typename T>
  requires isBID<T>
inline void print(const T &inp) {
  if constexpr (std::is_same_v<T, bool>) {
    PRINT_STREAM << std::boolalpha << inp << " ";
  } else {
    PRINT_STREAM << inp << std::endl;
  }
  PRINT_STREAM << std::endl;
}

inline void print(const char *inp) {
  if constexpr (std::is_same_v<T, bool>) {
    PRINT_STREAM << inp << " ";
  } else {
    PRINT_STREAM << inp << std::endl;
  }
  PRINT_STREAM << std::endl;
}

template <typename L, typename R>
  requires NotOperation<R>
inline void print(const Vec<L, R> &inp) {
  if (!inp.im()) {
    for (size_t i = 0; i < inp.size(); i++)
      PRINT_STREAM << std::boolalpha << inp[i] << " ";
    PRINT_STREAM << std::endl;
  } else {
    for (size_t i = 0; i < inp.nr(); i++) {
      for (size_t j = 0; j < inp.nc(); j++) {
        PRINT_STREAM << inp[j * inp.nr() + i] << "\t";
      }
      PRINT_STREAM << std::endl;
    }
  }
}

template <typename T, typename Op, typename Trait>
  requires UnaryOrBinaryOperation<Op>
inline void print(const etr::Vec<T, Op, Trait> &inp) {
  if (!inp.im()) {
    for (size_t i = 0; i < inp.size(); i++)
      PRINT_STREAM << std::boolalpha << inp[i] << " ";
    PRINT_STREAM << std::endl;
  } else {
    for (size_t i = 0; i < inp.nr(); i++) {
      for (size_t j = 0; j < inp.nc(); j++) {
        PRINT_STREAM << inp[j * inp.nr() + i] << "\t";
      }
      PRINT_STREAM << std::endl;
    }
  }
}

template <typename T> // issue: unnecessary new line
  requires(!isBID<T>)
inline void
print(const T &inp) { // issue: just a quick fix for printing unary expression
  if (!inp.im()) {
    for (size_t i = 0; i < inp.size(); i++)
      PRINT_STREAM << std::boolalpha << inp[i] << " ";
    PRINT_STREAM << std::endl;
  } else {
    for (size_t i = 0; i < inp.nr(); i++) {
      for (size_t j = 0; j < inp.nc(); j++) {
        PRINT_STREAM << inp[j * inp.nr() + i] << "\t";
      }
      PRINT_STREAM << std::endl;
    }
  }
}

} // namespace etr

#endif

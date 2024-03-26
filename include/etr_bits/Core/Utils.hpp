#ifndef UTILS_ETR_H
#define UTILS_ETR_H

#include "Header.hpp"

namespace etr {

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type CommonType(T1 arg1, T2 arg2) {
  return arg1 + arg2; // Fake function just for getting the common type
}

template <typename T> inline bool isDoubleInt(const T d) {
  int i = d;
  if ((d - i) > 0) {
    return false;
  }
  return true;
}

typedef double BaseType;

template <bool B> using BoolConstant = std::integral_constant<bool, B>;
using TRUE = BoolConstant<true>;
using T = BoolConstant<true>;
using FALSE = BoolConstant<false>;
using F = BoolConstant<false>;

#ifdef STANDALONE_ETR
const double NA_REAL = std::numeric_limits<double>::quiet_NaN();
const double R_PosInf = std::numeric_limits<double>::infinity();
#endif

inline int d2i(double inp) { return static_cast<int>(inp); }

inline double i2d(int inp) { return static_cast<double>(inp); }

inline bool d2b(double inp) { return static_cast<bool>(inp); }

inline bool i2b(double inp) { return static_cast<bool>(inp); }

inline double b2d(bool inp) { return static_cast<double>(inp); }

template <typename T> struct It {
  T *p;
  T &operator*() { return *p; }
  bool operator!=(const It &rhs) { return p != rhs.p; }
  void operator++() { ++p; }
};

inline void ass(bool inp, std::string message) {
#ifdef STANDALONE_ETR
  if (!inp)
    throw std::runtime_error(message);
#else
  if (!inp)
    Rcpp::stop(message);
#endif
}

inline void warn(bool inp, std::string message) {
#ifdef STANDALONE_ETR
  if (!inp)
    std::cerr << "Warning: " + message << std::endl;
#else
  if (!inp)
    Rcpp::warning("Warning: " + message);
#endif
}

} // namespace etr

#endif
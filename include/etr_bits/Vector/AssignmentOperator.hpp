#ifndef ASSING2VEC_ETR_H
#define ASSING2VEC_ETR_H

#include "VectorClass.hpp"
#include <type_traits>

template <typename TD>
  requires std::is_arithmetic_v<TD>
Vec &operator=(const TD inp) {
  // std::cout << "test1" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  static_assert(!isRVec::value,
                "Cannot assign to an r value. E.g. c(1, 2, 3) <- 1");
  if constexpr (is<TD, T>) {
    if constexpr (isSubset::value) {
      for (std::size_t i = 0; i < d.ind.size(); i++) {
        d[i] = inp;
      }
    } else if constexpr (isBorrow::value) {
      d.sz = 1;
      d[0] = inp;
    } else {
      d.resize(1);
      d[0] = inp;
    }
    return *this;
  } else {
    if constexpr (isSubset::value) {
      for (std::size_t i = 0; i < d.ind.size(); i++) {
        d[i] = static_cast<T>(inp);
      }
    } else if constexpr (isBorrow::value) {
      d.sz = 1;
      d[0] = static_cast<T>(inp);
    } else {
      d.resize(1);
      d[0] = static_cast<T>(inp);
    }
    return *this;
  }
}

Vec &operator=(const Vec<T, R, Trait> &otherVec) {
  // std::cout << "test2" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  static_assert(!isRVec::value,
                "Cannot assign to an r value. E.g. c(1, 2, 3) <- 1");

  using DataTypeOtherVec = typename etr::ExtractDataType<
      std::remove_reference_t<decltype(otherVec)>>::RetType;
  if constexpr (isBuffer::value) {
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    d.moveit(temp);
  } else if constexpr (isBorrow::value) {
    ass(otherVec.size() <= d.capacity,
        "number of items to replace is not a multiple of replacement length");
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    ass(d.sz <= otherVec.size(),
        "size cannot be increased above the size of the borrowed object");
    d.sz = otherVec.size();
    for (std::size_t i = 0; i < otherVec.size(); i++)
      d[i] = temp[i];
  } else if constexpr (isBorrowSEXP::value) {
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    if (otherVec.size() > this->size())
      d.resize(otherVec.size());
    d.moveit(temp);
  } else if constexpr (isSubset::value) {
    ass(otherVec.size() == d.ind.size(),
        "number of items to replace is not a multiple of replacement length");
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    if (d.p->size() < temp.size())
      d.resize(temp.size());
    for (std::size_t i = 0; i < d.ind.size(); i++) {
      d[i % d.ind.size()] = temp[i];
    }
  }
  if (otherVec.d.im()) {
    d.setMatrix(true, otherVec.d.nr(), otherVec.d.nc());
  }
  return *this;
}

template <typename T2, typename R2, typename Trait2>
Vec &operator=(const Vec<T2, R2, Trait2> &otherVec) {
  // std::cout << "test3" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  static_assert(!isRVec::value,
                "Cannot assign to an r value. E.g. c(1, 2, 3) <- 1");
  using DataTypeOtherVec = typename etr::ExtractDataType<
      std::remove_reference_t<decltype(otherVec)>>::RetType;
  if constexpr (isBuffer::value) {
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    d.moveit(temp);
  } else if constexpr (isBorrow::value) {
    ass(otherVec.size() <= d.capacity,
        "number of items to replace is not a multiple of replacement length");
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    d.sz = otherVec.size();
    for (std::size_t i = 0; i < otherVec.size(); i++)
      d[i] = temp[i];
  } else if constexpr (isBorrowSEXP::value) {
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    if (otherVec.size() > this->size())
      d.resize(otherVec.size());
    d.moveit(temp);
  } else if constexpr (isSubset::value) {
    ass(otherVec.size() == d.ind.size(),
        "number of items to replace is not a multiple of replacement length");
    temp.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      if constexpr (is<DataTypeOtherVec, T>) {
        temp[i] = otherVec[i];
      } else {
        temp[i] = static_cast<T>(otherVec[i]);
      }
    }
    for (std::size_t i = 0; i < d.ind.size(); i++) {
      d[i % d.ind.size()] = temp[i];
    }
  }
  if (otherVec.d.im()) {
    d.setMatrix(true, otherVec.d.nr(), otherVec.d.nc());
  }
  return *this;
}

#ifdef STANDALONE_ETR
#else
Vec &operator=(SEXP s) {
  d.initSEXP(s);
  return *this;
}
#endif
#endif

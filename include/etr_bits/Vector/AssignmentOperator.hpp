#ifndef ASSING2VEC_ETR_H
#define ASSING2VEC_ETR_H

#include "VectorClass.hpp"

template <typename TD>
  requires std::is_same_v<TD, T>
Vec &operator=(const TD inp) {
  // std::cout << "test1" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
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
}

template <typename TD>
  requires std::is_same_v<TD, int>
Vec &operator=(const TD inp) {
  // std::cout << "operator= test2" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  if constexpr (isSubset::value) {
    for (std::size_t i = 0; i < d.ind.size(); i++) {
      d[i] = static_cast<BaseType>(inp);
    }
  } else if constexpr (isBorrow::value) {
    d.sz = 1;
    d[0] = static_cast<BaseType>(inp);
  } else if constexpr (isVarPointer::value) {
    d.resize(1);
    d[0] = inp;
  } else {
    d.resize(1);
    d[0] = static_cast<BaseType>(inp);
  }
  return *this;
}

template <typename TD>
  requires std::is_same_v<TD, bool>
Vec &operator=(const TD inp) {
  // std::cout << "operator= test3" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  if constexpr (isSubset::value) {
    for (std::size_t i = 0; i < d.ind.size(); i++) {
      d[i] = static_cast<BaseType>(inp);
    }
  } else if constexpr (isBorrow::value) {
    d.sz = 1;
    d[0] = static_cast<BaseType>(inp);
  } else {
    d.resize(1);
    d[0] = static_cast<BaseType>(inp);
  }
  return *this;
}

Vec &operator=(Vec<BaseType> &other) {
  // std::cout << "test4" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  if constexpr (isSubset::value) {
    ass(other.size() == d.ind.size(),
        "number of items to replace is not a multiple of replacement length");
    for (std::size_t i = 0; i < d.ind.size(); i++) {
      d[i] = other[i];
    }
  } else {
    if (size() != other.size()) {
      resize(other.size());
      for (std::size_t i = 0; i < other.size(); i++)
        d[i] = other[i];
    }
  }
  if (other.d.im()) {
    d.setMatrix(true, other.d.nr(), other.d.nc()); // issue: correct?
  }
  return *this;
}

Vec &operator=(const Vec<T, R, Trait> &otherVec) {
  // std::cout << "test5" << std::endl;
  // printTAST<decltype(otherVec)>();
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  if constexpr (isBuffer::value) {
    Buffer<T> temp(otherVec.size()); // issue: create Buffer<T> as attribute
    for (std::size_t i = 0; i < otherVec.size(); i++)
      temp[i] = otherVec[i];
    d.moveit(temp);
  } else if constexpr (isBorrow::value) {
    ass(otherVec.size() <= d.capacity,
        "number of items to replace is not a multiple of replacement length");
    Buffer<T> temp(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++)
      temp[i] = otherVec[i];
    d.sz = otherVec.size();
    for (std::size_t i = 0; i < otherVec.size(); i++)
      d[i] = temp[i];
  } else if constexpr (isBorrowSEXP::value) {
    Buffer<T> temp(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++)
      temp[i] = otherVec[i];
    if (otherVec.size() > this->size())
      d.resize(otherVec.size());
    d.moveit(temp);
  } else if constexpr (isSubset::value) {
    ass(otherVec.size() == d.ind.size(),
        "number of items to replace is not a multiple of replacement length");
    Buffer<T> temp(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      temp[i] = otherVec[i];
    }
    if (d.p->size() < temp.size())
      d.resize(temp.size());
    for (std::size_t i = 0; i < d.ind.size(); i++) {
      d[i % d.ind.size()] = temp[i];
    }
  }
  if (otherVec.d.im()) { // issue:  && !d.im() missing?
    d.setMatrix(true, otherVec.d.nr(), otherVec.d.nc());
  }
  return *this;
}

template <typename T2, typename R2, typename Trait2>
Vec &operator=(const Vec<T2, R2, Trait2> &otherVec) {
  // std::cout << "test6" << std::endl;
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  if constexpr (isBuffer::value) {
    Buffer<T> temp(otherVec.size()); // issue: define temp as own attribute!
    using RetTypeOtherVec =
        std::remove_reference<decltype(otherVec.d)>::type::RetType;
    using isBaseTypeRet = std::is_same<RetTypeOtherVec, BaseType>;
    if constexpr (isBaseTypeRet::value) {
      for (std::size_t i = 0; i < otherVec.size(); i++) {
        temp[i] = otherVec[i];
      }
    } else {
      for (std::size_t i = 0; i < otherVec.size(); i++) {
        temp[i] = static_cast<BaseType>(otherVec[i]);
      }
    }
    d.moveit(temp);
  } else if constexpr (isBorrow::value) {
    ass(otherVec.size() <= d.capacity,
        "number of items to replace is not a multiple of replacement length");
    Buffer<T> temp(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++)
      temp[i] = otherVec[i];
    d.sz = otherVec.size();
    for (std::size_t i = 0; i < otherVec.size(); i++)
      d[i] = temp[i];
  } else if constexpr (isBorrowSEXP::value) {
    Buffer<T> temp(otherVec.size());
    using RetTypeOtherVec =
        std::remove_reference<decltype(otherVec.d)>::type::RetType;
    using isBaseTypeRet = std::is_same<RetTypeOtherVec, BaseType>;
    if constexpr (isBaseTypeRet::value) {
      for (std::size_t i = 0; i < otherVec.size(); i++) {
        temp[i] = otherVec[i];
      }
    } else {
      for (std::size_t i = 0; i < otherVec.size(); i++) {
        temp[i] = static_cast<BaseType>(otherVec[i]);
      }
    }
    if (otherVec.size() > this->size())
      d.resize(otherVec.size());
    d.moveit(temp);
  } else if constexpr (isSubset::value) {
    ass(otherVec.size() == d.ind.size(),
        "number of items to replace is not a multiple of replacement length");
    Buffer<T> temp(otherVec.size());
    using RetTypeOtherVec =
        std::remove_reference<decltype(otherVec.d)>::type::RetType;
    using isBaseTypeRet = std::is_same<RetTypeOtherVec, BaseType>;
    if constexpr (isBaseTypeRet::value) {
      for (std::size_t i = 0; i < otherVec.size(); i++) {
        temp[i] = otherVec[i];
      }
    } else {
      for (std::size_t i = 0; i < otherVec.size(); i++) {
        temp[i] = static_cast<BaseType>(otherVec[i]);
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

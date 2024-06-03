#ifndef ASSING2VEC_ETR_H
#define ASSING2VEC_ETR_H

#include "VectorClass.hpp"
#include <type_traits>

/*
template <typename TD> Vec &operator=(const TD &&otherVec) {
  static_assert(!isUnaryOP::value, "Cannot assign to unary calculation");
  static_assert(!isBinaryOP::value, "Cannot assign to binary calculation");
  static_assert(!isRVec::value,
                "Cannot assign to a r value. E.g. c(1, 2, 3) <- 3");
  // NOTE: arithmetic otherVecut
  if constexpr (std::is_arithmetic_v<TD>) {
    if constexpr (is<T, TD>) {
      // NOTE: T == TD
      if constexpr (isSubset::value) {
        for (std::size_t i = 0; i < d.ind.size(); i++) {
          d[i] = otherVec;
        }
      } else if constexpr (isBorrow::value) {
        d.sz = 1;
        d[0] = otherVec;
      } else {
        d.resize(1);
        d[0] = otherVec;
      }
      // NOTE: T != TD
    } else {

      if constexpr (isSubset::value) {
        for (std::size_t i = 0; i < d.ind.size(); i++) {
          d[i] = static_cast<T>(otherVec);
        }
      } else if constexpr (isBorrow::value) {
        d.sz = 1;
        d[0] = static_cast<T>(otherVec);
      } else {
        d.resize(1);
        d[0] = static_cast<T>(otherVec);
      }
    }
  } else { // NOTE: vector otherVecut
    using RetTypeOtherVec =
        std::remove_reference<decltype(otherVec.d)>::type::RetType;
    using isT = std::is_same<RetTypeOtherVec, T>;

    if constexpr (isBuffer::value) {
      temp.resize(otherVec.size());
      if constexpr (isT::value) {
        for (std::size_t i = 0; i < otherVec.size(); i++) {
          temp[i] = otherVec[i];
        }
      } else {
        for (std::size_t i = 0; i < otherVec.size(); i++) {
          temp[i] = static_cast<T>(otherVec[i]);
        }
      }
      d.moveit(temp);
    } else if constexpr (isBorrow::value) {
      ass(otherVec.size() <= d.capacity,
          "number of items to replace is not a multiple of replacement length");
      temp.resize(otherVec.size());
      for (std::size_t i = 0; i < otherVec.size(); i++)
        temp[i] = otherVec[i];
      d.sz = otherVec.size();
      for (std::size_t i = 0; i < otherVec.size(); i++)
        d[i] = temp[i];
    } else if constexpr (isBorrowSEXP::value) {
      temp.resize(otherVec.size());
      if constexpr (isT::value) {
        for (std::size_t i = 0; i < otherVec.size(); i++) {
          temp[i] = otherVec[i];
        }
      } else {
        for (std::size_t i = 0; i < otherVec.size(); i++) {
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
      if constexpr (isT::value) {
        for (std::size_t i = 0; i < otherVec.size(); i++) {
          temp[i] = otherVec[i];
        }
      } else {
        for (std::size_t i = 0; i < otherVec.size(); i++) {
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
  }

  return *this;
}
*/

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

template <typename LT, typename RT, typename LDeriv, typename RDeriv,
          typename TraitTD, typename OpTrait>
static constexpr QuarternyType<LT, RT, LDeriv, RDeriv, TraitTD, OpTrait>
produceQuarternyType() {
  return QuarternyType<LT, RT, LDeriv, RDeriv, TraitTD, OpTrait>();
}

template <typename LDeriv, typename RDeriv, typename TraitTD, typename OpTrait>
static constexpr BinaryType<LDeriv, RDeriv, TraitTD, OpTrait>
produceBinaryType() {
  return BinaryType<LDeriv, RDeriv, TraitTD, OpTrait>();
}

template <typename I, typename TraitTD, typename OpTrait>
static constexpr UnaryType<I, TraitTD, OpTrait> produceUnaryType() {
  return UnaryType<I, TraitTD, OpTrait>(); // issue: wrong wrong wrong
}

template <typename TRaw> static constexpr auto produceVariableType() {
  using TD = std::remove_reference_t<TRaw>;
  if constexpr (IsVec<TD>) {
    using tD = ExtractedTypeD<TD>;
    return VariableType<tD>();
  } else {
    return VariableType<TRaw>();
  }
}

template <typename TD>
  requires IsVarPointer<TD>
static constexpr auto walkTD() -> VariableType<TD> {
  static_assert(!IsVec<TD>, "Cannot create derivative expression tree");
  return VariableType<TD>();
}

template <typename TD>
  requires IsConstant<TD>
static constexpr auto walkTD() {
  return Constants<typename TD::Type, TD::I, ConstantTypeTrait>{};
}

template <typename TRaw>
  requires IsMultiplication<TRaw>
static constexpr auto walkTD() {
  using TDMultiplication = std::remove_const_t<std::remove_reference_t<TRaw>>;
  constexpr auto LT =
      produceVariableType<typename TDMultiplication::typeTraitL>();
  constexpr auto RT =
      produceVariableType<typename TDMultiplication::typeTraitR>();
  constexpr auto LDeriv = walkTD<typename TDMultiplication::typeTraitL>();
  constexpr auto RDeriv = walkTD<typename TDMultiplication::typeTraitR>();
  return produceQuarternyType<decltype(LT), decltype(RT), decltype(LDeriv),
                              decltype(RDeriv), QuarternaryTrait,
                              TimesDerivTrait>();
}

template <typename TD>
  requires IsAddition<TD>
static constexpr auto walkTD() {
  constexpr auto LDeriv = walkTD<typename TD::typeTraitL>();
  constexpr auto RDeriv = walkTD<typename TD::typeTraitR>();
  return produceBinaryType<decltype(LDeriv), decltype(RDeriv), BinaryTrait,
                           PlusDerivTrait>();
}

template <typename TD>
  requires IsSinus<TD>
static constexpr auto walkTD() {
  constexpr auto obj = walkTD<typename TD::typeTraitObj>();
  return produceUnaryType<decltype(obj), UnaryTrait, SinusDerivTrait>();
}

template <typename TD>
  requires(IsVec<TD> && !IsVariable<TD>)
static constexpr auto walkTD() {
  using TDVec = ExtractedTypeD<TD>;
  constexpr auto res = walkTD<TDVec>();
  return res;
}

// TODO: finish this
template <typename T2, typename R2, typename Trait2>
Vec &operator<<(const Vec<T2, R2, Trait2> &otherVec) {
  using tD = decltype(otherVec.d);
  if constexpr (IsVarPointer<tD> && IsVarPointer<DType>) {
    d.resize(otherVec.size());
    for (std::size_t i = 0; i < d.size(); i++) {
      d.setVal(otherVec.d.AllVarsRef, i, tD::getVal(otherVec.d.AllVarsRef, i));
    }
  } else if constexpr (IsVarPointer<tD> && !IsVarPointer<DType>) {
    d.resize(otherVec.size());
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = otherVec[i];
    }
  } else if constexpr (!IsVarPointer<tD> && IsVarPointer<DType>) {
    using tDRaw = std::remove_reference<decltype(otherVec)>::type;
    using typeExpr = std::remove_reference<ExtractedTypeD<tDRaw>>::type;
    /* printTAST<typeExpr>(); */
    constexpr auto res = walkTD<typeExpr>();
    /* printTAST<decltype(res)>(); */
    d.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      d.AllVarsRef.varBuffer[d.I][i] = otherVec[i];
    }

    d.AllVarsRef.resizeDerivs(R::I, R::TIdx, otherVec.size());
    for (std::size_t i = 0; i < res.getSize(d.AllVarsRef); i++) {
      d.setDeriv(d.AllVarsRef, i, res.getDeriv(d.AllVarsRef, i));
    }

  } else if constexpr (!IsVarPointer<tD> && !IsVarPointer<DType>) {
    d.resize(otherVec.size());
    for (std::size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
  }
  return *this;
}

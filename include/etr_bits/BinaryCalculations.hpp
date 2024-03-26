#ifndef BINARYOPERATION
#define BINARYOPERATION

#include "Core.hpp"

// issue: what is needed in order that for loops work with Operations
/*
RetType* p;
auto begin() const {
  return It<RetType>{p};
}
auto end() const {
  return It<RetType>{p + this -> size()};
}
*/

namespace etr {

template <typename L, typename R, typename Trait, typename CTrait>
struct BinaryOperation {
  using Type = DoubleTrait;
  using TypeTrait = Trait;
  using CaseTrait = BinaryTrait;
  using RetType = typename CTrait::RetType;
  const L &l;
  const R &r;
  using typeTraitL = L;
  using typeTraitR = R;
  MatrixParameter mp;
  bool im() const { return mp.im(); }
  size_t nc() const { return mp.nc(); }
  size_t nr() const { return mp.nr(); }
  BinaryOperation(const BinaryOperation &other)
      : l(other.l), r(other.r), mp(other.mp) {}
  BinaryOperation(const BinaryOperation &&other)
      : l(std::move(other.l)), r(std::move(other.r)), mp(std::move(other.mp)) {}
  BinaryOperation(const L &l_, const R &r_, const MatrixParameter &mp_)
      : l(l_), r(r_), mp(mp_) {}
  template <typename LType, typename RType, typename TraitOther>
  BinaryOperation(const BinaryOperation<LType, RType, TraitOther>
                      &other) // issue: needs move constructor
      : l(other.l), r(other.r), mp(other.mp) {}

  auto operator[](size_t i)
      const { // RetType is not suitable as int / int -_> should return a
              // double. How to handle this in detection of RetType?
    constexpr bool isDoubleL = std::is_arithmetic_v<L>;
    constexpr bool isDoubleR = std::is_arithmetic_v<R>;
    if constexpr (!isDoubleL && isDoubleR) {
      return Trait::f(l[i % l.size()], r);
    } else if constexpr (isDoubleL && !isDoubleR) {
      return Trait::f(l, r[i % r.size()]);
    } else if constexpr (!isDoubleL && !isDoubleR) {
      return Trait::f(l[i % l.size()], r[i % r.size()]);
    }
  }
  size_t size() const {
    constexpr bool isDoubleL = std::is_arithmetic_v<L>;
    constexpr bool isDoubleR = std::is_arithmetic_v<R>;
    if constexpr (isDoubleL && isDoubleR) {
      return 1;
    } else if constexpr (!isDoubleL && isDoubleR) {
      return l.size();
    } else if constexpr (isDoubleL && !isDoubleR) {
      return r.size();
    } else if constexpr (!isDoubleL && !isDoubleR) {
      return l.size() > r.size() ? l.size() : r.size();
    }
  }
  void setMatrix(bool i, size_t nrow, size_t ncol) {
    mp.setMatrix(i, nrow, ncol);
  }
  void setMatrix(MatrixParameter &mp_) {
    mp.setMatrix(mp_.ismatrix, mp_.rows, mp_.cols);
  }
  void setMatrix(const MatrixParameter &mp_) {
    mp.setMatrix(mp_.ismatrix, mp_.rows, mp_.cols);
  }

  template <typename AV> static size_t getSize(AV &av) {
    using TyL = typename std::remove_reference<typeTraitL>::type;
    using TyR = typename std::remove_reference<typeTraitR>::type;
    return TyL::getSize(av) > TyR::getSize(av) ? TyL::getSize(av)
                                               : TyR::getSize(av);
  }
  template <typename AV>
  static RetType getVal(
      AV &av,
      size_t VecIdx) { // issue: how to handle scalar types? Or temporary types?
    using TyL = typename std::remove_reference<typeTraitL>::type;
    using TyR = typename std::remove_reference<typeTraitR>::type;
    return f(TyL::template getVal<AV>(av, VecIdx % TyL::getSize(av)),
             TyR::template getVal<AV>(av, VecIdx % TyR::getSize(av)));
  }
};

template <typename L, typename R> auto operator+(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, PlusTrait>>(
        BinaryOperation<decltype(l.d), R, PlusTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), PlusTrait>>(
        BinaryOperation<L, decltype(r.d), PlusTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), PlusTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), PlusTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator-(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, MinusTrait>>(
        BinaryOperation<decltype(l.d), R, MinusTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), MinusTrait>>(
        BinaryOperation<L, decltype(r.d), MinusTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), MinusTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), MinusTrait>(l.d, r.d,
                                                                  mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator*(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, TimesTrait>>(
        BinaryOperation<decltype(l.d), R, TimesTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), TimesTrait>>(
        BinaryOperation<L, decltype(r.d), TimesTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), TimesTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), TimesTrait>(l.d, r.d,
                                                                  mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator/(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, DivideTrait>>(
        BinaryOperation<decltype(l.d), R, DivideTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), DivideTrait>>(
        BinaryOperation<L, decltype(r.d), DivideTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), DivideTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), DivideTrait>(l.d, r.d,
                                                                   mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator^(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, PowTrait>>(
        BinaryOperation<decltype(l.d), R, PowTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), PowTrait>>(
        BinaryOperation<L, decltype(r.d), PowTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), PowTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), PowTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator==(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, EqualTrait>>(
        BinaryOperation<decltype(l.d), R, EqualTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), EqualTrait>>(
        BinaryOperation<L, decltype(r.d), EqualTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), EqualTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d),

                        EqualTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator!=(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, UnEqualTrait>>(
        BinaryOperation<decltype(l.d), R, UnEqualTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), UnEqualTrait>>(
        BinaryOperation<L, decltype(r.d), UnEqualTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), UnEqualTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d),

                        UnEqualTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator>(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, LargerTrait>>(
        BinaryOperation<decltype(l.d), R, LargerTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), LargerTrait>>(
        BinaryOperation<L, decltype(r.d), LargerTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), LargerTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d),

                        LargerTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator>=(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, LargerEqualTrait>>(
        BinaryOperation<decltype(l.d), R, LargerEqualTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), LargerEqualTrait>>(
        BinaryOperation<L, decltype(r.d), LargerEqualTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), LargerEqualTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d),

                        LargerEqualTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator<(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, SmallerTrait>>(
        BinaryOperation<decltype(l.d), R, SmallerTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), SmallerTrait>>(
        BinaryOperation<L, decltype(r.d), SmallerTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), SmallerTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d),

                        SmallerTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

template <typename L, typename R> auto operator<=(const L &l, const R &r) {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<typename ExtractDataType<L>::RetType,
                                         R>::type,
               BinaryOperation<decltype(l.d), R, SmallerEqualTrait>>(
        BinaryOperation<decltype(l.d), R, SmallerEqualTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<typename std::common_type<
                   L, typename ExtractDataType<R>::RetType>::type,
               BinaryOperation<L, decltype(r.d), SmallerEqualTrait>>(
        BinaryOperation<L, decltype(r.d), SmallerEqualTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<
        typename std::common_type<typename ExtractDataType<L>::RetType,
                                  typename ExtractDataType<R>::RetType>::type,
        BinaryOperation<decltype(l.d), decltype(r.d), SmallerEqualTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d),

                        SmallerEqualTrait>(l.d, r.d, mp));
  } else {
    ass(false, "This case should not be reached. Contact author");
  }
}

} // namespace etr

#endif

#ifndef BINARYOPERATION
#define BINARYOPERATION

#include "UtilsTraits.hpp"

namespace etr {

template <typename L, typename R, binaryFct f, typename Trait, typename CTrait>
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
  template <typename LType, typename RType, binaryFct fOther,
            typename TraitOther>
  BinaryOperation(const BinaryOperation<LType, RType, fOther, TraitOther>
                      &other) // issue: needs move constructor
      : l(other.l), r(other.r), mp(other.mp) {}
  RetType operator[](size_t i) const {
    constexpr bool isDoubleL = std::is_arithmetic_v<L>;
    constexpr bool isDoubleR = std::is_arithmetic_v<R>;
    if constexpr (isDoubleL && isDoubleR) {
      if constexpr (std::is_same_v<CTrait, ComparisonTrait>) {
        return Trait::f(l, r);
      } else {
        return f(l, r);
      }
    } else if constexpr (!isDoubleL && isDoubleR) {
      if constexpr (std::is_same_v<CTrait, ComparisonTrait>) {
        return Trait::f(l[i % l.size()], r);
      } else {
        return f(l[i % l.size()], r);
      }
    } else if constexpr (isDoubleL && !isDoubleR) {
      if constexpr (std::is_same_v<CTrait, ComparisonTrait>) {
        return Trait::f(l, r[i % r.size()]);
      } else {
        return f(l, r[i % r.size()]);
      }
    } else if constexpr (!isDoubleL && !isDoubleR) {
      if constexpr (std::is_same_v<CTrait, ComparisonTrait>) {
        return Trait::f(l[i % l.size()], r[i % r.size()]);
      } else {
        return f(l[i % l.size()], r[i % r.size()]);
      }
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
  template <typename AV> static RetType getVal(AV &av, size_t VecIdx) { // issue: how to handle scalar types? Or temporary types?
    using TyL = typename std::remove_reference<typeTraitL>::type;
    using TyR = typename std::remove_reference<typeTraitR>::type;
    return f(TyL::template getVal<AV>(av, VecIdx % TyL::getSize(av)),
             TyR::template getVal<AV>(av, VecIdx % TyR::getSize(av)) );  
  }
};

template <typename L, typename R>
auto operator+(const L &l, const R &r)
    -> Vec<CommonType<L, R>,
           BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                           Addition, PlusTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<CommonType<L, R>, BinaryOperation<L, R, Addition, PlusTrait>>(
        BinaryOperation<L, R, Addition, PlusTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<CommonType<L, R>,
               BinaryOperation<decltype(l.d), R, Addition, PlusTrait>>(
        BinaryOperation<decltype(l.d), R, Addition, PlusTrait>(l.d, r,
                                                                    mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<CommonType<L, R>,
               BinaryOperation<L, decltype(r.d), Addition, PlusTrait>>(
        BinaryOperation<L, decltype(r.d), Addition, PlusTrait>(l, r.d,
                                                                    mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<CommonType<L, R>, BinaryOperation<decltype(l.d), decltype(r.d), Addition,
                                       PlusTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Addition, PlusTrait>(
            l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator-(const L &l, const R &r)
    -> Vec<double, BinaryOperation<decltype(convert(l).d),
                                   decltype(convert(r).d), Minus, MinusTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<L, R, Minus, MinusTrait>>(
        BinaryOperation<L, R, Minus, MinusTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<decltype(l.d), R, Minus, MinusTrait>>(
        BinaryOperation<decltype(l.d), R, Minus, MinusTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<L, decltype(r.d), Minus, MinusTrait>>(
        BinaryOperation<L, decltype(r.d), Minus, MinusTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<decltype(l.d), decltype(r.d), Minus,
                                       MinusTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Minus, MinusTrait>(
            l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator*(const L &l, const R &r)
    -> Vec<double, BinaryOperation<decltype(convert(l).d),
                                   decltype(convert(r).d), Times, TimesTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<L, R, Times, TimesTrait>>(
        BinaryOperation<L, R, Times, TimesTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<decltype(l.d), R, Times, TimesTrait>>(
        BinaryOperation<decltype(l.d), R, Times, TimesTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<L, decltype(r.d), Times, TimesTrait>>(
        BinaryOperation<L, decltype(r.d), Times, TimesTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<decltype(l.d), decltype(r.d), Times,
                                       TimesTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Times, TimesTrait>(
            l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator/(const L &l, const R &r)
    -> Vec<double,
           BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                           Divide, DivideTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<L, R, Divide, DivideTrait>>(
        BinaryOperation<L, R, Divide, DivideTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<decltype(l.d), R, Divide, DivideTrait>>(
        BinaryOperation<decltype(l.d), R, Divide, DivideTrait>(l.d, r,
                                                                    mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<L, decltype(r.d), Divide, DivideTrait>>(
        BinaryOperation<L, decltype(r.d), Divide, DivideTrait>(l, r.d,
                                                                    mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<decltype(l.d), decltype(r.d), Divide,
                                       DivideTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Divide, DivideTrait>(
            l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator^(const L &l, const R &r)
    -> Vec<double, BinaryOperation<decltype(convert(l).d),
                                   decltype(convert(r).d), Pow, PowTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<L, R, Pow, PowTrait>>(
        BinaryOperation<L, R, Pow, PowTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<decltype(l.d), R, Pow, PowTrait>>(
        BinaryOperation<decltype(l.d), R, Pow, PowTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double, BinaryOperation<L, decltype(r.d), Pow, PowTrait>>(
        BinaryOperation<L, decltype(r.d), Pow, PowTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<double,
               BinaryOperation<decltype(l.d), decltype(r.d), Pow, PowTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Pow, PowTrait>(l.d, r.d,
                                                                     mp));
  }
}

template <typename L, typename R>
auto operator==(const L &l, const R &r)
    -> Vec<bool, BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                                 Equal, EqualTrait, ComparisonTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, R, Equal, EqualTrait,
                                     ComparisonTrait>>(
        BinaryOperation<L, R, Equal, EqualTrait, ComparisonTrait>(
            l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), R, Equal, EqualTrait,
                                     ComparisonTrait>>(
        BinaryOperation<decltype(l.d), R, Equal, EqualTrait,
                        ComparisonTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, decltype(r.d), Equal, EqualTrait,
                                     ComparisonTrait>>(
        BinaryOperation<L, decltype(r.d), Equal, EqualTrait,
                        ComparisonTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), decltype(r.d), Equal,
                                     EqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Equal, EqualTrait,
                        ComparisonTrait>(l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator!=(const L &l, const R &r)
    -> Vec<bool, BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                                 UnEqual, UnEqualTrait, ComparisonTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, R, UnEqual, UnEqualTrait,
                                     ComparisonTrait>>(
        BinaryOperation<L, R, UnEqual, UnEqualTrait, ComparisonTrait>(
            l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), R, UnEqual,
                                     UnEqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), R, UnEqual, UnEqualTrait,
                        ComparisonTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, decltype(r.d), UnEqual,
                                     UnEqualTrait, ComparisonTrait>>(
        BinaryOperation<L, decltype(r.d), UnEqual, UnEqualTrait,
                        ComparisonTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), decltype(r.d), UnEqual,
                                     UnEqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), UnEqual, UnEqualTrait,
                        ComparisonTrait>(l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator>(const L &l, const R &r)
    -> Vec<bool, BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                                 Larger, LargerTrait, ComparisonTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, R, Larger, LargerTrait,
                                     ComparisonTrait>>(
        BinaryOperation<L, R, Larger, LargerTrait, ComparisonTrait>(
            l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), R, Larger, LargerTrait,
                                     ComparisonTrait>>(
        BinaryOperation<decltype(l.d), R, Larger, LargerTrait,
                        ComparisonTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, decltype(r.d), Larger, LargerTrait,
                                     ComparisonTrait>>(
        BinaryOperation<L, decltype(r.d), Larger, LargerTrait,
                        ComparisonTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), decltype(r.d), Larger,
                                     LargerTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Larger, LargerTrait,
                        ComparisonTrait>(l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator>=(const L &l, const R &r)
    -> Vec<bool,
           BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                           LargerEqual, LargerEqualTrait, ComparisonTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, R, LargerEqual,
                                     LargerEqualTrait, ComparisonTrait>>(
        BinaryOperation<L, R, LargerEqual, LargerEqualTrait,
                        ComparisonTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), R, LargerEqual,
                                     LargerEqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), R, LargerEqual, LargerEqualTrait,
                        ComparisonTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, decltype(r.d), LargerEqual,
                                     LargerEqualTrait, ComparisonTrait>>(
        BinaryOperation<L, decltype(r.d), LargerEqual, LargerEqualTrait,
                        ComparisonTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), decltype(r.d), LargerEqual,
                                     LargerEqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), LargerEqual,
                        LargerEqualTrait, ComparisonTrait>(l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator<(const L &l, const R &r)
    -> Vec<bool, BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                                 Smaller, SmallerTrait, ComparisonTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, R, Smaller, SmallerTrait,
                                     ComparisonTrait>>(
        BinaryOperation<L, R, Smaller, SmallerTrait, ComparisonTrait>(
            l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), R, Smaller,
                                     SmallerTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), R, Smaller, SmallerTrait,
                        ComparisonTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, decltype(r.d), Smaller,
                                     SmallerTrait, ComparisonTrait>>(
        BinaryOperation<L, decltype(r.d), Smaller, SmallerTrait,
                        ComparisonTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), decltype(r.d), Smaller,
                                     SmallerTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), Smaller, SmallerTrait,
                        ComparisonTrait>(l.d, r.d, mp));
  }
}

template <typename L, typename R>
auto operator<=(const L &l, const R &r)
    -> Vec<bool,
           BinaryOperation<decltype(convert(l).d), decltype(convert(r).d),
                           SmallerEqual, SmallerEqualTrait, ComparisonTrait>> {
  constexpr bool isDoubleL = std::is_arithmetic_v<L>;
  constexpr bool isDoubleR = std::is_arithmetic_v<R>;
  if constexpr (isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, R, SmallerEqual,
                                     SmallerEqualTrait, ComparisonTrait>>(
        BinaryOperation<L, R, SmallerEqual, SmallerEqualTrait,
                        ComparisonTrait>(l, r, mp));
  } else if constexpr (!isDoubleL && isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), R, SmallerEqual,
                                     SmallerEqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), R, SmallerEqual, SmallerEqualTrait,
                        ComparisonTrait>(l.d, r, mp));
  } else if constexpr (isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<L, decltype(r.d), SmallerEqual,
                                     SmallerEqualTrait, ComparisonTrait>>(
        BinaryOperation<L, decltype(r.d), SmallerEqual, SmallerEqualTrait,
                        ComparisonTrait>(l, r.d, mp));
  } else if constexpr (!isDoubleL && !isDoubleR) {
    MatrixParameter mp;
    defineMatrix(l, r, mp);
    return Vec<bool, BinaryOperation<decltype(l.d), decltype(r.d), SmallerEqual,
                                     SmallerEqualTrait, ComparisonTrait>>(
        BinaryOperation<decltype(l.d), decltype(r.d), SmallerEqual,
                        SmallerEqualTrait, ComparisonTrait>(l.d, r.d, mp));
  }
}

} // namespace etr

#endif

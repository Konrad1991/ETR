#ifndef UNARYOPERATION
#define UNARYOPERATION

#include "Core.hpp"

namespace etr {
template <typename I, typename Trait, typename CTrait> struct UnaryOperation {
  using RetType = typename CTrait::RetType;
  using TypeTrait = Trait;
  using CaseTrait = CTrait;
  const I &obj;
  using typeTraitObj = I;
  MatrixParameter mp;
  bool im() const { return mp.im(); }
  size_t nc() const { return mp.nc(); }
  size_t nr() const { return mp.nr(); }
  UnaryOperation(const UnaryOperation &other) : obj(other.obj), mp(other.mp) {}
  UnaryOperation(const UnaryOperation &&other) : obj(other.obj), mp(other.mp) {}
  UnaryOperation(const I &obj_, const MatrixParameter &mp)
      : obj(obj_), mp(mp) {}
  template <typename IType, typename TraitOther>
  UnaryOperation(const UnaryOperation<IType, TraitOther> &other)
      : obj(other.obj), mp(other.mp) {}
  RetType operator[](size_t i) const {
    constexpr bool isDouble = std::is_same_v<I, double>;
    if constexpr (isDouble) {
      return Trait::f(obj);
    } else if constexpr (!isDouble) {
      return Trait::f(obj[i % obj.size()]);
    }
  }
  size_t size() const {
    constexpr bool isDouble = std::is_same_v<I, double>;
    if constexpr (isDouble) {
      return 1;
    } else if constexpr (!isDouble) {
      return obj.size();
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

  template <typename AV> static RetType getSize(AV &av) {
    using Ty = typename std::remove_reference<typeTraitObj>::type;
    return Ty::template getSize<AV>(av);
  }

  template <typename AV> static RetType getVal(AV &av, size_t VecIdx) {
    using Ty = typename std::remove_reference<typeTraitObj>::type;
    return f(Ty::template getVal<AV>(av, VecIdx % Ty::template getSize(av)));
  }
};

template <typename T> auto operator-(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), MinusUnaryTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), MinusUnaryTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<BaseType, MinusUnaryTrait>>(
        UnaryOperation<BaseType, MinusUnaryTrait>{obj});
  }
}

template <typename T> auto sinus(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), SinusTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), SinusTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, SinusTrait>>(
        UnaryOperation<T, SinusTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto sinus(const T &obj) -> BaseType {
  return Sinus(obj);
}

template <typename T> auto sinush(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), SinusHTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), SinusHTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, SinusHTrait>>(
        UnaryOperation<T, SinusHTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto sinush(const T &obj) -> BaseType {
  return SinusH(obj);
}

template <typename T> auto asinus(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), ASinusTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), ASinusTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, ASinusTrait>>(
        UnaryOperation<T, ASinusTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto asinus(const T &obj) -> BaseType {
  return ASinus(obj);
}

template <typename T> auto cosinus(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), CosinusTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), CosinusTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, CosinusTrait>>(
        UnaryOperation<T, CosinusTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto cosinus(const T &obj) -> BaseType {
  return Cosinus(obj);
}

template <typename T> auto cosinush(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), CosinusHTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), CosinusHTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, CosinusHTrait>>(
        UnaryOperation<T, CosinusHTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto cosinush(const T &obj) -> BaseType {
  return CosinusH(obj);
}

template <typename T> auto acosinus(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), ACosinusTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), ACosinusTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, ACosinusTrait>>(
        UnaryOperation<T, ACosinusTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto acosinus(const T &obj) -> BaseType {
  return ACosinus(obj);
}

template <typename T> auto tangens(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), TangensTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), TangensTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, TangensTrait>>(
        UnaryOperation<T, TangensTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto tangens(const T &obj) -> BaseType {
  return Tangens(obj);
}

template <typename T> auto tangensh(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), TangensHTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), TangensHTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, TangensHTrait>>(
        UnaryOperation<T, TangensHTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto tangensh(const T &obj) -> BaseType {
  return TangensH(obj);
}

template <typename T> auto atangens(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), ATangensTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), ATangensTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, ATangensTrait>>(
        UnaryOperation<T, ATangensTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto atangens(const T &obj) -> BaseType {
  return ATangens(obj);
}

template <typename T> auto ln(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), LogTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), LogTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) { // issue: this should be never be used. Also
                                   // for binary operations true.
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, LogTrait>>(
        UnaryOperation<T, LogTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto ln(const T &obj) -> BaseType {
  return Log(obj);
}

template <typename T> auto sqroot(const T &obj) {
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), SquareRootTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), SquareRootTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, SquareRootTrait>>(
        UnaryOperation<T, SquareRootTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto sqroot(const T &obj) -> BaseType {
  return SquareRoot(obj);
}

template <typename T>
auto exp(const T &obj) { // issue: updae this in the documentation
  constexpr bool isDouble = std::is_arithmetic_v<T>;
  if constexpr (!isDouble) {
    return Vec<T, UnaryOperation<decltype(obj.d), ExpTrait>, UnaryTrait>(
        UnaryOperation<decltype(obj.d), ExpTrait>(obj.d, obj.d.mp));
  } else if constexpr (isDouble) {
    static_assert(std::is_same_v<T, BaseType>, "This should never be called!");
    return Vec<T, UnaryOperation<T, ExpTrait>>(
        UnaryOperation<T, ExpTrait>{obj});
  }
}
template <typename T>
  requires std::is_same_v<T, BaseType>
auto exp(const T &obj) -> BaseType {
  return Exp(obj);
}

} // namespace etr

#endif

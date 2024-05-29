#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

#include "VectorClass.hpp"

template <typename T2> Vec(T2 n) = delete;
// internally used
explicit Vec(SI &sz) : d(sz.sz) {
  // std::cout << "constructor test1" << std::endl;
}
explicit Vec(SI &&sz) : d(sz.sz) {
  // std::cout << "constructor test2" << std::endl;
}

// move constructors
template <typename L2> explicit Vec(const Subset<L2> &&inp) : d(inp) {
  d.setMatrix(inp.mp);
  // std::cout << "constructor test3" << std::endl;
}
template <typename L2> explicit Vec(const Buffer<L2> &&inp) : d(inp) {
  d.setMatrix(inp.mp);
}
template <typename U = R, typename T2>
  requires std::is_same_v<U, Borrow<BaseType>>
explicit Vec(const Borrow<T2> &&borrowed) : d(borrowed) {
  d.setMatrix(borrowed.mp);
}
template <typename L2, typename R2, typename OperationTrait>
explicit Vec(const BinaryOperation<L2, R2, OperationTrait> &&inp) : d(inp) {
  using TypeTrait = OperationTrait;
  d.setMatrix(inp.mp);
}
template <typename L2, typename R2, typename OperationTrait,
          typename DetailTrait> // only for comparison!
explicit Vec(const BinaryOperation<L2, R2, OperationTrait, DetailTrait> &&inp)
    : d(inp) {
  using TypeTrait = OperationTrait;
  d.setMatrix(inp.mp);
}
template <typename L2, typename OperationTrait>
explicit Vec(const UnaryOperation<L2, OperationTrait> &&inp) : d(inp) {
  using TypeTrait = OperationTrait;
  d.setMatrix(inp.mp);
}

template <int NBuffer_, int NBorrow_, int NBorrowSEXP_, int NConstants_>
explicit Vec(const AllVars<NBuffer_, NBorrow_, NBorrowSEXP_, NConstants_> &&inp)
    : d(inp) {
  using TypeTrait = VariableTypeTrait;
  using CaseTrait = VariableTypeTrait;
}

// copy constructors
template <typename L2> explicit Vec(Subset<L2> &inp) : d(inp) {
  d.setMatrix(inp.mp);
}
template <typename L2> explicit Vec(const Buffer<L2> &inp) : d(inp) {
  d.setMatrix(inp.mp);
}
template <typename L2, typename TraitOther>
explicit Vec(const Buffer<L2, TraitOther> &inp) : d(inp) {
  d.setMatrix(inp.mp);
}
template <typename U = R, typename T2>
  requires std::is_same_v<U, Borrow<T>>
explicit Vec(const Borrow<T2> &borrowed) : d(borrowed) {
  d.setMatrix(borrowed.mp);
}
template <typename U = R>
  requires std::is_same_v<U, Borrow<T>>
explicit Vec(T *ptr, std::size_t s) : d(ptr, s) {}
template <typename L2, typename R2, typename OperationTrait>
explicit Vec(BinaryOperation<L2, R2, OperationTrait> &inp) : d(inp) {
  using TypeTrait = OperationTrait;
  d.setMatrix(inp.mp);
}
template <typename L2, typename OperationTrait>
explicit Vec(UnaryOperation<L2, OperationTrait> &inp) : d(inp) {
  using TypeTrait = OperationTrait;
  d.setMatrix(inp.mp);
}

template <int NBuffer_, int NBorrow_, int NBorrowSEXP_, int NConstants_>
explicit Vec(AllVars<NBuffer_, NBorrow_, NBorrowSEXP_, NConstants_> &inp)
    : d(inp) {
  using TypeTrait = VariableTypeTrait;
  using CaseTrait = VariableTypeTrait;
}

// other constructors
template <typename U = R>
  requires std::is_same_v<U, BorrowSEXP<T>> // issue: BaseType has to
                                            // be replaced with T

#ifdef STANDALONE_ETR
#else
explicit Vec(SEXP &&inp) = delete;

template <typename U = R>
  requires std::is_same_v<U, BorrowSEXP<T>>
explicit Vec(SEXP inp) : d(inp) {}
#endif

explicit Vec(int sz) : d(1) {
  d[0] = static_cast<T>(sz);
}
explicit Vec(std::size_t sz) : d(1) { d[0] = sz; }
Vec(double sz) : d(1) { d[0] = sz; }

#ifdef STANDALONE_ETR
Vec(bool b) : d(1) { d[0] = static_cast<T>(b); }
#else
Vec(Rboolean b) : d(1) { d[0] = static_cast<T>(b); }
#endif

explicit Vec() : d() {} // std::cout << "constructor test4" << std::endl; }
explicit Vec(std::size_t rows, std::size_t cols) : d(rows * cols) {
  d.setMatrix(true, rows, cols);
}
explicit Vec(std::size_t rows, std::size_t cols, const double value)
    : d(rows * cols) {
  d.setMatrix(true, rows, cols);
  d.fill(value);
}
// other vector constructors
template <typename T2, typename R2, typename Trait2>
Vec(const Vec<T2, R2, Trait2> &other_vec) { // : d()
  using TypeTrait = Trait2;
  using CaseTrait = Trait2;
  if constexpr (isBorrow::value) { // issue: is this safe???
    d.sz = other_vec.size();
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  } else {
    this->d.resize(other_vec.size());
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  }
}

template <typename T2, typename R2, typename Trait2>
  requires IsVec<const Vec<T2, R2, Trait2>>
Vec(const Vec<T2, R2, Trait2>
        &&other_vec) { // issue: improve. Use move her : d()
  using TypeTrait = Trait2;
  using CaseTrait = Trait2;
  if constexpr (isBorrow::value) { // issue: is this safe???
    ass(d.sz <= other_vec.size(), "Sizes do not match");
    d.sz = other_vec.size();
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  } else {
    if (d.sz < other_vec.size()) {
      this->d.resize(other_vec.size());
    } else {
      d.sz = other_vec.size();
    }
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  }
}

template <typename T2, typename R2, typename Trait2>
  requires(IsRVec<const Vec<T2, R2, Trait2>> && !std::is_same_v<T, T2>)
Vec(const Vec<T2, R2, Trait2> &&other_vec) {
  using TypeTrait = Trait2;
  using CaseTrait = Trait2;
  if constexpr (isBorrow::value) {
    ass(d.sz <= other_vec.size(), "Sizes do not match");
    d.sz = other_vec.size();
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  } else {
    if (d.sz < other_vec.size()) {
      this->d.resize(other_vec.size());
    } else {
      d.sz = other_vec.size();
    }
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  }
}

template <typename T2, typename R2, typename Trait2>
  requires(IsRVec<const Vec<T2, R2, Trait2>> && std::is_same_v<T, T2>)
Vec(Vec<T2, R2, Trait2> &&other_vec) {
  using TypeTrait = Trait2;
  using CaseTrait = Trait2;
  if constexpr (isBorrow::value) {
    ass(d.sz <= other_vec.size(), "Sizes do not match");
    d.sz = other_vec.size();
    for (std::size_t i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  } else {
    std::size_t temp = other_vec.size();
    d.allocated = other_vec.d.allocated;
    other_vec.d.sz = this->size();
    d.sz = temp;
    T *tempP = other_vec.d.p;
    other_vec.d.p = d.p;
    d.p = tempP;
    if (other_vec.d.im()) {
      d.setMatrix(true, other_vec.nr(), other_vec.nc());
    }
  }
}

// pointer constructor
Vec(BaseType *ptr, std::size_t size) : d(size) {
  if constexpr (isBorrow::value) {
    d.init(ptr, size);
  } else if constexpr (isBuffer::value) {
    for (std::size_t i = 0; i < size; i++)
      d[i] = ptr[i];
    d.setMatrix(false, 0, 0);
  }
}

Vec(BaseType *ptr, std::size_t rows, std::size_t cols) : d(rows * cols) {
  for (std::size_t i = 0; i < d.size(); i++)
    d[i] = ptr[i];
  d.setMatrix(true, rows, cols);
}

template <typename T2>
  requires std::is_same_v<T2, bool>
explicit Vec(const Vec<T2> &other_vec) : d() {
  d.resize(other_vec.size());
  for (std::size_t i = 0; i < d.size(); i++)
    d[i] = other_vec[i];
  if (other_vec.d.im()) {
    d.setMatrix(true, other_vec.nr(), other_vec.nc());
  }
  // TODO: maybe allocated has to be set here. check!
}

#endif

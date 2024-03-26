#ifndef BUFFER_VECTOR_H
#define BUFFER_VECTOR_H

#include "../BinaryCalculations.hpp"
#include "../Core.hpp"
#include "../UnaryCalculations.hpp"
#include "../Allocation.hpp"
#include "../SEXPConversions.hpp"

namespace etr {

template <typename T, typename R, typename Trait> struct Vec {
  using Type = T;
  // using RetType = T;
  using TypeTrait = Trait;
  using CaseTrait = Trait;
  R d;
  using DType = R;
  using RetType = std::remove_reference<decltype(d)>::type::RetType;
  using typeTraitD = std::remove_reference<decltype(d)>::type::TypeTrait;
  using isBuffer = std::is_same<typeTraitD, BufferTrait>;
  using isBorrow = std::is_same<typeTraitD, BorrowTrait>;
  using isBorrowSEXP = std::is_same<typeTraitD, BorrowSEXPTrait>;
  using isSubset = std::is_same<typeTraitD, SubsetTrait>;
  using caseTraitD = std::remove_reference<decltype(d)>::type::CaseTrait;
  using isUnaryOP = std::is_same<caseTraitD, UnaryTrait>;
  using isBinaryOP = std::is_same<caseTraitD, BinaryTrait>;

  RetType getRetType() const { return RetType{}; }

  #include "Constructors.hpp"
  #include "AssignmentOperator.hpp"

  RetType &operator[](size_t idx) { return d[idx]; }
  RetType operator[](size_t idx) const { return d[idx]; }

  operator RetType() const {
    if constexpr (std::is_same_v<RetType, bool>) {
      ass(this->size() == 1, "Error in if: the condition has length > 1");
      return d[0];
    } else {
      return d[0];
    }
  }

  size_t size() const { return d.size(); }
  bool im() const { return d.im(); }
  size_t nc() const { return d.nc(); }
  size_t nr() const { return d.nr(); }
  auto begin() const {
    if constexpr (isSubset::value) {
      return It<T>{d.p->p};
    } else {
      return It<T>{d.p};
    }
  }
  auto end() const {
    if constexpr (isSubset::value) {
      return It<T>{d.p->p + this->size()};
    } else {
      return It<T>{d.p + this->size()};
    }
  }
  T &back() const { return d.p[this->size()]; }
  void fill(T value) { d.fill(value); }
  void resize(size_t newSize) { d.resize(newSize); }
  friend std::ostream &operator<<(std::ostream &os, const Vec &vec) {
    os << "Vec [ ";
    for (size_t i = 0; i < vec.size(); i++) {
      os << vec.d.p[i] << " ";
    }
    os << "]";
    return os;
  }

#ifdef STANDALONE_ETR
#else
  Vec &operator=(Rcpp::NumericVector &otherVec) {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(false, 0, 0);
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
    return *this;
  }
  Vec &operator=(Rcpp::NumericMatrix &otherVec) {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(true, otherVec.nrow(), otherVec.ncol());
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
    return *this;
  }
  Vec &operator=(arma::vec &otherVec) {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(false, 0, 0);
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
    return *this;
  }
  Vec &operator=(arma::mat &otherVec) {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(true, otherVec.n_rows, otherVec.n_cols);
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
    return *this;
  }
  Vec(Rcpp::NumericVector otherVec) : d() {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(false, 0, 0);
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
  }
  Vec(arma::vec otherVec) : d() {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(false, 0, 0);
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
  }
  Vec(Rcpp::NumericMatrix otherVec) : d() {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(true, otherVec.nrow(), otherVec.ncol());
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
  }
  Vec(arma::mat otherVec) : d() {
    d.resize(static_cast<size_t>(otherVec.size()));
    d.mp.setMatrix(true, otherVec.n_rows, otherVec.n_cols);
    for (size_t i = 0; i < otherVec.size(); i++) {
      d[i] = otherVec[i];
    }
  }

  operator Rcpp::NumericVector() const {
    Rcpp::NumericVector ret(this->size());
    for (size_t i = 0; i < ret.size(); i++) {
      ret[i] = d[i];
    }
    return ret;
  }
  operator Rcpp::NumericMatrix() const {
    ass(this->im() == true, "Object cannot be converted to NumericMatrix");
    Rcpp::NumericMatrix ret(this->nr(), this->nc());
    for (int i = 0; i < ret.size(); i++) {
      ret[i] = d[i];
    }
    return ret;
  }
  operator arma::vec() const {
    arma::vec ret(this->size());
    for (size_t i = 0; i < this->size(); i++) {
      ret[i] = d[i];
    }
    return ret;
  }
  operator arma::mat() const {
    ass(this->im() == true, "Object cannot be converted to arma::mat");
    arma::mat ret(this->nr(), this->nc());
    for (size_t i = 0; i < ret.size(); i++) {
      ret[i] = d[i];
    }
    return ret;
  }
#endif

#ifdef STANDALONE_ETR
  template <typename I> auto operator()(const I &idx) {
    return subset(*this, idx);
  }

  template <typename IL, typename IR>
  auto operator()(const IL &idxL, const IR &idxR) {
    return subset(*this, idxL, idxR);
  }

#endif
};

} // namespace etr

#endif

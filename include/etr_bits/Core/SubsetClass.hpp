#ifndef SUBSETCLASS_ETR_H
#define SUBSETCLASS_ETR_H

namespace etr {
// Points to a Variable and stores indicces in ind
template <typename T, typename SubsetTrait> struct Subset {
  using RetType = BaseType;
  using Type = T;
  using TypeTrait = SubsetTrait;
  using CaseTrait = SubsetTrait;
  Indices ind;
  T *p = nullptr;
  using CurrentBaseType = std::remove_reference<decltype(*p)>::type::Type;
  MatrixParameter mp;

  size_t size() const { return ind.size(); }
  bool im() const { return mp.im(); }
  size_t nc() const { return mp.nc(); }
  size_t nr() const { return mp.nr(); }
  void setMatrix(bool i, size_t nrow, size_t ncol) {
    mp.setMatrix(i, nrow, ncol);
  }
  void setMatrix(MatrixParameter &mp_) {
    mp.setMatrix(mp_.ismatrix, mp_.rows, mp_.cols);
  }
  void setMatrix(const MatrixParameter &mp_) {
    mp.setMatrix(mp_.ismatrix, mp_.rows, mp_.cols);
  }
  void resize(size_t newSize) { p->resize(newSize); }
  void realloc(size_t newSize) { p->realloc(newSize); }

  Subset(const Subset &other) {
    this->p = other.p;
    this->setMatrix(other.mp);
    this->ind = other.ind;
  }
  Subset(const Subset &&other) {
    this->p = other.p;
    this->setMatrix(other.mp);
    this->ind = other.ind;
  }
  template <typename T2, typename R2> Subset(Vec<T2, R2> &other) {
    this->p = &other.d;
  }
  template <typename T2, typename R2, typename TraitOther>
  Subset(const Vec<T2, R2, TraitOther> &other) {
    this->p = &other.d;
  }
#ifdef STANDALONE_ETR
#else
  Subset(SEXP) = delete;
#endif
  Subset(size_t i) = delete;
  Subset(int i) = delete;
  Subset() = delete;
  Subset(size_t r, size_t c) = delete;
  Subset(size_t r, size_t c, const double value) = delete;

  void resizeInd(int newSize) { ind.resize(newSize); }
  void setInd(int idx, int val) { ind[idx] = val; }
  void setPtr(const T *pOther) { this->p = pOther; }

  CurrentBaseType &operator[](size_t pos) {
    ass(this->p != nullptr, "Subset is pointing to nothing!");
    return this->p->operator[](ind[pos % p->size()]);
  }

  CurrentBaseType operator[](size_t pos) const {
    ass(p != nullptr, "Subset is pointing to nothing!");
    return this->p->operator[](ind[pos % p->size()]);
  }

  ~Subset() {}
};

} // namespace etr

#endif
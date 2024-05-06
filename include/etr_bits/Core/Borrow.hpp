#ifndef BORROW_ETR_H
#define BORROW_ETR_H

namespace etr {
// Points to a Variable and stores size
template <typename T, typename BorrowTrait> struct Borrow {
  using RetType = BaseType;
  using Type = T;
  using TypeTrait = BorrowTrait;
  using CaseTrait = BorrowTrait;
  T *p = nullptr;
  std::size_t sz = 1;
  std::size_t capacity = 1;
  bool allocated = false;
  MatrixParameter mp;

  std::size_t size() const { return sz; }
  bool im() const { return mp.im(); }
  std::size_t nc() const { return mp.nc(); }
  std::size_t nr() const { return mp.nr(); }
  void setMatrix(bool i, std::size_t nrow, std::size_t ncol) {
    mp.setMatrix(i, nrow, ncol);
  }

  void setMatrix(const MatrixParameter &mp_) {
    mp.setMatrix(mp_.ismatrix, mp_.rows, mp_.cols);
  }

  Borrow(const Borrow<T> &other)
      : sz(other.sz), capacity(other.capacity), allocated(false) {
    p = other.p;
    mp.setMatrix(other.mp);
  } // issue: deep copy required?
  Borrow(Borrow<T> &&other) noexcept
      : sz(other.sz), capacity(other.capacity), allocated(other.allocated),
        p(other.p) {
    other.capacity = 0;
    other.sz = 0;
    other.allocated = false;
    other.p = nullptr;
    mp.setMatrix(other.mp);
  }
#ifdef STANDALONE_ETR
#else
  Borrow(SEXP s) = delete;
#endif

  Borrow(std::size_t i){};
  Borrow(int i) = delete;
  Borrow(){};
  Borrow(std::size_t r, std::size_t c) = delete;
  Borrow(std::size_t r, std::size_t c, const double value) = delete;
  Borrow(T *p, std::size_t sz) {
    this->p = p;
    this->sz = sz;
    capacity = sz;
    this->allocated = false;
  }

  void init(T *p, std::size_t sz) {
    this->p = p;
    this->sz = sz;
    capacity = sz;
    this->allocated = false;
  }

  Borrow &operator=(const Borrow<T> &other) {
    p = other.p;
    sz = other.sz;
    capacity = other.capacity;
    allocated = false;
    mp.setMatrix(other.mp);
    return *this;
  }

  void fill(T val) {
    for (std::size_t i = 0; i < sz; i++) {
      p[i] = val;
    }
  }

  ~Borrow() {}

  void init(std::size_t size) = delete;
  void resize(std::size_t newSize) {
    ass(newSize >= 1, "Size has to be larger than 0");
    if (newSize <= capacity) {
      sz = newSize;
    } else {
      ass(false, "Cannot resize Borrow element");
    }
  };
  void set(std::size_t idx, T val) {
    ass(idx >= 0, "Index has to be a positive number");
    ass(idx < sz, "Index cannot be larger than size of Indices");
    p[idx] = val;
  }

  RetType operator[](std::size_t idx) const {
    ass(idx >= 0, "Error: out of boundaries --> value below 1");
    ass(idx < sz, "Error: out of boundaries --> value beyond size of vector");
    return p[idx];
  }

  RetType &operator[](std::size_t idx) {
    ass(idx >= 0, "Error: out of boundaries --> value below 1");
    ass(idx < sz, "Error: out of boundaries --> value beyond size of vector");
    return p[idx];
  }

  template <typename L2> Borrow &moveit(L2 &other) = delete;
  auto begin() const { return It<T>{p}; }
  auto end() const { return It<T>{p + sz}; }
  T &back() { return p[sz]; }
  T *data() const { return p; }
  void realloc(int new_size) = delete;
  void push_back(T input) = delete;
  void setSize(std::size_t sz_) { this->sz = sz_; }
  void setPtr(const T *pOther) { this->p = pOther; }

  friend std::ostream &operator<<(std::ostream &os, const Borrow &b) {
    os << "Vec [ ";
    for (std::size_t i = 0; i < b.size(); i++) {
      os << b.p[i] << " ";
    }
    os << "]";
    return os;
  }
};

} // namespace etr

#endif

#ifndef BORROWSEXP_ETR_H
#define BORROWSEXP_ETR_H

namespace etr {
#ifdef STANDALONE_ETR
#else
// Points to a SEXP and stores size
template <typename T, typename BorrowSEXPSEXPTrait> struct BorrowSEXP {
  using RetType = BaseType;
  using Type = T;
  using TypeTrait = BorrowSEXPSEXPTrait;
  using CaseTrait = BorrowSEXPSEXPTrait;
  T *p = nullptr;
  bool todelete = false;
  bool allocated = false;
  std::size_t sz = 0;
  std::size_t capacity = 0;
  MatrixParameter mp;

  std::size_t size() const { return sz; }
  bool im() const { return mp.im(); }
  std::size_t nc() const { return mp.nc(); }
  std::size_t nr() const { return mp.nr(); }
  void setMatrix(bool i, std::size_t nrow, std::size_t ncol) {
    mp.setMatrix(i, nrow, ncol);
  }

  BorrowSEXP(const BorrowSEXP<T> &other) {
    resize(other.size());
    for (std::size_t i = 0; i < sz; i++)
      p[i] = other[i];
    mp.setMatrix(other.mp);
  }
  BorrowSEXP(SEXP inp) {
    if (allocated == true) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      this->p = nullptr;
    }
    p = REAL(inp);
    sz = Rf_length(inp);
    capacity = Rf_length(inp);
    if (Rf_isMatrix(inp) == true) {
      mp.setMatrix(true, Rf_nrows(inp), Rf_ncols(inp));
    }
    todelete = false;
    allocated = true;
  }
  BorrowSEXP(std::size_t i) = delete;
  BorrowSEXP(int i) = delete;
  BorrowSEXP() {}
  BorrowSEXP(std::size_t r, std::size_t c) = delete;
  BorrowSEXP(std::size_t r, std::size_t c, const double value) = delete;

  ~BorrowSEXP() {
    if (todelete) {
      delete[] p;
    }
  }

  BorrowSEXP &operator=(const BorrowSEXP<T> &other) {
    resize(other.size());
    for (std::size_t i = 0; i < sz; i++)
      p[i] = other[i];
    mp.setMatrix(other.mp);
    return *this;
  }

  BorrowSEXP &operator=(SEXP inp) {
    if (allocated) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      this->p = nullptr;
    }
    p = REAL(inp);
    sz = static_cast<std::size_t>(Rf_length(inp));
    capacity = sz;
    if (Rf_isMatrix(inp) == true) {
      mp.setMatrix(true, Rf_nrows(inp), Rf_ncols(inp));
    }
    todelete = false;
    allocated = false;
    return *this;
  }

  RetType &operator[](std::size_t pos) {
    ass(p != nullptr, "Subset is pointing to nothing!");
    ass(pos >= 0, "Error: out of boundaries --> value below 1");
    ass(pos < sz, "Error: out of boundaries --> value beyond size of vector");
    return this->p[pos];
  }

  RetType operator[](std::size_t pos) const {
    ass(this->p != nullptr, "Subset is pointing to nothing!");
    ass(pos >= 0, "Error: out of boundaries --> value below 1");
    ass(pos < sz, "Error: out of boundaries --> value beyond size of vector");
    return this->p[pos];
  }

  void init(std::size_t size) {
    if (allocated && todelete) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      p = nullptr;
    }
    sz = size;
    capacity = static_cast<std::size_t>(1.15 * sz);
    p = new T[capacity];
    allocated = true;
    todelete = true;
  }

  void resize(std::size_t newSize) {
    ass(newSize >= 1, "Size has to be larger than 0");
    if (!allocated) {
      init(newSize);
      if constexpr (std::is_same_v<T, BaseType>) {
        fill(0.0);
      } else if constexpr (std::is_same_v<T, bool>) {
        fill(false);
      }
      return;
    } else {
      if (newSize > capacity) {
        ass(p != nullptr, "try to delete nullptr");
        delete[] p;
        sz = newSize;
        capacity = static_cast<std::size_t>(newSize * 1.15);
        p = new T[capacity];
        allocated = true;
        todelete = true;
        sz = newSize;
        if constexpr (std::is_same_v<T, BaseType>) {
          fill(0.0);
        } else if constexpr (std::is_same_v<T, bool>) {
          fill(false);
        }
      } else {
        sz = newSize;
        return;
      }
    }
  }

  template <typename L2> BorrowSEXP &moveit(L2 &other) {
    if (!todelete) {
      resize(other.size());
      T *temporary = other.p;
      int tempSize = other.sz;
      int tempCapacity = other.capacity;
      other.p = this->p;
      other.sz = this->sz;
      other.capacity = this->capacity;
      this->p = temporary;
      this->sz = tempSize;
      this->capacity = tempCapacity;
    } else {
      T *temporary = other.p;
      int tempSize = other.sz;
      int tempCapacity = other.capacity;
      other.p = this->p;
      other.sz = this->sz;
      other.capacity = this->capacity;
      this->p = temporary;
      this->sz = tempSize;
      this->capacity = tempCapacity;
    }
    return *this;
  }

  auto begin() const { return It<T>{p}; }
  auto end() const { return It<T>{p + sz}; }
  T &back() { return p[sz]; }
  T *data() const { return p; }
  void realloc(int new_size) {
    if (new_size <= sz)
      return;
    if (!todelete) {
      T *temp;
      temp = new T[sz];
      for (std::size_t i = 0; i < sz; i++)
        temp[i] = p[i];
      p = new T[new_size];
      for (std::size_t i = 0; i < sz; i++)
        p[i] = temp[i];
      ass(temp != nullptr, "try to delete nullptr");
      delete[] temp;
      temp = nullptr;
      allocated = true;
      todelete = true;
      for (std::size_t i = sz; i < new_size; i++)
        p[i] = 0.0;
      sz = new_size;
      capacity = sz;
    } else {
      T *temp;
      temp = new T[sz];
      for (std::size_t i = 0; i < sz; i++)
        temp[i] = p[i];
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      p = new T[new_size];
      for (std::size_t i = 0; i < sz; i++)
        p[i] = temp[i];
      ass(temp != nullptr, "try to delete nullptr");
      delete[] temp;
      temp = nullptr;
      allocated = true;
      for (std::size_t i = sz; i < new_size; i++)
        p[i] = 0.0;
      sz = new_size;
      capacity = sz;
    }
  }
  void push_back(T input) {
    if (sz == capacity) {
      realloc(sz * 2);
      capacity = sz;
    } else if (sz < capacity) {
      p[sz] = input; // p starts counting at 0!!!
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const BorrowSEXP &b) {
    os << "Vec [ ";
    for (std::size_t i = 0; i < b.size(); i++) {
      os << b.p[i] << " ";
    }
    os << "]";
    return os;
  }
  void fill(T val) {
    for (std::size_t i = 0; i < sz; i++) {
      p[i] = val;
    }
  }
};
#endif

} // namespace etr

#endif
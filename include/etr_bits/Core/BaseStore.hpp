#ifndef BASESTORE_ETR_H
#define BASESTORE_ETR_H

namespace etr {
template <typename T, typename BaseTrait> struct BaseStore {
  using RetType = T;
  using Type = T;
  using TypeTrait = BaseTrait;
  T *p = nullptr;
  size_t sz = 1;
  size_t capacity = 1;
  bool allocated = false;
  MatrixParameter mp;

  size_t size() const { return sz; }
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

  // constructors
  BaseStore(const BaseStore<T> &other)
      : sz(other.sz), capacity(other.capacity), allocated(other.allocated) {
    if (other.allocated) {
      p = new T[capacity]; // issue: new (use std.:align_val_t(16)) T[capacity]
      std::copy(other.p, other.p + capacity, p);
    } else {
      p = nullptr;
    }
  }
  BaseStore(BaseStore<T> &&other) noexcept
      : sz(other.sz), capacity(other.capacity), allocated(other.allocated),
        p(other.p) {
    other.capacity = 0;
    other.sz = 0;
    other.allocated = false;
    other.p = nullptr;
  }
#ifdef STANDALONE_ETR
#else
  BaseStore(SEXP s) {
    if (allocated) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      this->p = nullptr;
    }
    p = REAL(s);
    sz = static_cast<size_t>(Rf_length(s));
    capacity = static_cast<size_t>(sz * 1.15);
    if (Rf_isMatrix(s) == true) {
      mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
    }
    for (int i = 0; i < sz; i++) {
      p[i] = REAL(s)[i];
    }
    allocated = true;
  };
#endif
  BaseStore(size_t sz_) : sz(sz_), capacity(static_cast<size_t>(sz_ * 1.15)) {
    ass(sz_ > 0, "Size has to be larger than 0");
    p = new T[capacity];
    for (size_t i = 0; i < capacity; i++)
      p[i] = 0.0;
    allocated = true;
  }
  BaseStore(int sz_)
      : sz(static_cast<size_t>(sz_)),
        capacity(static_cast<size_t>(sz_ * 1.15)) {
    ass(sz_ > 0, "Size has to be larger than 0");
    p = new T[capacity];
    for (size_t i = 0; i < sz; i++)
      p[i] = 0.0;
    allocated = true;
  }
  BaseStore() {
    sz = 1;
    capacity = 1;
    p = new T[capacity];
    if constexpr (std::is_same_v<T, BaseType>) {
      p[0] = 0.0;
    } else if constexpr (std::is_same_v<T, bool>) {
      p[0] = false;
    }
    allocated = true;
    mp.setMatrix(false, 0, 0);
  }
  BaseStore(size_t r, size_t c) = delete;
  BaseStore(size_t r, size_t c, const double value) = delete;

  BaseStore &operator=(const BaseStore<T> &other) { // deep copy
    if (this == &other)
      return *this;
    if (other.size() > this->sz) {
      if (allocated) {
        size_t diff = other.size() - this->sz;
        this->realloc(this->sz + diff);
      } else {
        resize(other.size());
      }
    }
    for (size_t i = 0; i < this->sz; i++) {
      p[i] = other[i];
    }
    return *this;
  }

  void fill(T val) {
    for (size_t i = 0; i < sz; i++) {
      p[i] = val;
    }
  }

#ifdef STANDALONE_ETR
#else
  void initSEXP(SEXP s) {
    if (allocated) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      this->p = nullptr;
    }
    sz = static_cast<size_t>(Rf_length(s));
    capacity = static_cast<size_t>(sz * 1.15);
    p = new T[capacity];
    if (Rf_isMatrix(s) == true) {
      mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
    }
    for (int i = 0; i < sz; i++) {
      p[i] = REAL(s)[i];
    }
    allocated = true;
  }
#endif

  ~BaseStore() {
    if (p != nullptr) {
      if (allocated) {
        delete[] p;
        sz = 0;
        capacity = 0;
        p = nullptr;
        allocated = false;
      }
    }
  }

  void init(size_t size) {
    if (allocated) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      p = nullptr;
    }
    sz = size;
    capacity = static_cast<size_t>(1.15 * sz);
    p = new T[capacity];
    allocated = true;
  }
  void resize(size_t newSize) {
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
        capacity = static_cast<size_t>(newSize * 1.15);
        p = new T[capacity];
        sz = newSize;
        allocated = true;
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

  RetType operator[](size_t idx) const {
    ass(allocated, "No memory was allocated");
    ass(idx >= 0, "Error: out of boundaries --> value below 1");
    ass(idx < sz, "Error: out of boundaries --> value beyond size of vector");
    return p[idx];
  }

  RetType &operator[](size_t idx) {
    ass(allocated, "No memory was allocated");
    ass(idx >= 0, "Error: out of boundaries --> value below 1");
    ass(idx < sz, "Error: out of boundaries --> value beyond size of vector");
    return p[idx];
  }

  template <typename L2> BaseStore &moveit(L2 &other) {
    T *temporary = other.p;
    int tempSize = other.sz;
    int tempCapacity = other.capacity;
    other.p = this->p;
    other.sz = this->sz;
    other.capacity = this->capacity;
    this->p = temporary;
    this->sz = tempSize;
    this->capacity = tempCapacity;
    allocated = true;
    return *this;
  }
  auto begin() const { return It<T>{p}; }
  auto end() const { return It<T>{p + sz}; }
  T &back() { return p[sz]; }
  T *data() const { return p; }

  void realloc(size_t new_size) {
    T *temp;
    temp = new T[sz];
    for (size_t i = 0; i < sz; i++)
      temp[i] = p[i];
    if (p != nullptr && allocated)
      delete[] p;
    p = new T[new_size];
    for (size_t i = 0; i < sz; i++)
      p[i] = temp[i];
    ass(temp != nullptr, "try to delete nullptr");
    delete[] temp;
    for (size_t i = sz; i < new_size; i++)
      p[i] = 0.0;
    sz = new_size;
    capacity = sz;
    temp = nullptr;
    allocated = true;
  }

  void push_back(T input) {
    if (sz == capacity) {
      realloc(sz * 2);
      capacity = sz;
    } else if (sz < capacity) {
      p[sz] = input; // p starts counting at 0!!!
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const BaseStore &b) {
    os << "Vec [ ";
    for (size_t i = 0; i < b.size(); i++) {
      os << b.p[i] << " ";
    }
    os << "]";
    return os;
  }
};

struct Indices : public BaseStore<size_t> {
  using RetType = size_t;
};
} // namespace etr

#endif
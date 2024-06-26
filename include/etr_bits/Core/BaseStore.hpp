#ifndef BASESTORE_ETR_H
#define BASESTORE_ETR_H

#include "Header.hpp"
#include "MatrixParameter.hpp"
#include "Reflection.hpp"
#include "Types.hpp"
#include "Utils.hpp"

namespace etr {
template <typename T, typename BaseTrait> struct BaseStore {
  using RetType = T;
  using Type = T;
  using TypeTrait = BaseTrait;
  T *p = nullptr;
  std::size_t sz = 0;
  std::size_t capacity = 0;
  bool allocated = false;
  MatrixParameter mp;

  std::size_t size() const { return sz; }
  bool im() const { return mp.im(); }
  std::size_t nc() const { return mp.nc(); }
  std::size_t nr() const { return mp.nr(); }
  void setMatrix(bool i, std::size_t nrow, std::size_t ncol) {
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
      p = new T[capacity];
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

    if constexpr (is<RetType, double>) {
      ass(Rf_isReal(s), "R object is not of type numeric");
      sz = static_cast<std::size_t>(Rf_length(s));
      capacity = static_cast<std::size_t>(sz);
      p = new T[capacity];
      if (Rf_isMatrix(s) == true) {
        mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
      }
      for (int i = 0; i < sz; i++) {
        p[i] = REAL(s)[i];
      }
      allocated = true;
    } else if constexpr (is<RetType, int>) {
      ass(Rf_isInteger(s), "R object is not of type integer");
      sz = static_cast<std::size_t>(Rf_length(s));
      capacity = static_cast<std::size_t>(sz);
      p = new T[capacity];
      if (Rf_isMatrix(s) == true) {
        mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
      }
      for (int i = 0; i < sz; i++) {
        p[i] = INTEGER(s)[i];
      }
      allocated = true;
    } else if constexpr (is<RetType, bool>) {
      ass(Rf_isLogical(s), "R object is not of type logical");
      sz = static_cast<std::size_t>(Rf_length(s));
      capacity = static_cast<std::size_t>(sz);
      p = new T[capacity];
      if (Rf_isMatrix(s) == true) {
        mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
      }
      for (int i = 0; i < sz; i++) {
        p[i] = LOGICAL(s)[i];
      }
      allocated = true;
    } else {
      static_assert(sizeof(T) == 0, "Unsupported type found");
    }
  };
#endif
  BaseStore(std::size_t sz_)
      : sz(sz_), capacity(static_cast<std::size_t>(sz_ * 1.15)) {
    ass(sz_ > 0, "Size has to be larger than 0");
    p = new T[capacity];
    for (std::size_t i = 0; i < capacity; i++) {
      p[i] = T();
    }
    allocated = true;
  }
  BaseStore(int sz_)
      : sz(static_cast<std::size_t>(sz_)),
        capacity(static_cast<std::size_t>(sz_ * 1.15)) {
    ass(sz_ > 0, "Size has to be larger than 0");
    p = new T[capacity];
    for (std::size_t i = 0; i < sz; i++)
      p[i] = T();
    allocated = true;
  }
  BaseStore() {
    /*
    // TODO: check why this is called sometimes. Furthermore, add the same
    functionality default size = 0 to other containers sz = 1; capacity = 1; p =
    */
  }
  BaseStore(std::size_t r, std::size_t c) = delete;
  BaseStore(std::size_t r, std::size_t c, const double value) = delete;

  BaseStore &operator=(const BaseStore<T> &other) { // deep copy
    if (this == &other)
      return *this;
    if (other.size() > this->sz) {
      if (allocated) {
        std::size_t diff = other.size() - this->sz;
        this->realloc(this->sz + diff);
      } else {
        resize(other.size());
      }
    }
    for (std::size_t i = 0; i < this->sz; i++) {
      p[i] = other[i];
    }
    return *this;
  }

  template <typename TInp>
    requires(std::is_arithmetic_v<std::remove_reference_t<TInp>>)
  void fill(TInp &&val) {
    if constexpr (std::is_same_v<T, TInp>) {
      std::fill(p, p + sz, val);
    } else {
      auto temp = static_cast<T>(val);
      std::fill(p, p + sz, temp);
    }
  }

  template <typename TInp> void fill(TInp &&inp) {
    ass(inp.size() == sz, "cannot use fill with vectors of different lengths");
    using DataType = ExtractDataType<std::remove_reference_t<TInp>>::RetType;
    if constexpr (IsVec<TInp>) {
      if constexpr (!is<DataType, T>) {
        for (std::size_t i = 0; i < sz; i++)
          p[i] = static_cast<T>(inp[i]);
      } else {
        DataType *ptr = inp.getPtr();
        std::copy(ptr, ptr + sz, p);
      }
    } else if constexpr (IsRVec<TInp> && is<DataType, T>) {
      delete[] p;
      DataType *ptr = inp.getPtr();
      inp.d.p = nullptr;
      inp.d.allocated = false;
      p = ptr;
    } else {
      if constexpr (is<DataType, T>) {
        for (std::size_t i = 0; i < sz; i++)
          p[i] = inp[i];
      } else {
        for (std::size_t i = 0; i < sz; i++)
          p[i] = static_cast<T>(inp[i]);
      }
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
    if constexpr (is<RetType, double>) {
      ass(Rf_isReal(s), "R object is not of type numeric");
      sz = static_cast<std::size_t>(Rf_length(s));
      capacity = static_cast<std::size_t>(sz);
      p = new T[capacity];
      if (Rf_isMatrix(s) == true) {
        mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
      }
      for (int i = 0; i < sz; i++) {
        p[i] = REAL(s)[i];
      }
      allocated = true;
    } else if constexpr (is<RetType, int>) {
      ass(Rf_isInteger(s), "R object is not of type integer");
      sz = static_cast<std::size_t>(Rf_length(s));
      capacity = static_cast<std::size_t>(sz);
      p = new T[capacity];
      if (Rf_isMatrix(s) == true) {
        mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
      }
      for (int i = 0; i < sz; i++) {
        p[i] = INTEGER(s)[i];
      }
      allocated = true;
    } else if constexpr (is<RetType, bool>) {
      ass(Rf_isLogical(s), "R object is not of type logical");
      sz = static_cast<std::size_t>(Rf_length(s));
      capacity = static_cast<std::size_t>(sz);
      p = new T[capacity];
      if (Rf_isMatrix(s) == true) {
        mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
      }
      for (int i = 0; i < sz; i++) {
        p[i] = LOGICAL(s)[i];
      }
      allocated = true;
    } else {
      static_assert(sizeof(T) == 0, "Unsupported type found");
    }
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

  void init(std::size_t size) {
    if (allocated) {
      ass(p != nullptr, "try to delete nullptr");
      delete[] p;
      p = nullptr;
    }
    sz = size;
    capacity = static_cast<std::size_t>(1.15 * sz);
    p = new T[capacity];
    allocated = true;
  }
  void resize(std::size_t newSize) {
    ass(newSize >= 1, "Size has to be larger than 0");
    if (!allocated) {
      init(newSize);
      fill(T());
      return;
    } else {
      if (newSize > capacity) {
        ass(p != nullptr, "try to delete nullptr");
        delete[] p;
        capacity = static_cast<std::size_t>(newSize * 1.15);
        p = new T[capacity];
        sz = newSize;
        allocated = true;
        fill(T());
      } else {
        sz = newSize;
        return;
      }
    }
  }

  RetType operator[](std::size_t idx) const {
    ass(allocated, "No memory was allocated");
    ass(idx >= 0, "Error: out of boundaries --> value below 1");
    ass(idx < sz, "Error: out of boundaries --> value beyond size of vector");
    return p[idx];
  }

  RetType &operator[](std::size_t idx) {
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

  void realloc(std::size_t new_size) {
    T *temp;
    capacity = static_cast<int>(new_size * 1.15);
    temp = new T[capacity];
    for (std::size_t i = 0; i < sz; i++)
      temp[i] = p[i];

    for (std::size_t i = sz; i < new_size; i++)
      temp[i] = T();

    delete[] p;
    p = temp;

    sz = new_size;
    allocated = true;
    temp = nullptr;
  }

  void push_back(T input) {
    if (sz == capacity) {
      int szOld = sz;
      if (sz == 0) {
        realloc(1);
      } else if (sz > 0) {
        realloc(sz * 2);
      } else {
        ass(false, "negative size found.");
      }
      capacity = sz;
      p[szOld] = input;
      sz = szOld + 1;
    } else if (sz < capacity) {
      p[sz] = input;
      sz++;
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const BaseStore &b) {
    os << "Vec [ ";
    for (std::size_t i = 0; i < b.size(); i++) {
      os << b.p[i] << " ";
    }
    os << "]";
    return os;
  }
};

struct Indices : public BaseStore<std::size_t> {
  using RetType = std::size_t;
};
} // namespace etr

#endif

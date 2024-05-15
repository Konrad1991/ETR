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
    sz = static_cast<std::size_t>(Rf_length(s));
    capacity = static_cast<std::size_t>(sz * 1.15);
    if (Rf_isMatrix(s) == true) {
      mp.setMatrix(true, Rf_nrows(s), Rf_ncols(s));
    }
    for (int i = 0; i < sz; i++) {
      p[i] = REAL(s)[i];
    }
    allocated = true;
  };
#endif
  BaseStore(std::size_t sz_)
      : sz(sz_), capacity(static_cast<std::size_t>(sz_ * 1.15)) {
    ass(sz_ > 0, "Size has to be larger than 0");
    p = new T[capacity];
    for (std::size_t i = 0; i < capacity; i++)
      p[i] = 0.0;
    allocated = true;
  }
  BaseStore(int sz_)
      : sz(static_cast<std::size_t>(sz_)),
        capacity(static_cast<std::size_t>(sz_ * 1.15)) {
    ass(sz_ > 0, "Size has to be larger than 0");
    p = new T[capacity];
    for (std::size_t i = 0; i < sz; i++)
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
requires (std::is_arithmetic_v<std::remove_reference_t<TInp>>)
  void fill(TInp &&val) {
    if constexpr (std::is_same_v<T, TInp>) {
      std::fill(p, p + sz, val);
    } else {
      auto temp = static_cast<T>(val);
      std::fill(p, p + sz, temp);
    }
  }

  template<typename TInp>
  void fill(TInp && inp) {
    ass(inp.size() == sz, "cannot use fill with vectors of different lengths");
    using DataType = ExtractDataType<std::remove_reference_t<TInp>>::RetType;
    if constexpr(Operation<TInp>) {
      for (std::size_t i = 0; i < sz; i++)
        p[i] = inp[i];
    } else if constexpr (!std::is_same_v<DataType, T>) {
      for (std::size_t i = 0; i < sz; i++)
        p[i] = static_cast<T>(inp[i]);
    } else if constexpr(IsRVec<TInp>) {
      delete[] p;
      DataType *ptr = inp.getPtr();
      inp.d.p = nullptr; inp.d.allocated = false;
      p = ptr;
    } else {
      DataType *ptr = inp.getPtr();
      std::copy(ptr, ptr + sz,p);
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
    sz = static_cast<std::size_t>(Rf_length(s));
    capacity = static_cast<std::size_t>(sz * 1.15);
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
        capacity = static_cast<std::size_t>(newSize * 1.15);
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
    temp = new T[sz];
    for (std::size_t i = 0; i < sz; i++)
      temp[i] = p[i];
    if (p != nullptr && allocated)
      delete[] p;
    p = new T[new_size];
    for (std::size_t i = 0; i < sz; i++)
      p[i] = temp[i];
    ass(temp != nullptr, "try to delete nullptr");
    delete[] temp;
    for (std::size_t i = sz; i < new_size; i++)
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

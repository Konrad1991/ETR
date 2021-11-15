/*
R package etr
Copyright (C) 2021 Konrad Krämer

This file is part of R package etr


etr is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with etr
If not see: https://www.gnu.org/licenses/old-licenses/gpl-2.0.html#SEC4
*/
#ifndef VEC_H
#define VEC_H

#include "pointer_storage.hpp"

/*
Vector & matrix module
*/
template< typename T, typename R = STORE<T> >
class VEC {

private:

public:

  // Constructors
  // ================================================================
  bool subsetted;
  //bool fill;
  std::vector<int> indices;

  // for Matrix
  bool ismatrix;
  int ncols;
  int nrows;

  int ncols_sub;
  int nrows_sub;

  // data
  R d;

  // Constructors for vector
  VEC(const int n) : d(n), subsetted(0), ismatrix(0) {}
  VEC(const int n, const double value) : d(n, value), subsetted(0), ismatrix(0) {}
  VEC(const R& other_vec) : d(other_vec), subsetted(0), ismatrix(0) {}
  //VEC(const R&& other_vec) : d(other_vec), subsetted(0), ismatrix(0) {} // not correct?

  //VEC(const R& mat, int nrows_, int ncols_) : d(mat), subsetted(0), ncols(ncols_), nrows(nrows_), ismatrix(0) {}
  VEC() : subsetted(0), d(0), nrows(0), ncols(0), ismatrix(0) {}
  VEC(const std::vector<T> inp) : subsetted(0), d(inp), nrows(0), ncols(0), ismatrix(0) {}

  // Constructors for matrix
  VEC(const int rows, const int cols) : d(rows*cols), subsetted(0), nrows(rows), ncols(cols), ismatrix(1) {}
  VEC(const int rows, const int cols, const double value) : d(rows*cols, value), subsetted(0), nrows(rows), ncols(cols), ismatrix(1) {}
  VEC(const int rows, const int cols, int value) : d(rows*cols, value), subsetted(0), nrows(rows), ncols(cols), ismatrix(1) {}

  // vector & matrix operator=
  // ================================================================
  VEC& operator=(const T &dob) {

    if(subsetted == false) {
      d.resize(1);
      ismatrix = false;
      d[0] = dob;
    } else {
      for(int i = 0; i < indices.size(); i++) {
        d[indices[i]] = dob;
      }
    }

    subsetted = false;
    return *this;
  }

  VEC& operator=(const VEC& other_vec) {

    if(this == &other_vec) {
      VEC temp(other_vec.indices.size());
      for(int i = 0; i < other_vec.indices.size(); i++) {
        temp.d[i] = other_vec.d[other_vec.indices[i]];
      }

      this -> d = temp.d;
    }

    if(subsetted == false) {
      if(d.size() != other_vec.size()) {
          //d.realloc(other_vec.size());  // better resize?
          d.resize(other_vec.size());
      }

      this -> ismatrix = false;
      for(int i = 0; i < d.size(); i++) {
        d[i] = other_vec[i];
      }
      if(other_vec.im() == true) {
        this -> ismatrix = true;
        this -> ncols = other_vec.nc();
        this -> nrows = other_vec.nr();
      }
    } else {
      for(int i = 0; i < indices.size(); i++) {
        d[indices[i]] = other_vec[i];
      }
    }

    subsetted = false;

    return *this;
  }

  template<typename T2, typename R2>
  VEC& operator=(const VEC<T2, R2> &other_vec) {

    if(subsetted == false) {
      if(d.size() != other_vec.size()) {
        d.resize(other_vec.size());
          //d.realloc(other_vec.size());  // better resize?
      }
      this -> ismatrix = false;

      for(int i = 0; i < d.size(); i++) {
            d[i] = other_vec[i];
      }
      if(other_vec.d.im() == true) {
        ismatrix = true;
        ncols = other_vec.d.nc();
        nrows = other_vec.d.nr();
      }
    } else {
      for(int i = 0; i < indices.size(); i++) {
          d[indices[i]] = other_vec[i];
      }
    }

    subsetted = false;

    return *this;
  }

// getter methods for vector
// ================================================================
 int size() const {
   return d.size();
 }

 T operator[](int i) const {
   return d[i];
 }

 T& operator[](int i) {
   return d[i];
 }

 const R& data() const {
   return d;
 }

 R& data() {
   return d;
 }

 T* pointer() {
   return d.data();
 }
// ================================================================

bool is_subsetted() const {
  return subsetted;
}

void realloc(int new_size) { // when is it called?
  d.realloc(new_size);
}

// getter methods for matrix
// ================================================================
 int ncol() const {
   return ncols;
 }

 int nrow() const {
   return nrows;
 }


bool im() const {
  return ismatrix;
}

int nc() const {
  return ncols;
}

int nr() const {
  return nrows;
}

 auto begin() const {
   return It<T>{d.p};
 }

 auto end() const {
   return It<T>{d.p + this -> size()};
 }

 T& back() {
   return d.p[this -> size()];
 }

 // resize indices
 void rsi(int sizenew) {
   this -> indices.resize(sizenew);
 }

}; // end class VEC



int d2i(double inp) {
  return static_cast<int>(inp);
}

#endif

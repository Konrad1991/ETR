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

namespace etr {

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
  int rhs_subsetted = 0;
  std::vector<int> indices;

  // for Matrix
  bool ismatrix;
  int ncols;
  int nrows;

  int ncols_sub;
  int nrows_sub;

  // data
  R d;
  std::vector<double> temp;

  template<typename T2>
  VEC(T2 n) = delete;

  VEC(const bool value) : d(1, value),subsetted(0), ismatrix(0) {}

  VEC(const double value) : d(1, value),subsetted(0), ismatrix(0) {}
  VEC(const long unsigned int n) : d(n), subsetted(0), ismatrix(0) {d.fill(static_cast<double>(n));} // fill is a hack that sexp s = 1 works;

  // Constructors for vector
  VEC(const int n) : d(n), subsetted(0), ismatrix(0) {d.fill(static_cast<double>(n));} // fill is a hack that sexp s = 1 works;
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

  // constructor for calculations
  template<typename T2, typename R2>
  VEC(const VEC<T2, R2> &other_vec) :d(1) {

      this -> d.resize(other_vec.size());
      this -> ismatrix = false;
      for(int i = 0; i < d.size(); i++) {
            this -> d[i] = other_vec[i];
      }

      if(other_vec.d.im() == true) {
        this -> ismatrix = true;
        this -> ncols = other_vec.d.nc();
        this -> nrows = other_vec.d.nr();
      }

      subsetted = false;

  }

  // constructor for COMPARISON
  VEC(const VEC<bool>& other_vec) : d(1) {
    d.resize(other_vec.size());
    ismatrix = false;
    subsetted = false;
    for(int i = 0; i < d.size(); i++) {
      d[i] = other_vec[i];
    }

  }

  // constructor for pointer
  VEC(const int n, T* ptr, int cob) : d(n, ptr, cob), subsetted(0), ismatrix(0) {} //cob = copy, owning, borrow
  VEC(const int r, const int c, T* ptr, int cob) : d(r*c, ptr, cob), subsetted(0), ismatrix(1), nrows(r), ncols(c) {} //cob = copy, owning, borrow

  explicit operator bool() const{return d[0];}

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
      }
      this -> ismatrix = false;

      for(int i = 0; i < d.size(); i++) {
            this -> d[i] = other_vec[i];
      }
      if(other_vec.d.im() == true) {
        ismatrix = true;
        ncols = other_vec.d.nc();
        nrows = other_vec.d.nr();
      }
    } else {
      if(rhs_subsetted == 1) { // only subset at lhs
        for(int i = 0; i < indices.size(); i++) {
            this -> d[indices[i]] = other_vec[i];
        }
      } else if(rhs_subsetted % 2 == 0) { // only subsetted at rhs
        for(int i = 0; i < d.size(); i++) {
              this -> d[i] = other_vec[i];
        }
      } else if(rhs_subsetted % 2 != 0) { // subset at lhs and rhs

        this -> temp.resize(other_vec.size());
        for(int i = 0; i < indices.size(); i++) {
              this -> temp[i] = other_vec[i];
        }
        for(int i = 0; i < indices.size(); i++) {
              this -> d[i] = temp[i];
        }
      }

    }

    subsetted = false;
    rhs_subsetted = 0;

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

 VEC& operator() (int pos) {
   // missing check if subsetted
   pos--;
   rsi(1);
   subsetted = true;
   indices[0] = pos;
   rhs_subsetted++;
   return *this;
 }

}; // end class VEC



int d2i(double inp) {
  return static_cast<int>(inp);
}



}

#endif

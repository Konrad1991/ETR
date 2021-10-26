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
  std::vector<int> indices;

  // for Matrix
  bool ismatrix;
  int ncols;
  int nrows;

  // data
  R d;

  // Constructors for vector
  VEC(const int n) : d(n), subsetted(0), ismatrix(0) {}
  VEC(const int n, const double value) : d(n, value), subsetted(0), ismatrix(0) {}
  VEC(const R& other_vec) : d(other_vec), subsetted(0), ismatrix(0) {}

  VEC(const R& mat, int nrows_, int ncols_) : d(mat), subsetted(0), ncols(ncols_), nrows(nrows_), ismatrix(0) {}
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
      d[0] = dob;
    } else {
      for(int i = 0; i < indices.size(); i++) {
        d[indices[i]] = dob;
      }
    }

    ismatrix = false;

    subsetted = false;
    return *this;
  }

  VEC& operator=(const R& other_vec) {

    if(other_vec.size() > d.size()) {
      int diff = other_vec.size() - d.size();
      this -> realloc(d.size() + diff);
    }

    if(subsetted == false) {
      d.resize(other_vec.size());
      for(int i = 0; i < d.size(); i++) {
        d[i] = other_vec[i];
      }
    } else {
      for(int i = 0; i < indices.size(); i++) {
        d[indices[i]] = other_vec[i];
      }
    }

    subsetted = false;
    return *this;
  }


  VEC& operator=(const VEC& other_vec) {

    if(other_vec.size() > d.size()) {
      int diff = other_vec.size() - d.size();
      this -> realloc(d.size() + diff);
    }

    if(subsetted == false) {
      d.resize(other_vec.size());
      for(int i = 0; i < d.size(); i++) {
        d[i] = other_vec[i];
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

    if(other_vec.d.im() == true) {
      ismatrix = true;
      ncols = other_vec.d.nc();
      nrows = other_vec.d.nr();
    }

    if(other_vec.size() > d.size()) {
      int diff = other_vec.size() - d.size();
      this -> realloc(d.size() + diff);
    }

    if(subsetted == false) {
      for(int i = 0; i < d.size(); i++) {
        d[i] = other_vec[i];
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

void realloc(int new_size) {
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

 // Vector
 // subsetting at RHS
 // ================================================================

 /*
 start and end
 */
 /*
 VEC<double> operator()(int start, int end) {
   VEC<double> t;
   start--;
   end--;
   t.d.resize(end - start + 1);

   for(int i = 0; i < t.d.size(); i++) {
     t.d[i] = d[i + start];
   }
   return t;
 }
 */

 /*
 desired positions
 */
 VEC<double> operator()(VEC<double>&& ip) {

   VEC<double> t;
   int start = ip[0] - 1;
   int end = ip.d.back() - 1;

   t.d.resize((end -1) - (start -1) + 1);
   for(int i = 0; i < t.d.size(); i++) {
     t.d[i] = d[start + i];
   }
   return t;
 }

 /*
 desired positions
 */
 VEC<double> operator()(VEC<double> ip) {

   VEC<double> t;
   int start = ip[0] - 1;
   int end = ip.d.back() - 1;

   t.d.resize((end -1) - (start -1) + 1);
   for(int i = 0; i < t.d.size(); i++) {
     t.d[i] = d[start + i];
   }
   return t;
 }

 /*
 desired positions
 */
 VEC<double> operator()(std::vector<double>&& ip) {

   VEC<double> t;
   int start = ip[0] - 1;
   int end = ip.back() - 1;

   t.d.resize((end -1) - (start -1) + 1);
   for(int i = 0; i < t.d.size(); i++) {
     t.d[i] = d[start + i];
   }
   return t;
 }

 /*
 desired positions
 */
 VEC<double> operator()(std::vector<double> ip) {

   VEC<double> t;
   int start = ip[0] - 1;
   int end = ip.back() - 1;

   t.d.resize((end -1) - (start -1) + 1);
   for(int i = 0; i < t.d.size(); i++) {
     t.d[i] = d[start + i];
   }
   return t;
 }


 /*
 one position
 */
 T& operator()(int pos) {
   pos--;
   return d[pos];
 }

 /*
 one position
 */
 T& operator()(int rows, int cols) {
   rows--;
   cols--;
   return d[rows*nrows + cols];
 }


}; // end class VEC


#endif

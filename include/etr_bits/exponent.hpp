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


#ifndef EXPONENT
#define EXPONENT

#include "vec.hpp"

template<typename T, typename L, typename R>
class VVEXP {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;
  double exponent;

public:

  VVEXP(const L &a, bool r_ismatrix, int r_rows, int r_cols, double exponent_) : r(a), exponent(exponent_) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

   }

   T operator[](const int i) const {
     return std::pow(r[i], exponent);
   }

   int size() const {
     return r.size();
   }

   bool im() const {
     return ismatrix;
   }

   int nc() const {
     return ncol_;
   }

   int nr() const {
     return nrow_;
   }

};


template<typename T, typename L, typename R>
VEC< T, VVEXP< T, L, R> > operator^(const VEC<T, L>& a, const R exponent) {
    return VEC<T, VVEXP<T, L, R> > (VVEXP<T, L, R>(a.data(), a.im(), a.nrow(), a.ncol(), exponent) );
}


double exp(double base, double exponent) {
  return std::pow(base, exponent);
}

#endif

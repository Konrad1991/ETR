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


#ifndef TRIGO
#define TRIGO

#include "vec.hpp"

template<typename T, typename L>
class VVSIN {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVSIN(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::sin(r[i]);
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


template<typename T, typename L>
VEC< T, VVSIN< T, L> > sinus(const VEC<T, L>& a) {
    return VEC<T, VVSIN<T, L> > (VVSIN<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double sinus(double base) {
  return std::sin(base);
}

double sinus(int base) {
  return std::sin(static_cast<double>(base));
}



template<typename T, typename L>
class VVsinh {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVsinh(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::sinh(r[i]);
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


template<typename T, typename L>
VEC< T, VVsinh< T, L> > sinush(const VEC<T, L>& a) {
    return VEC<T, VVsinh<T, L> > (VVsinh<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double sinush(double base) {
  return std::sinh(base);
}

double sinush(int base) {
  return std::sinh(static_cast<double>(base));
}


template<typename T, typename L>
class VVasin {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVasin(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::asin(r[i]);
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


template<typename T, typename L>
VEC< T, VVasin< T, L> > asinus(const VEC<T, L>& a) {
    return VEC<T, VVasin<T, L> > (VVasin<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double asinus(double base) {
  return std::asin(base);
}

double asinus(int base) {
  return std::asin(static_cast<double>(base));
}





template<typename T, typename L>
class VVCOS {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVCOS(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::cos(r[i]);
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


template<typename T, typename L>
VEC< T, VVCOS< T, L> > cosinus(const VEC<T, L>& a) {
    return VEC<T, VVCOS<T, L> > (VVCOS<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double cosinus(double base) {
  return std::cos(base);
}

double cosinus(int base) {
  return std::cos(static_cast<double>(base));
}






template<typename T, typename L>
class VVacos {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVacos(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::acos(r[i]);
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


template<typename T, typename L>
VEC< T, VVacos< T, L> > acosinus(const VEC<T, L>& a) {
    return VEC<T, VVacos<T, L> > (VVacos<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double acosinus(double base) {
  return std::acos(base);
}

double acosinus(int base) {
  return std::acos(static_cast<double>(base));
}





template<typename T, typename L>
class VVCOSH {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVCOSH(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::cosh(r[i]);
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


template<typename T, typename L>
VEC< T, VVCOSH< T, L> > cosinush(const VEC<T, L>& a) {
    return VEC<T, VVCOSH<T, L> > (VVCOSH<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double cosinush(double base) {
  return std::cosh(base);
}

double cosinush(int base) {
  return std::cosh(static_cast<double>(base));
}







template<typename T, typename L>
class VVtan {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVtan(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::tan(r[i]);
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


template<typename T, typename L>
VEC< T, VVtan< T, L> > tangens(const VEC<T, L>& a) {
    return VEC<T, VVtan<T, L> > (VVtan<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double tangens(double base) {
  return std::tan(base);
}

double tangens(int base) {
  return std::tan(static_cast<double>(base));
}





template<typename T, typename L>
class VVatan {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVatan(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::atan(r[i]);
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


template<typename T, typename L>
VEC< T, VVatan< T, L> > atangens(const VEC<T, L>& a) {
    return VEC<T, VVatan<T, L> > (VVatan<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double atangens(double base) {
  return std::atan(base);
}

double atangens(int base) {
  return std::atan(static_cast<double>(base));
}





template<typename T, typename L>
class VVtanh {

private:
  const L& r; //const L& l;
  bool ismatrix;
  int nrow_;
  int ncol_;

public:

  VVtanh(const L &a, bool r_ismatrix, int r_rows, int r_cols) : r(a) {

    if( r_ismatrix == true) {
      ismatrix = r_ismatrix;
      nrow_ = r_rows;
      ncol_ = r_cols;
    }

  }

   T operator[](const int i) const {
     return std::tanh(r[i]);
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


template<typename T, typename L>
VEC< T, VVtanh< T, L> > tangensh(const VEC<T, L>& a) {
    return VEC<T, VVtanh<T, L> > (VVtanh<T, L>(a.data(), a.im(), a.nrow(), a.ncol()) );
}


double tangensh(double base) {
  return std::tanh(base);
}

double tangensh(int base) {
  return std::tanh(static_cast<double>(base));
}

#endif

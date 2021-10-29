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


#ifndef SUBSETTING
#define SUBSETTING

#include "vec.hpp"



// Vector
// subsetting at RHS
// ================================================================

/*
desired positions
*/
VEC<double> subset(VEC<double>& inp, VEC<double>&& ip) {

  VEC<double> t(ip.size());

  for(int i = 0; i < t.size(); i++) {
    t[i] = inp[ip[i] - 1]; // user start counting at 1
  }
  return t;
}

/*
desired positions
*/
VEC<double> subset(VEC<double>& inp, VEC<double>& ip) {
  VEC<double> t(ip.size());

  for(int i = 0; i < t.size(); i++) {
    t[i] = inp[ip[i] - 1]; // user start counting at 1
  }
  return t;
}

/*
one position
*/
double subset(VEC<double>& inp, int pos) {
  pos--;
  return inp[pos]; // user start counting at 1
}

/*
one position
*/
double subset(VEC<double>& inp, double pos) {
  int temp = static_cast<int>(pos);
  temp--; // user start counting at 1
  return inp[temp];
}



/*
one position
*/
double subset(VEC<double>&inp, int row, int col) {
  row--;
  col--;
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }
  return inp[row*inp.nr() + col];
}

/*
one position
*/
double subset(VEC<double>&inp, double row_, double col_) {
  int row = static_cast<int>(row_);
  int col = static_cast<int>(col_);
  row--;
  col--;
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }
  return inp[row*inp.nr() + col];
}


/*
desired positions
*/
VEC<double> subset(VEC<double>&inp, int r, char s) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }
  int c = inp.nc();

  VEC<double> ret(1, c);

  for(int j = 0; j < c; j++) {
       ret[1 + j -1] = inp[ (r-1)*inp.nr() + j];
  }

  return ret;
}


/*
desired positions
*/
VEC<double> subset(VEC<double>&inp, double r_, char s) {
  int r = static_cast<int>(r_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }
  int c = inp.nc();

  VEC<double> ret(1, c);

  for(int j = 0; j < c; j++) {
       ret[1 + j -1] = inp[ (r-1)*inp.nr() + j];
  }

  return ret;
}

/*
desired positions
*/
VEC<double> subset(VEC<double>&inp, char s, VEC<double>& cols_) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  int r = cols_.size();
  int c = inp.nc();

  VEC<double> ret(r, c);

  for(int i = 0; i < r; i++) {
     for(int j = 0; j < c; j++) {
      ret[i*inp.nr() + j] =  inp[cols_[i]-1 + j*c];  // user start counting at 1
     }
  }

  return ret;
}

/*
desired positions
*/
VEC<double> subset(VEC<double>&inp, VEC<double>& rows_, char s) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  int r = rows_.size();
  int c = inp.nc();

  VEC<double> ret(r, c);

  for(int i = 0; i < r; i++) {
     for(int j = 0; j < c; j++) {
       ret[i*inp.nr() + j] = inp[j + (rows_[i]-1)*c]; // user start counting at 1
     }
  }

  return ret;
}


/*
desired positions
*/
VEC<double> subset(VEC<double>&inp, VEC<double>& rows_, VEC<double>& cols_) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  int r = rows_.size();
  int c = cols_.size();

  VEC<double> ret(r, c);

  for(int i = 0; i < r; i++) {
     for(int j = 0; j < c; j++) {
       ret[i*r + j] = inp[(rows_[i]-1)*inp.nr() + cols_[j] -1]; // user start counting at 1
     }
  }

  return ret;
}

// subsetting at LHS
// ================================================================
/*
desired positions
*/
VEC<double>& self(VEC<double>& inp, VEC<double>& ip) {

  inp.subsetted = true;
  inp.indices.resize(ip.size());
  for(size_t i = 0; i < inp.indices.size(); i++) {
    inp.indices[i] = static_cast<int>(ip[i]) -1;
  }
  return inp;
}

/*
one position
*/
VEC<double>& self(VEC<double>& inp, int pos) {
  pos--;
  inp.subsetted = true;
  inp.indices.resize(1);
  inp.indices[0] = pos;
  return inp;
}


/*
desired positions
*/
VEC<double>& self(VEC<double>&inp, VEC<double>& rows_, VEC<double>& cols_) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  int r = rows_.size();
  int c = cols_.size();
  inp.indices.resize(r*c);

  for(int i = 0; i < r; i++) {
     for(int j = 0; j < c; j++) {
       inp.indices[i*r + j] = i*r + j;
     }
  }

  return inp;
}


/*
desired positions
*/
VEC<double>& self(VEC<double>&inp, char s, VEC<double>& cols_) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  int r = inp.nr();
  int c = cols_.size();
  inp.indices.resize(r*c);

  for(int i = 0; i < r; i++) {
     for(int j = 0; j < c; j++) {
       inp.indices[i*inp.nr() + j] = i*inp.nr() + j;
     }
  }

  return inp;
}


/*
desired positions
*/
VEC<double>& self(VEC<double>&inp, VEC<double>& rows_, char s) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  int r = rows_.size();
  int c = inp.nc();
  inp.indices.resize(r*c);

  for(int i = 0; i < r; i++) {
     for(int j = 0; j < c; j++) {
       inp.indices[i*inp.nr() + j] = i*inp.nr() + j;
     }
  }

  return inp;
}


#endif

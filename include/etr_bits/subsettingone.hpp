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


#ifndef SUBSETTING_ONE
#define SUBSETTING_ONE

#include "vec.hpp"


VEC<double> subset(VEC<double>& inp) {
  VEC<double> ret = inp;

  return ret;
}


VEC<double> subset(VEC<double>& inp, int pos) {
  VEC<double> ret(1);
  pos--;
  ret[0] = inp[pos];

  return ret;
}


VEC<double> subset(VEC<double>& inp, double pos_) {
  VEC<double> ret(1);
  int pos = static_cast<int>(pos_);
  pos--;
  ret[0] = inp[pos];

  return ret;
}


VEC<double> subset(VEC<double>& inp, bool all) {
  if(all == true) {
      VEC<double> ret = inp;
      return ret;
  } else if(all == false) { // maybe abort program
    VEC<double> ret;
    return ret;
  }
  std::cerr << "error during comparison" << std::endl;
  exit(0);
  return inp;
}


VEC<double> subset(VEC<double>& inp, int r, int c) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(1);
  r--;
  c--;
  int pos = c*inp.nr() + r;

  ret[0] = inp[pos];

  return ret;
}

VEC<double> subset(VEC<double>& inp, double r_, double c_) {
  int r = static_cast<int>(r_);
  int c = static_cast<int>(c_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(1);
  r--;
  c--;
  int pos = c*inp.nr() + r;

  ret[0] = inp[pos];

  return ret;
}

VEC<double> subset(VEC<double>& inp, int r, double c_) {
  int c = static_cast<int>(c_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(1);
  r--;
  c--;
  int pos = c*inp.nr() + r;

  ret[0] = inp[pos];

  return ret;
}

VEC<double> subset(VEC<double>& inp, double r_, int c) {
  int r = static_cast<int>(r_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(1);
  r--;
  c--;
  int pos = c*inp.nr() + r;

  ret[0] = inp[pos];

  return ret;
}

VEC<double> subset(VEC<double>& inp, int r, bool cols) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  if(cols == false) {
    VEC<double> empty;
    return empty;
  }

  VEC<double> ret(inp.nc());
  int pst = 0;

  for(int i = 0; i < ret.size(); i++) {
      pst = i*inp.nr() + r - 1;
      ret[i] = inp[pst];
  }

  return ret;
}


VEC<double> subset(VEC<double>& inp, double r_, bool cols) {

  int r = static_cast<int>(r_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  if(cols == false) {
    VEC<double> empty;
    return empty;
  }

  VEC<double> ret(inp.nc());
  int pst = 0;

  for(int i = 0; i < ret.size(); i++) {
      pst = i*inp.nc() + r - 1;
      ret[i] = inp[pst];
  }

  return ret;
}


VEC<double> subset(VEC<double>& inp, bool rows, bool cols) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  if( (cols == false) || (rows == false) ) {
    VEC<double> empty;
    return empty;
  }

  VEC<double> ret;
  ret = inp;

  return ret;
}

VEC<double> subset(VEC<double>& inp, bool rows, int c) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  if(rows == false) {
    VEC<double> empty;
    return empty;
  }

  VEC<double> ret(inp.nr());
  int pst = 0;

  for(int i = 0; i < ret.size(); i++) {
      pst = (c-1)*inp.nr() + i;
      ret[i] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, bool rows, double c_) {

  int c = static_cast<int>(c_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  if(rows == false) {
    VEC<double> empty;
    return empty;
  }

  VEC<double> ret(inp.nr());
  int pst = 0;

  for(int i = 0; i < ret.size(); i++) {
      pst = (c-1)*inp.nr() + i;
      ret[i] = inp[pst];
  }

  return ret;
}





#endif

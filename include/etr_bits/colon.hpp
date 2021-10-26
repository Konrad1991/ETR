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


#ifndef COLON_H
#define COLON_H

#include "vec.hpp"


VEC<double> colon(int start, int end) {
  VEC<double> ret(end - start + 1);
  for(int i = 0; i < ret.size(); i++) {
    ret[i] = start + static_cast<double>(i);
  }

  return ret;
}

int length(double inp) {
  return 1;
}

int length(int inp) {
  return 1;
}

int length(bool inp) {
  return 1;
}

template<typename T>
int length(VEC<T>& inp) {
  return inp.size();
}

VEC<double> dim(VEC<T>& inp) {
  if(inp.im() == false) {
    std::cerr << "dim can only be called with matrix" << std::endl;
    exit(0);
  }

  VEC<double> ret(2);

  ret(1) = inp.nr();
  ret(2) = inp.nc();

  return ret;
}


void dim(bool inp) {
    std::cerr << "dim can only be called with matrix" << std::endl;
    exit(0);
}

void dim(int inp) {
    std::cerr << "dim can only be called with matrix" << std::endl;
    exit(0);
}

void dim(double inp) {
    std::cerr << "dim can only be called with matrix" << std::endl;
    exit(0);
}

#endif

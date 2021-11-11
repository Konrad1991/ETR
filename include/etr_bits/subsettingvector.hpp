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


#ifndef SUBSETTING_VEC
#define SUBSETTING_VEC

#include "vec.hpp"

VEC<double> subset(VEC<double>& inp, VEC<double>&& pos) {
  VEC<double> ret(pos.size());
  for(int i = 0; i < ret.size(); i++) {
    ret[i] = inp[d2i(pos[i]) - 1];
  }

  return ret;
}


VEC<double> subset(VEC<double>& inp, VEC<double>& pos) {
  VEC<double> ret(pos.size());
  for(int i = 0; i < ret.size(); i++) {
    ret[i] = inp[d2i(pos[i]) - 1];
  }

  return ret;
}


VEC<double> subset(VEC<double>& inp, VEC<bool>& pos) {

  int counter = 0;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
    }
  }

  VEC<double> ret(counter);

  counter = 0;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
        ret[counter] = inp[static_cast<int>(pos[i]) - 1];
        counter++;
    }
  }

  return ret;
}



VEC<double> subset(VEC<double>& inp, VEC<bool>&& pos) {

  int counter = 0;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
    }
  }

  VEC<double> ret(counter);

  counter = 0;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
        ret[counter] = inp[i - 1];
        counter++;
    }
  }

  return ret;
}


#endif

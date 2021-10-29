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

#ifndef STACK
#define STACK

#include "header.hpp"


class STCK {

public:
  std::vector<std::vector<int> > stack;
  size_t sz;

  STCK(std::vector<int>&& inp) {
    stack.resize(1);
    stack.push_back(inp);
    sz = stack.size();
  }

  STCK() : sz(0) {
    stack.resize(1);
  }

  void get(std::vector<int>& inp) {
    if(sz >= 1) {
        inp.resize(stack[sz].size());
        for(int i = 0; i < inp.size(); i++) {
          inp[i] = stack[sz][i];
        }
        sz--;
    }  else {
      std::cerr << "error stack interface" << std::endl;
      exit(0);
    }
  }

  STCK& operator=(std::vector<int>& inp) {

    stack.push_back(inp);
    sz++;
    return *this;
  }

  ~STCK() {
    if(sz != 0) {
      exit(0);
    }
  }

};

#endif

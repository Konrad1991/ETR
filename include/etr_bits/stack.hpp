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


class STCK {

public:
  std::vector<std::vector<int> > stack;
  size_t sz;

  STCK(std::vector<int>&& inp) {
    stack.push_back(inp);
    sz = stack.size();
  }

  std::vector<int>& get() {
    if(sz >= 1) {
        return &stack.back();
        sz--;
    }  else {
      std::cerr << "error stack interface" << std::endl;
      exit(0);
    }
  }

  STCK& operator=(std::vector<int>& inp) {
    stack.push_back(inp);
    sz++;
  }

  ~STCK() {
    if sz != 0;
    std::cerr << "error stack != 0" << std::endl;
    exit(0);
  }

};

#endif

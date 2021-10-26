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


#ifndef PRINT
#define PRINT

#include "vec.hpp"

// print empty line
void print() {
  std::cout << std::endl;
}

void print(std::string inp) {
  std::cout << inp << std::endl;
}


void print(double inp){
  std::cout << inp << std::endl;
}

void print(int inp){
  std::cout << inp << std::endl;
}

void print(bool inp) {
  std::cout << inp << std::endl;
}


// Vector & matrix
// print fct
// ================================================================
void print(const VEC<double>& inp) { // const

    if(inp.ismatrix == false) {
      for(int i = 0; i < inp.size(); i++) {
        std::cout << inp[i] << std::endl;
      }
    } else if(inp.ismatrix == true) {
      for(int i = 0; i < inp.nrows; i++) {
        for(int j = 0; j < inp.ncols; j++) {
          std::cout << inp.d[i*inp.nrows + j] << "\t";
        }
          std::cout << std::endl;
      }
    }
}



#endif

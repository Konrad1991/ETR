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


#ifndef SUBSETTING_MAT
#define SUBSETTING_MAT

// subset mat helper
double smh(VEC<double>& inp, int r, int c) {
  double ret;
  r--;
  c--;
  int pos = c*inp.nr() + r;
  ret = inp[pos];
  return ret;
}


/*
subsetting:

int, vec bool
double, vec bool

vec bool, int
vec bool, double
vec double, int
vec double, double

vec bool, bool
bool, vec bool
vec double, bool
bool, vec double

vec double, vec double



// missing:
int, vec double
double, vec double
*/


VEC<double> subset(VEC<double>& inp, int row, VEC<bool>& pos) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < positions.size(); j++) {
    pst = (positions[j])*inp.nr() + row -1;
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, int row, VEC<bool>&& pos) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < positions.size(); j++) {
    pst = (positions[j])*inp.nr() + row -1;
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, double row_, VEC<bool>& pos) {

  int row = static_cast<int>(row_);
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < positions.size(); j++) {
    pst = (positions[j])*inp.nr() + row -1;
    ret[j] = inp[pst];
  }

  return ret;
}



VEC<double> subset(VEC<double>& inp, double row_, VEC<bool>&& pos) {

  int row = static_cast<int>(row_);
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < positions.size(); j++) {
    pst = (positions[j])*inp.nr() + row -1;
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<bool>& pos, int col) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + positions[j];
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<bool>&& pos, int col) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + positions[j];
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<bool>& pos, double col_) {

  int col = static_cast<int>(col_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + positions[j];
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<bool>&& pos, double col_) {

  int col = static_cast<int>(col_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + positions[j];
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>& pos, int col) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = pos.size();
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + (pos[j]-1);
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>&& pos, int col) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = pos.size();
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + (pos[j]-1);
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>& pos, double col_) {

  int col = d2i(col_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = pos.size();
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + (pos[j]-1);
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>&& pos, double col_) {

  int col = d2i(col_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nc());
  ret.ismatrix = true;
  ret.ncols = 1;
  ret.nrows = pos.size();
  int curr_r = 0;
  int pst = 0;

  for(int j = 0; j < ret.nr(); j++) {
    pst = (col-1)*inp.nr() + (pos[j]-1);
    ret[j] = inp[pst];
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<bool>& pos, bool substitute) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = inp.nc();
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    for(int j = 0; j < ret.nr(); j++) {
      pst = i*inp.nr() + positions[j];
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<bool>&& pos, bool substitute) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(counter * inp.nc());
  ret.ismatrix = true;
  ret.ncols = inp.nc();
  ret.nrows = counter;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    for(int j = 0; j < ret.nr(); j++) {
      pst = i*inp.nr() + positions[j];
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, bool substitute, VEC<bool>& pos) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(inp.nr()*counter);
  ret.ismatrix = true;
  ret.ncols = counter;
  ret.nrows = inp.nr();
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    for(int j = 0; j < ret.nr(); j++) {
      pst = inp.nr()*positions[i] + j;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, bool substitute, VEC<bool>&& pos) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }


  int counter = 0;
  std::vector<int> positions;
  for(int i = 0; i < pos.size(); i++) {
    if(pos[i] == true) {
      counter++;
      positions.push_back(i);
    }
  }

  VEC<double> ret(inp.nr()*counter);
  ret.ismatrix = true;
  ret.ncols = counter;
  ret.nrows = inp.nr();
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    for(int j = 0; j < ret.nr(); j++) {
      pst = inp.nr()*positions[i] + j;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>& pos, bool substitute) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nc());
  ret.ismatrix = true;
  ret.ncols = inp.nc();
  ret.nrows = pos.size();
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    for(int j = 0; j < ret.nr(); j++) {
      pst = i*inp.nr() + d2i(pos[j]-1);
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>&& pos, bool substitute) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nc());
  ret.ismatrix = true;
  ret.ncols = inp.nc();
  ret.nrows = pos.size();
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    for(int j = 0; j < ret.nr(); j++) {
      pst = i*inp.nr() + d2i(pos[j]-1);
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, bool substitute, VEC<double>& pos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nr());
  ret.ismatrix = true;
  ret.ncols = pos.size();
  ret.nrows = inp.nr();
  int curr_c = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    curr_c = static_cast<int>(pos[i]) - 1;
    for(int j = 0; j < ret.nr(); j++) {

      pst = curr_c*inp.nr() + j;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, bool substitute, VEC<double>&& pos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(pos.size() * inp.nr());
  ret.ismatrix = true;
  ret.ncols = pos.size();
  ret.nrows = inp.nr();
  int curr_c = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    curr_c = static_cast<int>(pos[i]) - 1;
    for(int j = 0; j < ret.nr(); j++) {

      pst = curr_c*inp.nr() + j;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>& rpos, VEC<double>& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(rpos.size() * cpos.size());
  ret.ismatrix = true;
  ret.ncols = cpos.size();
  ret.nrows = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < ret.nr(); j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nr() + curr_r;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>&& rpos, VEC<double>& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(rpos.size() * cpos.size());
  ret.ismatrix = true;
  ret.ncols = cpos.size();
  ret.nrows = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < ret.nr(); j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nr() + curr_r;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>& rpos, VEC<double>&& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(rpos.size() * cpos.size());
  ret.ismatrix = true;
  ret.ncols = cpos.size();
  ret.nrows = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < ret.nr(); j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nr() + curr_r;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

VEC<double> subset(VEC<double>& inp, VEC<double>&& rpos, VEC<double>&& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret(rpos.size() * cpos.size());
  ret.ismatrix = true;
  ret.ncols = cpos.size();
  ret.nrows = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < ret.nc(); i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < ret.nr(); j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nr() + curr_r;
      ret[i*ret.nr() + j] = inp[pst];
    }
  }

  return ret;
}

#endif

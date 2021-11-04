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


#ifndef subassignTINGASSIGN
#define subassignTINGASSIGN

#include "vec.hpp"

VEC<double>& subassign(VEC<double>& inp) {
  return inp;
}


VEC<double>& subassign(VEC<double>& inp, int pos) {
  pos--;
  inp.indices.resize(1);
  inp.indices[0] = pos;
  inp.subsetted = true;

  return inp;
}


VEC<double>& subassign(VEC<double>& inp, double pos_) {
  int pos = static_cast<int>(pos_);
  pos--;
  inp.indices.resize(1);
  inp.indices[0] = pos;
  inp.subsetted = true;

  return inp;
}


VEC<double>& subassign(VEC<double>& inp, bool all) {
  if(all == true) {
    return inp;
  } else if(all == false) {  // maybe abort program
    inp.subsetted = true;
    inp.indices.resize(0);
    return inp;
  }

  std::cerr << "error during comparison" << std::endl;
  exit(0);
  return inp;
}

VEC<double>& subassign(VEC<double>& inp, int r, int c) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  r--;
  c--;
  int pos = c*inp.nr() + r;
  inp.indices.resize(1);

  inp.indices[0] = pos;
  inp.subsetted = true;

  return inp;
}


VEC<double>& subassign(VEC<double>& inp, double r_, double c_) {
  int r = static_cast<int>(r_);
  int c = static_cast<int>(c_);

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  r--;
  c--;
  int pos = c*inp.nr() + r;
  inp.indices.resize(1);

  inp.indices[0] = pos;
  inp.subsetted = true;

  return inp;
}


VEC<double>& subassign(VEC<double>& inp, VEC<double>&& pos) {
  inp.indices.resize(pos.size());
  for(int i = 0; i < pos.size(); i++) {
    inp.indices[i] = d2i(pos[i]) - 1;
  }
  inp.subsetted = true;

  return inp;
}

VEC<double>& subassign(VEC<double>& inp, VEC<double>& pos) {
  inp.indices.resize(pos.size());
  for(int i = 0; i < pos.size(); i++) {
    inp.indices[i] = d2i(pos[i]) - 1;
  }
  inp.subsetted = true;

  return inp;
}





VEC<double>& subassign(VEC<double>& inp, VEC<double>& pos, bool substitute) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }
  inp.subsetted = true;
  inp.ncols_sub = inp.nc();
  inp.nrows_sub = pos.size();
  int curr_r = 0;
  int pst = 0;
  inp.indices.resize(inp.nc()*pos.size());

  for(int i = 0; i < inp.nrows_sub; i++) {
    curr_r = static_cast<int>(pos[i]) - 1;
    for(int j = 0; j < inp.ncols_sub; j++) {
      pst = j*inp.nr() + curr_r;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}


VEC<double>& subassign(VEC<double>& inp, VEC<double>&& pos, bool substitute) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }
  inp.subsetted = true;
  inp.ncols_sub = inp.nc();
  inp.nrows_sub = pos.size();
  int curr_r = 0;
  int pst = 0;
  inp.indices.resize(inp.nc()*pos.size());

  for(int i = 0; i < inp.nrows_sub; i++) {
    curr_r = static_cast<int>(pos[i]) - 1;
    for(int j = 0; j < inp.ncols_sub; j++) {
      pst =  j*inp.nr() + curr_r;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}






VEC<double>& subassign(VEC<double>& inp, bool substitute, VEC<double>& pos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  inp.indices.resize(pos.size() * inp.nrows_sub);
  inp.subsetted = true;
  inp.ncols_sub = pos.size();
  inp.nrows_sub = inp.nr();
  int curr_c = 0;
  int pst = 0;

  for(int i = 0; i < inp.ncols_sub; i++) {
    curr_c = static_cast<int>(pos[i]) - 1;
    for(int j = 0; j < inp.nrows_sub; j++) {
      pst = curr_c*inp.nrows_sub + j;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}


VEC<double>& subassign(VEC<double>& inp, bool substitute, VEC<double>&& pos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  inp.indices.resize(pos.size() * inp.nrows_sub);
  inp.subsetted = true;
  inp.ncols_sub = pos.size();
  inp.nrows_sub = inp.nr();
  int curr_c = 0;
  int pst = 0;

  for(int i = 0; i < inp.ncols_sub; i++) {
    curr_c = static_cast<int>(pos[i]) - 1;
    for(int j = 0; j < inp.nrows_sub; j++) {
      pst = curr_c*inp.nrows_sub + j;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}





VEC<double>& subassign(VEC<double>& inp, VEC<double>& rpos, VEC<double>& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  inp.indices.resize(rpos.size() * cpos.size());
  inp.subsetted = true;
  inp.ncols_sub = cpos.size();
  inp.nrows_sub = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < inp.ncols_sub; i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < inp.nrows_sub; j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nrows_sub + curr_r;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}



VEC<double>& subassign(VEC<double>& inp, VEC<double>&& rpos, VEC<double>& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  inp.indices.resize(rpos.size() * cpos.size());
  inp.subsetted = true;
  inp.ncols_sub = cpos.size();
  inp.nrows_sub = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < inp.ncols_sub; i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < inp.nrows_sub; j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nrows_sub + curr_r;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}



VEC<double>& subassign(VEC<double>& inp, VEC<double>& rpos, VEC<double>&& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  inp.indices.resize(rpos.size() * cpos.size());
  inp.subsetted = true;
  inp.ncols_sub = cpos.size();
  inp.nrows_sub = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < inp.ncols_sub; i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < inp.nrows_sub; j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nrows_sub + curr_r;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}



VEC<double>& subassign(VEC<double>& inp, VEC<double>&& rpos, VEC<double>&& cpos) {
  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  inp.indices.resize(rpos.size() * cpos.size());
  inp.subsetted = true;
  inp.ncols_sub = cpos.size();
  inp.nrows_sub = rpos.size();
  int curr_c = 0;
  int curr_r = 0;
  int pst = 0;

  for(int i = 0; i < inp.ncols_sub; i++) {
    curr_c = d2i(cpos[i]) - 1;
    for(int j = 0; j < inp.nrows_sub; j++) {
      curr_r = d2i(rpos[j]) -1;
      pst = curr_c*inp.nrows_sub + curr_r;
      inp.indices[i*inp.nrows_sub + j] = pst;
    }
  }

  return inp;
}







#endif

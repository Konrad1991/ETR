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
start and end
*/
VEC<double> subset(VEC<double>& inp, int start, int end) {
  VEC<double> t;
  start--;
  end--;
  t.d.resize(end - start + 1);

  for(int i = 0; i < t.d.size(); i++) {
    t.d[i] = inp[i + start];
  }
  return t;
}


/*
desired positions
*/
VEC<double> subset(VEC<double>& inp, VEC<double>&& ip) {

  VEC<double> t;
  int start = ip[0] - 1;
  int end = ip.d.back() - 1;

  t.d.resize((end -1) - (start -1) + 1);
  for(int i = 0; i < t.d.size(); i++) {
    t.d[i] = inp[start + i];
  }
  return t;
}

/*
desired positions
*/
VEC<double> subset(VEC<double>& inp, VEC<double> ip) {

  VEC<double> t;
  int start = ip[0] - 1;
  int end = ip.d.back() - 1;

  t.d.resize((end -1) - (start -1) + 1);
  for(int i = 0; i < t.d.size(); i++) {
    t.d[i] = inp[start + i];
  }
  return t;
}

/*
desired positions
*/
VEC<double> subset(VEC<double>& inp, std::vector<double>&& ip) {

  VEC<double> t;
  int start = ip[0] - 1;
  int end = ip.back() - 1;

  t.d.resize((end -1) - (start -1) + 1);
  for(int i = 0; i < t.d.size(); i++) {
    t.d[i] = inp[start + i];
  }
  return t;
}

/*
desired positions
*/
VEC<double> subset(VEC<double>& inp, std::vector<double> ip) {

  VEC<double> t;
  int start = ip[0] - 1;
  int end = ip.back() - 1;

  t.d.resize((end -1) - (start -1) + 1);
  for(int i = 0; i < t.d.size(); i++) {
    t.d[i] = inp[start + i];
  }
  return t;
}











/*
one position
*/
double subset(VEC<double>& inp, int pos) {
  pos--;
  return inp[pos];
}



/*
desired positions
*/
VEC<double> subset(VEC<double>&inp, VEC<double>& rows_, VEC<double>& cols_) {

  if(inp.ismatrix == false) {
    std::cerr << "incorrect number of dimensions" << std::endl;
    exit(0);
  }

  VEC<double> ret( (rows_.size())*(cols_.size()));

  for(int i = 0; i < rows_.size(); i++) {
     for(int j = 0; j < cols_.size(); j++) {
       ret[i*static_cast<int>(rows_.size()) + j] = inp.d[i *static_cast<int>(rows_.size()) + j];
     }
  }

  ret.ismatrix = true;
  ret.ncols = cols_.size();
  ret.nrows = rows_.size();

  return ret;
}

// subsetting at LHS
// ================================================================
/*
start and end
*/
VEC<double>& self(VEC<double>& inp, int start, int end) {

  inp.subsetted = true;
  inp.indices.resize((end -1) - (start -1) + 1);
  for(size_t i = 0; i < inp.indices.size(); i++) {
    inp.indices[i] = start + i -1;
  }
  return inp;
}


/*
desired positions
*/
VEC<double>& self(VEC<double>& inp, VEC<double>& ip) {

  int start = ip[0] - 1;
  int end = ip.d.back() - 1;

  inp.subsetted = true;
  inp.indices.resize((end -1) - (start -1) + 1);
  for(size_t i = 0; i < inp.indices.size(); i++) {
    inp.indices[i] = start + i -1;
  }
  return inp;
}

/*
desired positions
*/
VEC<double>& self(VEC<double>& inp, VEC<double> ip) {

  int start = ip[0] - 1;
  int end = ip.d.back() - 1;

  inp.subsetted = true;
  inp.indices.resize((end -1) - (start -1) + 1);
  for(size_t i = 0; i < inp.indices.size(); i++) {
    inp.indices[i] = start + i -1;
  }
  return inp;
}


/*
desired positions
*/
VEC<double>& self(VEC<double>& inp, std::vector<double>& ip) {

  int start = ip[0] - 1;
  int end = ip.back() - 1;

  inp.subsetted = true;
  inp.indices.resize((end -1) - (start -1) + 1);
  for(size_t i = 0; i < inp.indices.size(); i++) {
    inp.indices[i] = start + i -1;
  }
  return inp;
}

/*
desired positions
*/
VEC<double>& self(VEC<double>& inp, std::vector<double> ip) {

  int start = ip[0] - 1;
  int end = ip.back() - 1;

  inp.subsetted = true;
  inp.indices.resize((end -1) - (start -1) + 1);
  for(size_t i = 0; i < inp.indices.size(); i++) {
    inp.indices[i] = start + i -1;
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

#endif

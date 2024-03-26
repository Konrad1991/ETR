#ifndef HEADER_ETR_H
#define HEADER_ETR_H

#include <cstddef>  
#include <cmath>
#include <cxxabi.h>
#include <iostream>
#include <type_traits>

#ifdef STANDALONE_ETR
#else
// [[Rcpp::depends(RcppArmadillo)]]
#include "RcppArmadillo.h"

#endif

#include <ios>
#include <iostream>
#include <iterator>
#include <math.h>
#include <memory>
#include <mutex>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#endif
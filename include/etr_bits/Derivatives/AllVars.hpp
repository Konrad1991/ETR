#ifndef ALLVARS_ETR_H
#define ALLVARS_ETR_H

#include "../Core.hpp"
#include "../BinaryCalculations.hpp"
#include "../UnaryCalculations.hpp"

namespace etr {

template <class F, class... Args> inline F LoopVariadicT(F f, Args &&...args) {
  (f(std::forward<Args>(args)), ...);
  return f;
}

template <int NBuffer_, int NBorrow_, int NBorrowSEXP_> struct AllVars {
  static constexpr int NBuffer = NBuffer_;
  static constexpr int NBorrow = NBorrow_;
  static constexpr int NBorrowSEXP = NBorrowSEXP_;
  std::array<Vec<BaseType, Buffer<BaseType>> *, NBuffer> varBuffer;
  std::array<Vec<BaseType, Borrow<BaseType>> *, NBorrow> varBorrow;
  std::array<Vec<BaseType, BorrowSEXP<BaseType>> *, NBorrowSEXP> varBorrowSEXP;

  std::array<Buffer<BaseType>, NBuffer> varBufferDerivs;
  std::array<Buffer<BaseType>, NBorrow> varBorrowDerivs;
  std::array<Buffer<BaseType>, NBorrowSEXP> varBorrowSEXPDerivs;
  int IndepVarIdx;
  int IndepVarTypeIdx;
  bool DerivInit = false;

  AllVars(int IndepVarIdx_, int IndepVarTypeIdx_) : 
      IndepVarIdx(IndepVarIdx_), IndepVarTypeIdx(IndepVarTypeIdx_) {}

  template <typename... Args> void initBuffer(Args &&...args) {
    int idx = 0;
    LoopVariadicT(
        [&](auto arg) {
          this->varBuffer[idx] = arg;
          idx++;
        },
        args...);
  }

  template <typename... Args> void initBorrow(Args &&...args) {
    int idx = 0;
    LoopVariadicT(
        [&](auto arg) {
          this->varBorrow[idx] = arg;
          idx++;
        },
        args...);
  }

  template <typename... Args> void initBorrowSEXP(Args &&...args) {
    int idx = 0;
    LoopVariadicT(
        [&](auto arg) {
          this->varBorrowSEXP[idx] = arg;
          idx++;
        },
        args...);
  }

  std::size_t size(size_t Idx, int TypeIdx) const {
    if (TypeIdx == 0) {
      return varBuffer[Idx]->size();
    } else if (TypeIdx == 1) {
      return varBorrow[Idx]->size();
    } else if (TypeIdx == 2) {
      // return varBorrowSEXP[Idx]->size();
    }
  }

  bool im(size_t Idx, int TypeIdx) const {
    if (TypeIdx == 0) {
      return varBuffer[Idx]->im();
    } else if (TypeIdx == 1) {
      return varBorrow[Idx]->im();
    } else if (TypeIdx == 2) {
      return varBorrowSEXP[Idx]->im();
    }
  }

  std::size_t nr(size_t Idx, int TypeIdx) const {
    if (TypeIdx == 0) {
      return varBuffer[Idx]->nr();
    } else if (TypeIdx == 1) {
      return varBorrow[Idx]->nr();
    } else if (TypeIdx == 2) {
      return varBorrowSEXP[Idx]->nr();
    }
  }

  std::size_t nc(size_t Idx, int TypeIdx) const {
    if (TypeIdx == 0) {
      return varBuffer[Idx]->nc();
    } else if (TypeIdx == 1) {
      return varBorrow[Idx]->nc();
    } else if (TypeIdx == 2) {
      return varBorrowSEXP[Idx]->nc();
    }
  }

  void resize(size_t Idx, int TypeIdx, size_t newSize) {
    if (TypeIdx == 0) {
      return varBuffer[Idx]-> resize(newSize);
    } else if (TypeIdx == 1) {
      return varBorrow[Idx]->resize(newSize);
    } else if (TypeIdx == 2) {
      // issue: check why it is not working. But varBorrow should not work!
      // return varBorrowSEXP[Idx]->resize(newSize);
    }
   } 
};

}

#endif

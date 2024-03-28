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
  std::array<Buffer<BaseType>, NBuffer + NBorrow + NBorrowSEXP> Derivs;
  size_t IndepVarIdx = 0;
  std::array<size_t, NBuffer + NBorrow + NBorrowSEXP> VarSizes;

  AllVars(size_t IndepVarIdx_) : IndepVarIdx(IndepVarIdx_) {}

  template <typename... Args> void initBuffer(Args &&...args) {
    int idx = 0;
    LoopVariadicT(
        [&](auto arg) {
          this->varBuffer[idx] = arg;
          this->VarSizes[idx] = arg->size();
          idx++;
        },
        args...);
  }

  template <typename... Args> void initBorrow(Args &&...args) {
    int idx = 0;
    LoopVariadicT(
        [&](auto arg) {
          this->varBorrow[idx] = arg;
          this->VarSizes[idx + NBuffer] = arg->size();
          idx++;
        },
        args...);
  }

  template <typename... Args> void initBorrowSEXP(Args &&...args) {
    int idx = 0;
    LoopVariadicT(
        [&](auto arg) {
          this->varBorrowSEXP[idx] = arg;
          this->VarSizes[idx + NBuffer + NBorrow] = arg->size();
          idx++;
        },
        args...);
  }

  std::size_t size(size_t Idx) const {
    if (Idx < NBuffer) {
      return varBuffer[Idx]->size();
    } else if (Idx >= NBuffer && Idx < NBorrowSEXP) {
      return varBorrow[Idx - NBuffer]->size();
    } else {
      return varBorrowSEXP[Idx - NBuffer - NBorrowSEXP]->size();
    }
  }

  bool im(size_t Idx) const {
    if (Idx < NBuffer) {
      return varBuffer[Idx]-> im();
    } else if (Idx >= NBuffer && Idx < NBorrowSEXP) {
      return varBorrow[Idx - NBuffer]-> im();
    } else {
      return varBorrowSEXP[Idx - NBuffer - NBorrowSEXP]-> im();
    }
  }

  std::size_t nr(size_t Idx) const {
    if (Idx < NBuffer) {
      return varBuffer[Idx]->nr();
    } else if (Idx >= NBuffer && Idx < NBorrowSEXP) {
      return varBorrow[Idx - NBuffer]->nr();
    } else {
      return varBorrowSEXP[Idx - NBuffer - NBorrowSEXP]->nr();
    }
  }

  std::size_t nc(size_t Idx) const {
    if (Idx < NBuffer) {
      return varBuffer[Idx]->nc();
    } else if (Idx >= NBuffer && Idx < NBorrowSEXP) {
      return varBorrow[Idx - NBuffer]->nc();
    } else {
      return varBorrowSEXP[Idx - NBuffer - NBorrowSEXP]->nc();
    }
  }
};

}

#endif
#ifndef VAR_POINTER_ETR_H
#define VAR_POINTER_ETR_H

#include "../Core.hpp"
#include "../BinaryCalculations.hpp"
#include "../UnaryCalculations.hpp"

namespace etr {

template <typename T, int Idx, int TypeIdx, typename Trait>
struct VarPointer {
  using TypeTrait = Trait;
  using CaseTrait = Trait;
  using Type = T;
  using RetType = T;
  static constexpr int I = Idx;
  static constexpr int TIdx = TypeIdx;
  
  T &AllVarsRef;
  VarPointer(T &AllVars_) : AllVarsRef(AllVars_) {}

  size_t size() const { return AllVarsRef.size(Idx, TypeIdx); }

  bool im() const { return AllVarsRef.im(Idx, TypeIdx); }

  size_t nr() const { return AllVarsRef.nr(Idx, TypeIdx); }

  size_t nc() const { return AllVarsRef.nc(Idx, TypeIdx); }

  void resize(size_t newSize) {
    AllVarsRef.resize(Idx, TIdx, newSize);
  }

  template <typename AV> static size_t getSize(AV &av) {
    if constexpr (TypeIdx == 0) {
      return av.varBuffer[Idx] -> size();
    } else if constexpr(TypeIdx == 1) {
      return av.varBorrow[Idx] -> size();
    } else if constexpr(TypeIdx == 2) {
      return av.varBorrowSEXP[Idx] -> size();
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  auto get() const {
    if constexpr (TypeIdx == 0) {
      return AllVarsRef.varBuffer[Idx];
    } else if constexpr(TypeIdx == 1) {
      return AllVarsRef.varBorrow[Idx];
    } else if constexpr(TypeIdx == 2) {
      return AllVarsRef.varBorrowSEXP[Idx];
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  template <typename AV> static auto getVal(AV &av, size_t VecIdx) {
    if constexpr (TypeIdx == 0) {
      return av.varBuffer[Idx] ->operator[](VecIdx);
    } else if constexpr(TypeIdx == 1) {
      return av.varBorrow[Idx] ->operator[](VecIdx);
    } else if constexpr(TypeIdx == 2) {
      return av.varBorrowSEXP[Idx] ->operator[](VecIdx);
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  template <typename AV> static auto getDeriv(AV &av, size_t VecIdx) {
    if constexpr (TypeIdx == 0) {
      if (av.varBufferDerivs[Idx].size() != av.varBuffer[Idx] -> size()) {
        av.varBufferDerivs[Idx].resize(av.varBuffer[Idx]->size());
        if ( (Idx == av.IndepVarIdx) && !av.DerivInit) {
          av.varBufferDerivs[Idx].fill(1.0); 
          av.DerivInit = true;
        } 
      }
      return av.varBufferDerivs[Idx][VecIdx];
    } else if constexpr(TypeIdx == 1) {
      if (av.varBorrowDerivs[Idx].size() != av.varBorrow[Idx] -> size()) {
        av.varBorrowDerivs[Idx].resize(av.varBorrow[Idx]->size());
        if ( (Idx == av.IndepVarIdx) && !av.DerivInit) {
          av.varBorrowDerivs[Idx].fill(1.0); 
          av.DerivInit = true;
        } 
      }
      return av.varBorrowDerivs[Idx][VecIdx];
    } else if constexpr(TypeIdx == 2) {
      if (av.varBorrowSEXPDerivs[Idx].size() != av.varBorrowSEXP[Idx] -> size()) {
        av.varBorrowSEXPDerivs[Idx].resize(av.varBorrowSEXP[Idx]->size());
        if ( (Idx == av.IndepVarIdx) && !av.DerivInit) {
          av.varBorrowSEXPDerivs[Idx].fill(1.0); 
          av.DerivInit = true;
        } 
      }
      return av.varBorrowSEXPDerivs[Idx][VecIdx];
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  template <typename AV, typename Val> static auto setDeriv(AV &av, size_t VecIdx, Val v) {
    if constexpr (TypeIdx == 0) {
      av.varBufferDerivs[Idx][VecIdx] = v;
    } else if constexpr(TypeIdx == 1) {
      av.varBorrowDerivs[Idx][VecIdx] = v;
    } else if constexpr(TypeIdx == 2) {
      av.varBorrowSEXPDerivs[Idx][VecIdx] = v;
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  template <typename AV, typename Val> static auto setVal(AV &av, size_t VecIdx, Val v) {
    if constexpr (TypeIdx == 0) {
      av.varBuffer[Idx] -> operator[](VecIdx) = v;
    } else if constexpr(TypeIdx == 1) {
      av.varBorrow[Idx] -> operator[](VecIdx) = v;
    } else if constexpr(TypeIdx == 2) {
      av.varBorrowSEXP[Idx] -> operator[](VecIdx) = v;
    } else {
      ass(false, "Unknown variable index found");
    }
  }
};


}


#endif

#ifndef VAR_POINTER_ETR_H
#define VAR_POINTER_ETR_H

#include "../Core.hpp"
#include "../BinaryCalculations.hpp"
#include "../UnaryCalculations.hpp"

namespace etr {

template <typename T, int Idx, typename Trait>
struct VarPointer {
  using TypeTrait = Trait;
  using CaseTrait = Trait;
  using Type = T;
  using RetType = T;
  static constexpr int I = Idx;
  
  T &AllVarsRef;
  VarPointer(T &AllVars_) : AllVarsRef(AllVars_) {}

  size_t size() const { return AllVarsRef.size(Idx); }

  bool im() const { return AllVarsRef.im(Idx); }

  size_t nr() const { return AllVarsRef.nr(Idx); }

  size_t nc() const { return AllVarsRef.nc(Idx); }

  template <typename AV> static size_t getSize(AV &av) {
    if constexpr (Idx < av.NBuffer) {
      return av.varBuffer[Idx]->size();
    } else if constexpr (Idx >= av.NBuffer && Idx < (av.NBuffer + av.NBorrow)) {
      return av.varBorrow[Idx - av.NBuffer]->size();
    } else if constexpr (Idx >= (av.NBuffer + av.NBorrow) &&
                         Idx < (av.NBuffer + av.NBorrow + av.NBorrowSEXP)) {
      return av.varBorrowSEXP[Idx - av.NBuffer - av.NBorrowSEXP]->size();
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  auto get() const {
    if constexpr (Idx < AllVarsRef.NBuffer) {
      return AllVarsRef.varBuffer[Idx];
    } else if constexpr (Idx >= AllVarsRef.NBuffer &&
                         Idx < (AllVarsRef.NBuffer + AllVarsRef.NBorrow)) {
      return AllVarsRef.varBorrow[Idx - AllVarsRef.NBuffer];
    } else if constexpr (Idx >= (AllVarsRef.NBuffer + AllVarsRef.NBorrow) &&
                         Idx < (AllVarsRef.NBuffer + AllVarsRef.NBorrow +
                                AllVarsRef.NBorrowSEXP)) {
      return AllVarsRef
          .varBorrowSEXP[Idx - AllVarsRef.NBuffer - AllVarsRef.NBorrowSEXP];
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  template <typename AV> static auto getVal(AV &av, size_t VecIdx) {
    if constexpr (Idx < av.NBuffer) {
      return (av.varBuffer[Idx]->operator[](VecIdx));
    } else if constexpr (Idx >= av.NBuffer && Idx < (av.NBuffer + av.NBorrow)) {
      return av.varBorrow[Idx - av.NBuffer]->operator[](VecIdx);
    } else if constexpr (Idx >= (av.NBuffer + av.NBorrow) &&
                         Idx < (av.NBuffer + av.NBorrow + av.NBorrowSEXP)) {
      return av.varBorrowSEXP[Idx - av.NBuffer - av.NBorrowSEXP]->operator[](
          VecIdx);
    } else {
      ass(false, "Unknown variable index found");
    }
  }

  template <typename AV> static auto getDeriv(AV &av, size_t VecIdx) {
    if constexpr (Idx < av.NBuffer) {
      if (av.varBuffer[Idx]->size() != av.VarSizes[Idx]) {
        av.Derivs[Idx].resize(av.varBuffer[Idx]->size());
        if (Idx == av.IndepVarIdx)
          av.Derivs[Idx].fill(1.0); // issue: correct?
      }
      return av.Derivs[Idx][VecIdx];
    } else if constexpr (Idx >= av.NBuffer && Idx < (av.NBuffer + av.NBorrow)) {
      if (av.varBorrow[Idx - av.NBuffer]->size() != av.VarSizes[Idx]) {
        av.Derivs[Idx].resize(av.varBorrow[Idx - av.NBuffer]->size());
        if (Idx == av.IndepVarIdx)
          av.Derivs[Idx].fill(1.0); // issue: correct?
      }
      return av.Derivs[Idx][VecIdx];
    } else if constexpr (Idx >= (av.NBuffer + av.NBorrow) &&
                         Idx < (av.NBuffer + av.NBorrow + av.NBorrowSEXP)) {
      if (av.varBorrowSEXP[Idx - av.NBuffer - av.NBorrowSEXP]->size() !=
          av.VarSizes[Idx]) {
        av.Derivs[Idx].resize(
            av.varBorrowSEXP[Idx - av.NBuffer - av.NBorrowSEXP]->size());
        if (Idx == av.IndepVarIdx)
          av.Derivs[Idx].fill(1.0); // issue: correct?
      }
      return av.Derivs[Idx][VecIdx];
    } else {
      ass(false, "Unknown variable index found");
    }
  }
};


}


#endif

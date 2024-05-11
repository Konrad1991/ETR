#ifndef GET_DERIV_ETR_H
#define GET_DERIV_ETR_H

namespace etr {

// NOTE: maybe later an additional int argument
// is added specifieng the order of the derivative
template <int Idx, typename T> inline auto get_deriv(T &vec) {
  vec.d.AllVarsRef.varConstants[Idx].resize(vec.d.size());
  for (std::size_t i = 0; i < vec.d.AllVarsRef.varConstants[Idx].size(); i++) {
    vec.d.AllVarsRef.varConstants[Idx][i] = vec.d.getDeriv(vec.d.AllVarsRef, i);
  }
  Vec<double, VarPointer<decltype(vec.d.AllVarsRef), Idx, -1>,
      VariableTypeTrait>
      ret(vec.d.AllVarsRef);
  return ret;
}

} // namespace etr

#endif

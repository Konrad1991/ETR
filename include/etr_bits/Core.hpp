#ifndef UTILSTRAITS_H
#define UTILSTRAITS_H

#include "./Core/BaseStore.hpp"
#include "./Core/Borrow.hpp"
#include "./Core/BorrowSEXP.hpp"
#include "./Core/Concepts.hpp"
#include "./Core/Header.hpp"
#include "./Core/MatrixParameter.hpp"
#include "./Core/Reflection.hpp"
#include "./Core/SubsetClass.hpp"
#include "./Core/Traits.hpp"
#include "./Core/Types.hpp"
#include "./Core/Utils.hpp"

namespace etr {
template <typename T, typename Trait, typename CTrait>
struct Buffer : public BaseStore<T> {
  using RetType = T; // BaseType;
  using TypeTrait = Trait;
  using CaseTrait = CTrait;
};

} // namespace etr

#endif

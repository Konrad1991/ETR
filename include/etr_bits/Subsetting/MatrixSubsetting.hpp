#ifndef SUBSETTING_MATRIX_HPP
#define SUBSETTING_MATRIX_HPP

#include "UtilsSubsetting.hpp"

namespace etr {

/*
      [,1]      [,2]
 [1,] "bool"    "bool"
 [2,] "bool"    "int"
 [3,] "bool"    "double"
 [4,] "bool"    "vec"
 [5,] "bool"    "vecbool"
 [6,] "int"     "bool"
 [7,] "int"     "int"
 [8,] "int"     "double"
 [9,] "int"     "vec"
[10,] "int"     "vecbool"
[11,] "double"  "bool"
[12,] "double"  "int"
[13,] "double"  "double"
[14,] "double"  "vec"
[15,] "double"  "vecbool"
[16,] "vec"     "bool"
[17,] "vec"     "int"
[18,] "vec"     "double"
[19,] "vec"     "vec"
[20,] "vec"     "vecbool"
[21,] "vecbool" "bool"
[22,] "vecbool" "int"
[23,] "vecbool" "double"
[24,] "vecbool" "vec"
[25,] "vecbool" "vecbool"
*/

template <typename T, typename I, typename R, typename C>
inline void calcIndMatrix(T &vec, I &ind, MatrixParameter &mp, const R *idxL,
                          const C *idxR) {
  ass(vec.im(), "incorrect number of dimensions");
  if constexpr (isd<R, bool, C, bool>) {
    if (*idxL && *idxR) {
      ind.resize(vec.size());
      for (std::size_t i = 0; i < vec.size(); i++)
        ind[i] = i;
      mp.setMatrix(vec.d.mp);
      return;
    } else {
      ass(false, "Variable[FALSE, FALSE] subsetting is not supported. Sorry");
      return;
    }
  } else if constexpr (isd<R, bool, C, int>) {
    if (!*idxL) {
      ass(false, "Variable[FALSE, FALSE] subsetting is not supported. Sorry");
      return;
    }
    ind.resize(vec.nr());
    for (std::size_t j = 0; j < vec.nr(); j++) {
      ind[j] = (*idxR - 1) * vec.nr() + j;
    }
    mp.setMatrix(false, 0, 0);
    return;
  } else if constexpr (isd<R, bool, C, double>) {
    if (!*idxL) {
      ass(false, "Variable[FALSE, FALSE] subsetting is not supported. Sorry");
      return;
    }
    ind.resize(vec.nr());
    for (std::size_t j = 0; j < vec.nr(); j++) {
      ind[j] = (static_cast<std::size_t>(*idxR) - 1) * vec.nr() + j;
    }
    mp.setMatrix(false, 0, 0);
    return;
  } else if constexpr (is<R, bool> && IsAV<C>) {
    using DataTypeC = ExtractDataType<C>::RetType;
    if constexpr (is<DataTypeC, bool>) {
      if (!idxL) {
        ass(false, "Variable[FALSE, FALSE] subsetting is not supported. Sorry");
        return;
      }
      std::size_t counter = 0;
      for (std::size_t i = 0; i < idxR->size(); i++) {
        if ((*idxR)[i])
          counter++;
      }
      ass(counter > 0, "subset has to have at least one element");
      BaseStore<std::size_t> positions(counter);
      counter = 0;
      std::size_t counter2 = 0;
      for (std::size_t i = 0; i < idxR->size(); i++) {
        if (((i % vec.nc()) == 0) && i != 0)
          counter2++;
        if ((*idxR)[i]) {
          positions[counter] = i - counter2 * vec.nc();
          counter++;
        }
      }
      ind.resize(vec.nr() * positions.size());
      counter = 0;
      for (std::size_t j = 0; j < positions.size(); j++) {
        for (std::size_t i = 0; i < vec.nr(); i++) {
          ind[counter] = (positions[j]) * vec.nr() + i;
          counter++;
        }
      }
      mp.setMatrix(true, vec.nr(), positions.size());
      return;
    } else if constexpr (is<DataTypeC, double>) {
      if (!idxL) {
        ass(false, "Variable[FALSE, FALSE] subsetting is not supported. Sorry");
        return;
      }
      std::size_t counter = 0;
      ind.resize(vec.nr() * idxR->size());
      for (std::size_t j = 0; j < idxR->size(); j++) {
        for (std::size_t i = 0; i < vec.nr(); i++) {
          ind[counter] = (d2i((*idxR)[j]) - 1) * vec.nr() + i;
          counter++;
        }
      }
      mp.setMatrix(true, vec.nr(), idxR->size());
    } else if constexpr (is<DataTypeC, int>) {
      if (!idxL) {
        ass(false, "Variable[FALSE, FALSE] subsetting is not supported. Sorry");
        return;
      }
      std::size_t counter = 0;
      ind.resize(vec.nr() * idxR->size());
      for (std::size_t j = 0; j < idxR->size(); j++) {
        for (std::size_t i = 0; i < vec.nr(); i++) {
          ind[counter] = ((*idxR)[j] - 1) * vec.nr() + i;
          counter++;
        }
      }
      mp.setMatrix(true, vec.nr(), idxR->size());
    }
  } else if constexpr (isd<R, int, C, bool>) {
    std::cout << "int bool" << std::endl;
  } else if constexpr (isd<R, int, C, int>) {
    std::cout << "int int" << std::endl;
  } else if constexpr (isd<R, int, C, double>) {
    std::cout << "int double" << std::endl;
  } else if constexpr (is<R, int> && IsAV<C>) {
    std::cout << "int vec" << std::endl;
  } else if constexpr (isd<R, double, C, bool>) {
    std::cout << "double bool" << std::endl;
  } else if constexpr (isd<R, double, C, int>) {
    std::cout << "double int" << std::endl;
  } else if constexpr (isd<R, double, C, double>) {
    std::cout << "double double" << std::endl;
  } else if constexpr (is<R, double> && IsAV<C>) {
    std::cout << "double vec" << std::endl;
  } else if constexpr (IsAV<R> && is<C, bool>) {
    std::cout << "vec bool" << std::endl;
  } else if constexpr (IsAV<R> && is<C, int>) {
    std::cout << "vec int" << std::endl;
  } else if constexpr (IsAV<R> && is<C, double>) {
    std::cout << "vec double" << std::endl;
  } else if constexpr (IsAV<R> && IsAV<C>) {
    std::cout << "vec vec" << std::endl;
  } else {
    std::cout << "not found" << std::endl;
  }
}

template <typename V, typename R, typename C>
  requires IsVec<V>
inline auto subset(V &vec, R &&r, C &&c) {
  using DataType = ExtractDataType<V>::RetType;
  Subset<decltype(convert(vec).d), SubsetTrait> sub(vec);
  calcIndMatrix(vec, sub.ind, sub.mp, &r, &c);
  return Vec<DataType, decltype(convertSubset(vec)), SubVecTrait>(
      std::move(sub));
}

template <typename V, typename R, typename C>
  requires(IsRVec<V> || IsSubVec<V> || OperationVec<V>)
inline const auto subset(V &&vec, R &&r, C &&c) {
  using DataType = ExtractDataType<V>::RetType;
  Subset<const decltype(convert(vec).d), SubsetTrait> sub(
      vec); // TODO: check whether a new trait SubsetTraitconst is needed
  calcIndMatrix(vec, sub.ind, sub.mp, &r, &c);
  return Vec<DataType, decltype(convertSubsetConst(vec)), SubVecTrait>(
      std::move(sub));
}

template <typename L, typename R>
  requires(std::is_same_v<L, int> || std::is_same_v<L, double>)
inline void calcInd(const Vec<BaseType> &vec, Indices &ind, MatrixParameter &mp,
                    const L &idxL, const R &idxR) {
  ass(vec.im(), "incorrect number of dimensions");
  int indexRow = static_cast<std::size_t>(idxL);
  if constexpr (std::is_same_v<R, bool>) {
    if (!idxR)
      return;
    ind.resize(vec.nc());
    for (std::size_t j = 0; j < vec.nc(); j++)
      ind[j] = j * vec.nr() + (indexRow - 1);
    mp.setMatrix(false, 0, 0);
    return;
  } else if constexpr (std::is_same_v<R, int>) {
    indexRow--;
    ind.resize(1);
    ind[0] = (idxR - 1) * vec.nr() + indexRow;
    return;
  } else if constexpr (std::is_same_v<R, double>) {
    indexRow--;
    ind.resize(1);
    ind[0] = (static_cast<std::size_t>(idxR) - 1) * vec.nr() + indexRow;
    return;
  } else {
    using vecTrait = std::remove_reference<decltype(idxR)>::type::TypeTrait;
    using isVec = std::is_same<vecTrait, VectorTrait>;
    if constexpr (isVec::value) {
      using whichType = std::remove_reference<decltype(idxR)>::type::Type;
      using isBool = std::is_same<whichType, bool>;
      if constexpr (isBool::value) {
        std::size_t counter = 0;
        ass(idxR.size() <= vec.nc(),
            "Error in matrix: logical subscript too long");
        for (std::size_t i = 0; i < vec.nc(); i++) {
          if (idxR[i % idxR.size()])
            counter++;
        }
        BaseStore<int> positions(counter);
        counter = 0;
        std::size_t counter2 = 0;
        for (std::size_t i = 0; i < vec.nc(); i++) {
          if (((i % vec.nc()) == 0) && i != 0)
            counter2++;
          if (idxR[i % idxR.size()]) {
            positions[counter] = i - counter2 * vec.nc();
            counter++;
          }
        }
        ind.resize(positions.size());
        indexRow--;
        for (std::size_t j = 0; j < positions.size(); j++) {
          ind[j] = (d2i(positions[j])) * vec.nr() + indexRow;
        }
        mp.setMatrix(false, 0, 0);
      } else if constexpr (std::is_same_v<whichType, BaseType>) {
        ind.resize(idxR.size());
        indexRow--;
        for (std::size_t j = 0; j < idxR.size(); j++)
          ind[j] = (d2i(idxR[j]) - 1) * vec.nr() + indexRow;
        mp.setMatrix(false, 0, 0);
      } else {
        static_assert(!isVec::value || !std::is_same_v<whichType, BaseType>,
                      "Unknown type of index variable");
      }
    } else {
      static_assert(!isVec::value, "Unknown type of index variable");
    }
  }
}

template <typename L, typename R>
  requires IsVecDouble<L>
inline void calcInd(const Vec<BaseType> &vec, Indices &ind, MatrixParameter &mp,
                    const L &idxL, const R &idxR) {
  ass(vec.im(), "incorrect number of dimensions");
  if constexpr (std::is_same_v<R, bool>) {
    if (!idxR)
      return;
    ind.resize(idxL.size() * vec.nc());
    std::size_t counter = 0;
    for (std::size_t i = 0; i < vec.nc(); i++) {
      for (std::size_t j = 0; j < idxL.size(); j++) {
        ind[counter] = i * vec.nr() + (d2i(idxL[j]) - 1);
        counter++;
      }
    }
    mp.setMatrix(true, idxL.size(), vec.nc());
  } else if constexpr (std::is_same_v<R, int>) {
    ind.resize(idxL.size());
    for (int j = 0; j < idxL.size(); j++) {
      ind[j] = (idxR - 1) * vec.nr() + (d2i(idxL[j]) - 1);
    }
    return;
  } else if constexpr (std::is_same_v<R, double>) {
    ind.resize(idxL.size());
    for (int j = 0; j < idxL.size(); j++) {
      ind[j] = d2i(idxR - 1.0) * vec.nr() + (d2i(idxL[j]) - 1);
    }
    return;
  } else {
    using vecTrait = std::remove_reference<decltype(idxR)>::type::TypeTrait;
    using isVec = std::is_same<vecTrait, VectorTrait>;
    if constexpr (isVec::value) {
      using whichType = std::remove_reference<decltype(idxR)>::type::Type;
      using isBool = std::is_same<whichType, bool>;
      if constexpr (isBool::value) {
        std::size_t counter = 0;
        for (std::size_t i = 0; i < idxR.size(); i++)
          if (idxR[i])
            counter++;
        BaseStore<int> positions(counter);
        counter = 0;
        std::size_t counter2 = 0;
        for (std::size_t i = 0; i < idxR.size(); i++) {
          if (((i % vec.nc()) == 0) && i != 0) {
            counter2++;
          }
          if (idxR[i]) {
            positions[counter] = i - counter2 * vec.nc();
            counter++;
          }
        }
        ind.resize(idxL.size() * positions.size());
        counter = 0;
        for (std::size_t j = 0; j < positions.size(); j++) {
          for (std::size_t i = 0; i < idxL.size(); i++) {
            ind[counter] = (positions[j]) * vec.nr() + d2i(idxL[i]) - 1;
            counter++;
          }
        }
        mp.setMatrix(true, idxL.size(), positions.size());
        return;
      } else if constexpr (std::is_same_v<whichType, BaseType>) {
        ind.resize(idxL.size() * idxR.size());
        std::size_t counter = 0;
        for (std::size_t i = 0; i < idxR.size(); i++) {
          for (std::size_t j = 0; j < idxL.size(); j++) {
            ind[counter] = (d2i(idxR[i]) - 1) * vec.nr() + (d2i(idxL[j]) - 1);
            counter++;
          }
        }
        mp.setMatrix(true, idxL.size(), idxR.size()); // issue: correct?
        return;
      } else {
        static_assert(!isVec::value || !std::is_same_v<whichType, BaseType>,
                      "Unknown type of index variable");
      }
    } else {
      static_assert(!isVec::value, "Unknown type of index variable");
    }
  }
}

template <typename L, typename R>
  requires IsVecBool<L>
inline void calcInd(const Vec<BaseType> &vec, Indices &ind, MatrixParameter &mp,
                    const L &idxL, const R &idxR) {
  ass(vec.im(), "incorrect number of dimensions");
  if constexpr (std::is_same_v<R, bool>) {
    if (!idxR)
      return;
    std::size_t counter = 0;
    for (std::size_t i = 0; i < idxL.size(); i++) {
      if (idxL[i])
        counter++;
    }
    BaseStore<std::size_t> positions(counter);
    counter = 0;
    std::size_t counter2 = 0;
    for (std::size_t i = 0; i < idxL.size(); i++) {
      if (((i % vec.nr()) == 0) && i != 0)
        counter2++;
      if (idxL[i]) {
        positions[counter] = i - counter2 * vec.nr();
        counter++;
      }
    }
    ind.resize(vec.nc() * positions.size());
    ind.fill(0);
    counter = 0;
    for (std::size_t j = 0; j < vec.nc(); j++) {
      for (std::size_t i = 0; i < positions.size(); i++) {
        ind[counter] = j * vec.nr() + positions[i];
        counter++;
      }
    }
    mp.setMatrix(true, positions.size(), vec.nc());
  } else if constexpr (std::is_same_v<R, int>) {
    std::size_t counter = 0;
    for (int i = 0; i < vec.nr(); i++) {
      if (idxL[i % idxL.size()])
        counter++;
    }
    ass(idxL.size() <= vec.nr(), "Error in matrix: logical subscript too long");
    BaseStore<int> positions(counter);
    counter = 0;
    std::size_t counter2 = 0;
    for (std::size_t i = 0; i < vec.nr(); i++) {
      if (((i % vec.nr()) == 0) && i != 0) {
        counter2++;
      }
      if (idxL[i % idxL.size()]) {
        positions[counter] = i - counter2 * vec.nr();
        counter++;
      }
    }
    ind.resize(positions.size());
    for (std::size_t j = 0; j < positions.size(); j++) {
      ind[j] = (idxR - 1) * vec.nr() + positions[j];
    }
    mp.setMatrix(false, 0, 0);
  } else if constexpr (std::is_same_v<R, double>) {
    std::size_t counter = 0;
    for (int i = 0; i < idxL.size(); i++) {
      if (idxL[i])
        counter++;
    }
    BaseStore<int> positions(counter);
    counter = 0;
    std::size_t counter2 = 0;
    for (std::size_t i = 0; i < idxL.size(); i++) {
      if (((i % vec.nr()) == 0) && i != 0) {
        counter2++;
      }
      if (idxL[i]) {
        positions[counter] = i - counter2 * vec.nr();
        counter++;
      }
    }
    ind.resize(positions.size());
    for (std::size_t j = 0; j < positions.size(); j++) {
      ind[j] = d2i(idxR - 1.0) * vec.nr() + positions[j];
    }
    mp.setMatrix(false, 0, 0);
  } else {
    using vecTrait = std::remove_reference<decltype(idxR)>::type::TypeTrait;
    using isVec = std::is_same<vecTrait, VectorTrait>;
    if constexpr (isVec::value) {
      using whichType = std::remove_reference<decltype(idxR)>::type::Type;
      using isBool = std::is_same<whichType, bool>;
      if constexpr (isBool::value) {
        std::size_t counter = 0;
        for (std::size_t i = 0; i < idxL.size(); i++) {
          if (idxL[i] == true) {
            counter++;
          }
        }
        BaseStore<int> positions_rows(counter);
        counter = 0;
        std::size_t counter2 = 0;
        for (std::size_t i = 0; i < idxL.size(); i++) {
          if (((i % vec.nr()) == 0) && i != 0) {
            counter2++;
          }
          if (idxL[i]) {
            positions_rows[counter] = i - counter2 * vec.nr();
            counter++;
          }
        }
        counter = 0;
        for (std::size_t i = 0; i < idxR.size(); i++) {
          if (idxR[i])
            counter++;
        }
        BaseStore<int> positions_cols(counter);
        counter = 0;
        counter2 = 0;
        for (std::size_t i = 0; i < idxR.size(); i++) {
          if (((i % vec.nc()) == 0) && i != 0) {
            counter2++;
          }
          if (idxR[i]) {
            positions_cols[counter] = i - counter2 * vec.nc();
            counter++;
          }
        }
        ind.resize(positions_rows.size() * positions_cols.size());
        counter = 0;
        for (std::size_t j = 0; j < positions_cols.size(); j++) {
          for (std::size_t i = 0; i < positions_rows.size(); i++) {
            ind[counter] = positions_cols[j] * vec.nr() + positions_rows[i];
            counter++;
          }
        }
        mp.setMatrix(true, positions_rows.size(), positions_cols.size());
        return;
      } else if constexpr (std::is_same_v<whichType, BaseType>) {
        std::size_t counter = 0;
        for (std::size_t i = 0; i < idxL.size(); i++)
          if (idxL[i])
            counter++;
        BaseStore<int> positions(counter);
        counter = 0;
        std::size_t counter2 = 0;
        for (std::size_t i = 0; i < idxL.size(); i++) {
          if (((i % vec.nr()) == 0) && i != 0) {
            counter2++;
          }
          if (idxL[i]) {
            positions[counter] = i - counter2 * vec.nr();
            counter++;
          }
        }
        ind.resize(positions.size() * idxR.size());
        counter = 0;
        for (std::size_t j = 0; j < idxR.size(); j++) {
          for (std::size_t i = 0; i < positions.size(); i++) {
            ind[counter] = (d2i(idxR[j]) - 1) * vec.nr() + positions[i];
            counter++;
          }
        }
      } else {
        static_assert(!isVec::value || !std::is_same_v<whichType, BaseType>,
                      "Unknown type of index variable");
      }
    } else {
      static_assert(!isVec::value, "Unknown type of index variable");
    }
  }
}

/*
template <typename IL, typename IR>
inline auto subset(Vec<BaseType> &vec, const IL &idxL, const IR & idxR)
    -> Vec<BaseType, Subset<decltype(convert(vec).d), SubsetTrait>> {
  Subset<decltype(convert(vec).d), SubsetTrait> sub(vec);
  calcInd(vec, sub.ind, sub.mp,  idxL, idxR);
  return Vec<BaseType, decltype(convertSubset(vec))>(std::move(sub));
}
*/

/*
template <typename T, typename R, typename IL, typename IR>
  requires NotOperation<R>
inline auto subset(Vec<T, R> &vec, const IL &idxL, const IR &idxR)
    -> Vec<BaseType,
           Subset<decltype(convert(vec).d),
                  SubsetTrait>> { // issue: add also NotOperation and
                                  // UnaryOrBinaryOperation to vector subsetting
  Subset<decltype(convert(vec).d), SubsetTrait> sub(vec);
  calcInd(vec, sub.ind, sub.mp, idxL, idxR);
  return Vec<BaseType, decltype(convertSubset(vec))>(std::move(sub));
}

template <typename L, typename R, typename Trait, typename IL, typename IR>
  requires NotOperation<R>
inline auto subset(Vec<L, R, Trait> &vec, const IL &idxL, const IR &idxR)
    -> Vec<BaseType, Subset<decltype(convert(vec).d), SubsetTrait>> {
  Subset<decltype(convert(vec).d), SubsetTrait> sub(vec);
  calcInd(vec, sub.ind, sub.mp, idxL, idxR);
  return Vec<BaseType, decltype(convertSubset(vec))>(std::move(sub));
}

template <typename T, typename R, typename IL, typename IR>
  requires UnaryOrBinaryOperation<R>
inline auto subset(const Vec<T, R> &vec, const IL &idxL, const IR &idxR)
    -> Vec<BaseType> {
  Indices ind;
  MatrixParameter mp;
  calcInd(vec, ind, mp, idxL, idxR);
  Buffer<BaseType> retBuffer(ind.size());
  for (std::size_t i = 0; i < retBuffer.size(); i++)
    retBuffer[i] = vec[ind[i]];
  retBuffer.setMatrix(mp);
  Vec<BaseType> ret(retBuffer);
  return ret;
}

template <typename L, typename R, typename Trait, typename IL, typename IR>
  requires UnaryOrBinaryOperation<R>
inline auto subset(const Vec<L, R, Trait> &vec, const IL &idxL, const IR &idxR)
    -> Vec<BaseType> {
  Indices ind;
  MatrixParameter mp;
  calcInd(vec, ind, mp, idxL, idxR);
  Buffer<BaseType> retBuffer(ind.size());
  for (std::size_t i = 0; i < retBuffer.size(); i++)
    retBuffer[i] = vec[ind[i]];
  retBuffer.setMatrix(mp);
  Vec<BaseType> ret(retBuffer);
  return ret;
}
*/

}; // namespace etr

#endif

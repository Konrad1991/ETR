#ifndef SUBSETTING_AT_HPP
#define SUBSETTING_AT_HPP

#include "UtilsSubsetting.hpp"

namespace etr {
template <typename T, typename R>
  requires std::is_same_v<R, std::size_t>
inline BaseType &at(T &inp, R i) {
  i--;
  ass(i >= 0, "Error: out of boundaries --> value below 1");
  ass(i < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[i];
}

template <typename T> inline BaseType &at(T &inp, BaseType i_) {
  std::size_t i = d2i(i_);
  i--;
  ass(i >= 0, "Error: out of boundaries --> value below 1");
  ass(i < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[i];
}

template <typename T>
inline BaseType &at(T &inp, std::size_t r, std::size_t c) {
  ass(inp.im() == true, "Input is not a matrix!");
  r--;
  c--;
  ass((c * inp.nr() + r) >= 0, "Error: out of boundaries --> value below 1");
  ass((c * inp.nr() + r) < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[c * inp.nr() + r];
}

template <typename T> inline BaseType &at(T &inp, BaseType r_, BaseType c_) {
  ass(inp.im() == true, "Input is not a matrix!");
  std::size_t r = d2i(r_);
  std::size_t c = d2i(c_);
  r--;
  c--;
  ass((c * inp.nr() + r) >= 0, "Error: out of boundaries --> value below 1");
  ass((c * inp.nr() + r) < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[c * inp.nr() + r];
}

template <typename T, typename R>
  requires std::is_same_v<R, std::size_t>
inline BaseType &at(const Vec<BaseType> &inp, R i) {
  i--;
  ass(i >= 0, "Error: out of boundaries --> value below 1");
  ass(i < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[i];
}

inline BaseType &at(const Vec<BaseType> &inp, BaseType i_) {
  std::size_t i = d2i(i_);
  i--;
  ass(i >= 0, "Error: out of boundaries --> value below 1");
  ass(i < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[i];
}

inline BaseType &at(const Vec<BaseType> &inp, std::size_t r, std::size_t c) {
  ass(inp.im() == true, "Input is not a matrix!");
  r--;
  c--;
  ass((c * inp.nr() + r) >= 0, "Error: out of boundaries --> value below 1");
  ass((c * inp.nr() + r) < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[c * inp.nr() + r];
}

inline BaseType &at(const Vec<BaseType> &inp, BaseType r_, BaseType c_) {
  ass(inp.im() == true, "Input is not a matrix!");
  std::size_t r = d2i(r_);
  std::size_t c = d2i(c_);
  r--;
  c--;
  ass((c * inp.nr() + r) >= 0, "Error: out of boundaries --> value below 1");
  ass((c * inp.nr() + r) < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[c * inp.nr() + r];
}

inline BaseType &at(const Vec<BaseType> &&inp, std::size_t r, std::size_t c) {
  ass(inp.im() == true, "Input is not a matrix!");
  r--;
  c--;
  ass((c * inp.nr() + r) >= 0, "Error: out of boundaries --> value below 1");
  ass((c * inp.nr() + r) < inp.size(),
      "Error: out of boundaries --> value beyond size of vector");
  return inp.d.p[c * inp.nr() + r];
}

} // namespace etr

#endif

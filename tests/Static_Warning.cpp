#define STANDALONE_ETR
#include "../include/etr.hpp"

// https://www.reddit.com/r/cpp/comments/66o1ju/does_a_static_warn_exist/
template <bool condition> struct warn_if {};
template <> struct [[deprecated]] warn_if<false> {
  constexpr warn_if() = default;
};
#define static_warn(x, ...) ((void)warn_if<x>())

[[deprecated]]
void fct_with_warning() {
  // static_warn(false, "This is bad");
}

int main(int argc, char *argv[]) {
  constexpr bool b = true;
  if constexpr (std::is_same_v<decltype(b), double>) {
    fct_with_warning();
  }
  return 0;
}

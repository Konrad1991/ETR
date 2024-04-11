#include <iostream>

// https://www.reddit.com/r/cpp/comments/66o1ju/does_a_static_warn_exist/

template<bool condition>
struct warn_if{};

template<> struct [[deprecated]] warn_if<false>{constexpr warn_if() = default;};

#define static_warn(x, ...) ((void) warn_if<x>())

[[deprecated("Use calcSomethingDifferently(int).")]]    
inline void warning() {}

int main() {
    constexpr bool b = true;
    if constexpr(std::is_same_v<decltype(b), bool>) {
        //warning();
            static_warn(false, "This is bad");
    } 
    
}
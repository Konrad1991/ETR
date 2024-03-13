#include <iostream>
#include <cxxabi.h>

inline std::string demangle(const char *mangledName) {
  int status;
  char *demangled = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
  std::string result(demangled);
  std::free(demangled);
  return result;
}

template <typename T> inline void printType(T inp) {
  std::cout << demangle(typeid(inp).name()) << std::endl;
}

template <typename T> void inline printT() {
  std::cout << demangle(typeid(T).name()) << std::endl;
}

template <typename T, typename U>
using CommonType = typename std::common_type<typename T::Type, typename U::Type>::type;

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type commonType(T1 arg1, T2 arg2) {
        return arg1 + arg2; 
 }

int main() {
    int a = 4;
    double b = 20;
    std::cout << a / b << std::endl;
    printT<decltype(commonType(a, b))>();
}

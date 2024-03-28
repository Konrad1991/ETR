#define STANDALONE_ETR

#include "../include/etr.hpp"
using namespace etr;

int main() {
    
    Vec<double> vec0 = vector(100);
    print(vec0);
    printTAST<decltype(vec0)>();

    auto calc = coca(1, 2, 3) + 3.14;
    printTAST<decltype(calc)>();

    printTAST<decltype(vector(3))>();

    printTAST<decltype(vector(3) + 3.14)>();
}


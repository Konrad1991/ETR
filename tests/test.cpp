#define STANDALONE_ETR
#include "../include/etr.hpp"
using namespace etr;
#include <iomanip>

int main() {
    Buffer<double> bs;
    ExtractDataType<decltype(bs)>::RetType test1;
    printT<decltype(test1)>();

    Vec<int> v;
    ExtractDataType<decltype(v)>::RetType test2;
    printT<decltype(test2)>();

    sexp test = coca(1, 2, 3);
    printT<decltype(v + v)>();
    printT<decltype(test + test)>();
    printT<decltype(test+ v)>();

    print(test + 1);
    print(test + 1.0);

    printT<decltype(test + 1)>();
    printT<decltype(test + 1.0)>();

    //for(auto& i: (test + 1.0)) {
    //    std::cout << i << std::endl;
    //}

    test = test / 20;
    print(test);

    Vec<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    Vec<int> v2(3);
    v2[0] = 10; v2[1] = 20; v2[2] = 30;

    v1 / v2;
    printT<decltype(v1 / v2)>();
    Vec<double> res = v1 / v2;
    print(res);


    sexp bla(3);
    sexp bla2 = bla - 1.0;
    print(bla2);


    std::vector<double> vd{1., 2., 3.};

    BorrowPtr bp(vd.data(), vd.size());

    bp + 3.14;
    {
        std::vector<double> vd(16);
        BorrowPtr a(vd.data(), vd.size());
        a = etr::matrix(4, 4);
        for (auto&i:  etr::colon(etr::i2d(1), etr::at(etr::dim(a), 1))) {;   
                 for (auto&j:  etr::colon(etr::i2d(1), etr::at(etr::dim(a), 2))) {;  
                     etr::subset(a, i, j) = i + j;   
                 };  
        };    
        print(a);
    }
      
    
}


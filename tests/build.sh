#!/bin/bash

cd /home/konrad/Documents/GitHub/RProjects/etr_supplement/ETR/tests/
g++ ./BaseStore_Tests.cpp -std=c++20 && ./a.out
g++ ./Coca_Tests.cpp -std=c++20 && ./a.out
g++ ./Colon_Tests.cpp -std=c++20 && ./a.out
g++ ./Concepts_Test.cpp -std=c++20 && ./a.out
g++ ./Derivatives_Tests.cpp -std=c++20 && ./a.out
g++ ./Helper_Tests.cpp -std=c++20 && ./a.out
g++ ./Matrix_Tests.cpp -std=c++20 && ./a.out
g++ ./Rep_Tests.cpp -std=c++20 && ./a.out
g++ ./Subsetting_Tests.cpp -std=c++20 && ./a.out
g++ ./Unary_Tests.cpp -std=c++20 && ./a.out
g++ ./Vector_Tests.cpp -std=c++20 && ./a.out

#!/bin/bash

#cd .. && find . -type f -name "*.o" | xargs rm && make && cd tests

#g++ -std=c++20 -Wall -Wextra -pedantic \
#  -I../include -I../src/R_ext -I../src -c -o demo.o demo.c

#g++ -o demo demo.o -L.. -lrmath -lm -lR

g++ -std=c++20 -Wall -Wextra -pedantic -I. -c -o sunif.o sunif.cpp
g++ -std=c++20 -Wall -Wextra -pedantic -I. -c -o demo.o demo.cpp
g++ -o demo demo.o sunif.o

./demo 

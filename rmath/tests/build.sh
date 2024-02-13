#!/bin/bash

gcc -std=c99 -Wall -Wextra -pedantic -I../include -I../src/R_ext -I../src -c -o demo.o demo.c

gcc -o demo demo.o -L.. -lrmath -lm -lR

./demo 1 1

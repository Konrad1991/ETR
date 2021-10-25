# ETR
 Expression template for C++ similar to R syntax 
 
# Overview

This is the expression template from the R package ast2ast. It aims to provide a library with as similar as possible syntax to R. 

```Cpp
#include "etr.hpp"
int main() {
vec a = colon(1, 3);
vec b = colon(2, 4);

vec c;

c = a + b;

print(c);

vec d = c(1, 2);

print(d);

vec e = concatenate(1., 2., c); // does not work
}
```
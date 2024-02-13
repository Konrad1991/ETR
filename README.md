- [Overview](#overview)
- [Integrate ETR in your project](#integrate-etr-in-your-project)
- [How to use it](#how-to-use-it)
    + [Hello World from ETR](#hello-world-from-etr)
    + [Variable declaration & borrowing of raw pointers](#variable-declaration)
    + [Basic arithmetic](#basic-arithmetic)
    + [Subsetting](#subsetting)
    + [Helper functions](#helper-functions)
    + [Comparison functions](#comparison-functions)
    + [Looping](#looping)
    + [Math functions](#math-functions)
    + [Interpolation](#interpolation)

# Overview 

ETR is an expression template library for C++ with syntax almost similar to R. Within this repository the standalone version can be found. As the C++ code is used in the R package ast2ast (https://github.com/Konrad1991/ast2ast) also R specific code is included. 
By using *#define STANDALONE* the R specific code is removed. The library contains one main type:
    
    * The main type: template <typename T, typename R = Buffer<T>, typename Trait = VectorTrait> struct Vec;
There exists also other container responsible for storing the memory (typename R). Within the standalone library the *Borrow* struct is most importantly. See in the documention above about how to use it.
The class Vec can hold a scalar, vector or a matrix. Moreover, the type can change dynamically at runtime. 

# Integrate ETR in your project

Notably, it is a header-only library and thus can be easly integrated in other projects. Simply clone the repository and add the 'etr_bits' folder in your project (can be found in the 'include' folder). Afterwards you have to include the 'etr.hpp' file in your codebase (*#include 'etr.hpp'*). The file can also be found in the 'include' folder. Use of C++17 is required, i.e. compile a program using: 'g++ test.cpp -std=c++17'. There is also a problem with older versions of gcc. The tests all run successfully using gcc-10. Code coverage can be found in folder tests (84.3%).
How the program works in detail, is explained below using small examples. 

# How to use it

### Hello World from ETR

The **print** function can be used to print strings, scalar values, vectors or matrices. If you want to add a empty line use the function without an argument. 

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {
  print("Hello World");
}
```

### Variable declaration & borrowing of raw pointers

All variables are of type **sexp**. This type can hold a scalar, a vector or a matrix (The only type that can be hold by these containers is a **double**). If you want to allocate memory you can use the functions **vector** or **matrix**. Another possibility to allocate memory are the functions **colon** and **coca**. The **colon** function excepts a start and a end value and returns a vector with n-values seperated by an interval with length 1 respectively. The **coca** functions concatenates the given input. \
Notably, it is possible to change the type of a variable within the program. You can see below that at the end the variable *scalar* contains a vector. 
Beyond that, it is possible to borrow a pointer. In the example below a raw pointer is used to allocate memory on the heap. Afterwards it is wrapped in a BorrowPtr class instance. On the one hand it is more convinient to use the Vector class. Furthermore, it protects from unallowed access i.e. you cannot assign longer elements than that which was borrowed.

Currently, I work on using other types as double. This is still work in progress even though many things work already. 

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {

  sexp scalar = 1.0; print(scalar);

  sexp empty_vec = vector(10); // vector with 10 elements
  sexp full_vec = vector(3.14, 10); // vector with 10 elements all contain 3.14

  sexp emtpy_mat = matrix(5, 2); // matrix with 10 elements; 5 rows and 2 cols
  sexp full_mat = matrix(10.5, 5, 4); // matrix with 10 elements; 5 rows and 4 cols all contain 10.5

  sexp vec_range = colon(1, 10); // vector containing 1, 2, 3, ..., 10
  sexp vec = coca(1, 5, 6, vec_range); // vector containing 1, 5, 6, vec_range

  // change the type
  scalar = vector(5.2, 12);
  print(scalar);

  // you can borrow a raw pointer
   size_t size = 3; 
  double* ptr = new double[size];
  
  BorrowPtr v_borrow(ptr, size);
  v_borrow = colon(1, 3);
  print(v_borrow);
  
  ptr[0] = 3.14;
  print(v_borrow);

  std::cout << ptr[0] << " " << ptr[1] << " " << ptr[2] << std::endl;

  delete[] ptr; // you are responsible to not use v_borrow after deleting ptr!
}
```

### Basic arithmetic

You can apply basic functions like **+**, **-**, **/** and **\*** to scalar, vector, matrices and any combinations. 

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {

sexp v = colon(1, 10);

v = v/1.0 + 10.0;
print(v);

sexp m = matrix(3., 5, 2);
m = m - v;
print(m);
}
```

### Subsetting

You can use the operator() to subset a variable. 

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {

  sexp a = coca(1, 2.2, 3);
  print(a);
  
  sexp b = matrix(colon(1, 16), 4, 4);
  print(b);

  print(b(1));
 
  b(3) = 4.5;

  print(b);

}
```


### Helper functions

In order to extract informations about variables. You can use the **length** function in order to determine number of stored objects in vector or matrix. In case the variable is a matrix the **dim** function returns a vector containg the number of rows in the first place followed by the number of columns. 
There are some special print functions available: printType prints the type of an object, printTType prints the type of the type of an object, printAST prints the expression tree of the current object and printTAST prints the expression tree of a type of an object.

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {

    sexp v = colon(1, 2);
    print(length(v));

    sexp m = matrix(5, 2);
    print(length(m));
    print(dim(m));

    printType(v);
    printT<sexp>();
    printAST(v + v*2.0);
    printTAST<decltype(v - v*v)>();

}
```

### Comparison functions

As usual in R you can use **==**, **!=**, **<=**, **>=**, **<** and **>**. If one of the comparison functions returns more then one bool and is used in an **if** or **else if** the first element is used.

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {

  sexp a = coca(1, 2, 3);
  sexp b = coca(1, 2, 4);

  sexp c = a == b;
  print(c);
  print(a == b);
  print(a >= b);
  print(a <= b);
  print(a < b);
  print(a > b);
  print(a != b);

  sexp d = coca(1, 2, 3, 4);
  sexp e = coca(1, 4);

  print(d == e);
  print(e >= d);

  auto a_is_b = a == b;
  printAST(a_is_b);
  print(a_is_b);
  if(a(1)) {
    print(a==b);
    print(1);
    print(4.5);
  }

  print(d);
  print(coca(1,2,d));

}
```

### Looping

You can use range based for loops in order to loop over **sexp** objects. 

```Cpp
#include "etr.hpp"
using namespace etr;
Hallo Sid,

danke dir.
VG Konrad
int main() {

  sexp v = colon(1, 10);

  for(auto& i: v) {
    print(i);
  }

}

```


### Math functions

The following math functions can be used:

- exponent: exp(variable, exponent); 
  - on non primitive types one can also write a^exponent
- natural logarithm: ln(variable)
- sinus(variable)
- sinush(variable)
- asinus(variable)
- cosinus(variable)
- cosinush(variable)
- acosinus(variable)
- tangens(variable)
- tangensh(variable)
- atangens(variable)


### Interpolation

It is possible to use a catmull-rome interpolation function called **cmr**. The first argument is the position where the desired value should be calculated. The second argument is the x-variable (i.e. a vector), and the last argument are the y-values. See the example below how to use the function. 

```Cpp
#include "etr.hpp"
using namespace etr;

int main() {

    sexp t = colon(1, 8);
    sexp p = coca(1, 2, 3, 4, 5, 6, 7, 8);

    sexp res = cmr(1, t, p);
    print(res);

    res = cmr(1.5, t, p);
    print(res);

    res = cmr(2.5, t, p);
    print(res);

    res = cmr(4, t, p);
    print(res);

    res = cmr(5, t, p);
    print(res);

    res = cmr(5.5, t, p);
    print(res);

    res = cmr(7.5, t, p);
    print(res);

    res = cmr(7.99, t, p);
    print(res);
    print();
    res = cmr(8, t, p);
    print(res);

    print();
    res = cmr(9, t, p);
    print(res);

    print();
    res = cmr(-1, t, p);
    print(res);

}

```



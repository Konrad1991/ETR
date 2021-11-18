- [Overview](#overview)
- [Integrate ETR in your project](#integrate-etr-in-your-project)
- [How to use it](#how-to-use-it)
    + [Hello World from ETR](#hello-world-from-etr)
    + [Variable declaration](#variable-declaration)
    + [Basic arithmetic](#basic-arithmetic)
    + [Subsetting](#subsetting)
      - [Subsetting vector in detail](#subsetting-vector-in-detail)
      - [Subsetting matrix in detail](#subsetting-matrix-in-detail)
    + [Assign to a subset](#assign-to-a-subset)
    + [Helper functions](#helper-functions)
    + [Looping](#looping)
    + [Math functions](#math-functions)

# Overview 

ETR is an expression template library for C++ with syntax almost similar to R. It provides one class (**sexp**) which can hold a scalar, vector or matrix. The type can dynamically be changed during runtime. 
Furthermore, basic arithmetic operations (+, -, \*, /) can be applied to these objects. Thus, it is easy to write C++ which almost looks like R code. 

# Integrate ETR in your project

Notably, it is a header-only library and thus can be easly integrated in other projects. Simply clone the repository and add the 'etr_bits' folder in your project (can be found in the 'include' folder). Afterwards you have to include the 'etr.hpp' file in your codebase (*#include 'etr.hpp'*). The file can also be found in the 'include' folder. Use of C++17 is required, i.e. compile a program using: 'g++ test.cpp -std=c++17'. 

How the program works in detail, is explained below using small examples. 

# How to use it

### Hello World from ETR

The **print** function can be used to print strings, scalar values, vectors or matrices. If you want to add a empty line use the function without an argument. 

```Cpp
#include "etr.hpp"

int main() {
  print("Hello World");
}
```

### Variable declaration

All variables are of type **sexp**. This type can hold a scalar, a vector or a matrix (The only type that can be hold by these containers is a **double**). If you want to allocate memory you can use the functions **vector** or **matrix**. Another possibility to allocate memory are the functions **colon** and **coca**. The **colon** function excepts a start and a end value and returns a vector with n-values seperated by an interval with length 1 respectively. The **coca** functions concatenates the given input. \
Notably, it is possible to change the type of a variable within the program. You can see below that at the end the variable *scalar* contains a vector. 

```Cpp
#include "etr.hpp"

int main() {

sexp scalar; // currently scalar has to be first declared without initialization 
scalar = 1;
print("This is a scalar:");
print(scalar);

sexp empty_vec = vector(10); // vector with 10 elements
sexp full_vec = vector(3.14, 10); // vector with 10 elements all contain 3.14

sexp emtpy_mat = matrix(5, 2); // matrix with 10 elements; 5 rows and 2 cols
sexp full_mat = matrix(10.5, 5, 4); // matrix with 10 elements; 5 rows and 4 cols all contain 10.5

sexp vec_range = colon(1, 10); // vector containing 1, 2, 3, ..., 10
sexp vec = coca(1, 5, 6, vec_range); // vector containing 1, 5, 6, vec_range

// change the type
scalar = vector(5.2, 12);
print(scalar);
}
```

### Basic arithmetic

You can apply basic functions like **+**, **-**, **/** and **\*** to scalar, vector, matrices and any combinations. 

```Cpp
#include "etr.hpp"

int main() {

sexp v = colon(1, 10);

v = v/1 + 10;
print(v);

sexp m = matrix(3., 5, 2);
m = m - v;
print(m);
}
```

### Subsetting

Currently you have to use the function **subset** to extract certain elements (later usage of **()** will be possible). The **subset** function returns a **sexp** object. Indices starts counting from 1 (as usual in R). To subset a vector use one parameter either of type scalar, bool, nothing (use **nullptr**) or another sexp object. In case you want to subset a matrix you can use either one or two arguments which are from the types scalar, bool, nothing (use **nullptr**) or another sexp objects. 

**Caveat: You cannot delete objects using negative indices as in R**

```Cpp
#include "etr.hpp"

int main() {

sexp v1 = colon(1, 2);
sexp v2 = vector(3, 5);

v1 = v1 + subset(v2, coca(1, 5));

print(subset(v1, 1));
print(subset(v1, true));
print();

sexp m = matrix(colon(1, 15), 3, 5);
print(subset(m, coca(1, 3, 2), coca(5, 2, 1)));
}
```

#### Subsetting vector in detail
<details>
  <summary>Click to expand!</summary>
In the program below you can see all the cases of subsetting a vector (matrix subsetting behaves in the same way). 

```Cpp
#include "etr.hpp"

int main() {
  sexp v = colon(1, 6);
  print(v);
  print();

  print("bool");
  print("true: ");
  print(subset(v, true));
  print("false: ");
  print(subset(v, false));
  print();

  print("integer or double");
  print(subset(v, 1));
  print(subset(v, 5.5));
  print();

  print("nothing (nullptr):");
  print(subset(v, nullptr));
  print();

  sexp positions = coca(1, 6, 2, 3);
  print("other vec:");
  print(subset(v, positions));
  print();

  VEC<bool> vec_bool(4); // output e.g. of comparison of two vectors not implemented yet
  vec_bool[0] = true;
  vec_bool[1] = false;
  vec_bool[2] = true;
  vec_bool[3] = true;
  print("bool vec:");
  print(subset(v, vec_bool));
  print();
}
```
</details>


#### Subsetting matrix in detail
<details>
  <summary>Click to expand!</summary>
In the program below you can see all the cases of subsetting a matrix.


```Cpp
#include "etr.hpp"

int main() {
  sexp m = matrix(colon(1, 15), 5, 3);
  print(m);
  print();

  print("bool");
  print("true, true: ");
  print(subset(m, true, true));
  print("false, true: ");
  print(subset(m, false, true));
  print();

  print("integer or double");
  print(subset(m, 1, 1));
  print(subset(m, 5.5, 2));
  print();

  print("nothing (nullptr):");
  print(subset(m, nullptr, nullptr));
  print();

  sexp positions1 = coca(1, 5, 2, 3);
  sexp positions2 = coca(1, 3, 2, 3);
  print("other vecs:");
  print(subset(m, positions1, positions2));
  print();

  VEC<bool> vec_bool1(3); // output e.g. of comparison of two vectors not implemented yet
  vec_bool1[0] = true;
  vec_bool1[1] = false;
  vec_bool1[2] = true;

  VEC<bool> vec_bool2(4); // output e.g. of comparison of two vectors not implemented yet
  vec_bool2[0] = true;
  vec_bool2[1] = true;
  vec_bool2[2] = false;
  vec_bool2[3] = true;
  print("bool vec:");
  print(subset(m, vec_bool1, vec_bool2));
  print();

}
```
</details>

### Assign to a subset

Currently you have to use the function **subassign** to extract only certain elements and assign new values to them (later usage of **&()** will be possible). The **subassign** function returns a reference to the input object. Indices starts counting from 1 (as usual in R). To subset a vector use one parameter either of type scalar, bool, nothing (use **nullptr**) or another sexp object. In case you want to subset a matrix you can use either one or two arguments which are from the types scalar, bool, nothing (use **nullptr**) or another sexp objects. 

```Cpp
#include "etr.hpp"

int main() {

sexp v1 = colon(1, 5);
sexp v2 = vector(3, 10);

subassign(v2, colon(1, 5)) = v1 + subset(v2, colon(6, 10));
print(v2);

}
```

### Helper functions

In order to extract informations about variables. You can use the **length** function in order to determine number of stored objects in vector or matrix. In case the variable is a matrix the **dim** function returns a vector containg the number of rows in the first place followed by the number of columns. 

```Cpp
#include "etr.hpp"

int main() {

sexp v = colon(1, 2);
print(length(v));

sexp m = matrix(5, 2);
print(length(m));
print(dim(m));
}
```


### Looping

You can use range based for loops in order to loop over **sexp** objects. 

```Cpp
#include "etr.hpp"

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



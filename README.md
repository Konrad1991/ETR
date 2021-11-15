# ETR

Expression template library for C++ with syntax almost similar to R. It is a header-only library just include *etr.hpp*. Use of C++17 is required. \
How the program works in detail is explained below using small examples. 

# How to use it

### Hello World from *ETR*

The *print* function can be used to print strings, scalar values, vectors or matrices. If you want to add a empty line use the function without an argument. 

```Cpp
#include "etr.hpp"

int main() {
  print("Hello World");
}
```

### Variable declaration

All variables are of type *sexp*. This type can hold a scalar, a vector or a matrix. The only type that can be hold by these containers is *double*. If you want to allocate memory you can use the functions vector or matrix. Another possibility to allocate memory are the functions *range* and *coca*. The *range* function excepts a start and a end value and returns a vector with n-intervals all of length 1. The *coca* functions concatenates the given input. 

```Cpp
#include "etr.hpp"

int main() {

sexp scalar = 1;
print("This is a scalar:");
print(scalar);

sexp empty_vec = vector(10); // vector with 10 elements
sexp full_vec = vector(3.14, 10); // vector with 10 elements all contain 3.14

sexp emtpy_mat = matrix(5, 2); // matrix with 10 elements; 5 rows and 2 cols
sexp full_mat = matrix(10.5, 5, 4); // matrix with 10 elements; 5 rows and 2 cols all contain 10.5

sexp vec_range = range(1, 10); // vector containing 1, 2, 3, ..., 10
sexp vec = coca(1, 5, 6, vec_range); // vector containing 1, 5, 6, vec_range
}
```

### Basic arithmetic

You can apply basic functions like *+*, *-*, */* and *\** to scalar, vector, matrices and any combinations. 

```Cpp
#include "etr.hpp"

int main() {

sexp v = range(1, 10);

v = v/1 + 10;
print(v);

sexp m = matrix(3., 5, 2);
m = m - v;
print(m);
}
```

### Subsetting

Currently you have to use the function subset to extract only certain elements (later usage of *()* will be possible). The *subset* function returns a *sexp* object. Indices starts counting from 1 (as usual in R). You can subset using a scalar, bool, nothing (use *nullptr*) or another sexp object to subset vectors. In case you want to subset a matrix you can use either one or two arguments which are from the types scalar, bool, nothing (use *nullptr*) or other sexp objects. 

```Cpp
#include "etr.hpp"

int main() {

sexp v1 = range(1, 2);
sexp v2 = vector(3, 5);

v1 = v1 + subset(v2, coca(1, 5));

print(subset(v1, 1));
print(subset(v1, true));
print();

sexp m = matrix(range(1, 15), 3, 5);
print(subset(m, coca(1, 3, 2), coca(5, 2, 1)));
}
```

### Subsetting assign

Currently you have to use the function subassign to extract only certain elements (later usage of *&()* will be possible). The *subassign* function returns a reference to the input object. Indices starts countingfrom 1 (as usual in R). You can subset using a scalar, bool, nothing (use *nullptr*) or another sexp object to subset vectors. In case you want to subset a matrix you can use either one or two arguments which are from the types scalar, bool, nothing (use *nullptr*) or other sexp objects. 

```Cpp
#include "etr.hpp"

int main() {

sexp v1 = range(1, 2);
sexp v2 = vector(3, 5);

subassign(v2, coca(1, 5)) = v1 + subset(v2, coca(1, 5));
}
```

### Helper functions

In order to extract informations about variables. You can use the *length* function in order to determine number of stored objects. In case the variable is a matrix the *dim* function returns a vector containg the number of rows in the first place followed by the number of columns. 

```Cpp
#include "etr.hpp"

int main() {

sexp v = range(1, 2);
print(length(v));

sexp m = matrix(5, 2);
print(length(m));
print(dim(m));
}
```


### Looping

You can use range based for loops in order to loop over *sexp* objects. 

```Cpp
#include "etr.hpp"

int main() {

  sexp v = range(1, 10);

  for(auto& i: v) {
    print(i);
  }

}

```



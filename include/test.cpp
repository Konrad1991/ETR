#include "etr.hpp"





int main() {

sexp scalar;
scalar = 1;
print("This is a scalar:");
print(scalar);

sexp empty_vec = vector(10); // vector with 10 elements
sexp full_vec = vector(3.14, 10); // vector with 10 elements all contain 3.14

sexp emtpy_mat = matrix(5, 2); // matrix with 10 elements; 5 rows and 2 cols
sexp full_mat = matrix(10.5, 5, 4); // matrix with 10 elements; 5 rows and 4 cols all contain 10.5

sexp vec_range = range(1, 10); // vector containing 1, 2, 3, ..., 10
sexp vec = coca(1, 5, 6, vec_range); // vector containing 1, 5, 6, vec_range

// change the type
scalar = vector(5.2, 12);
print(scalar);
}

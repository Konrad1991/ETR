# ToDo

## Types

- CommonType everywhere
- all helper functions such as vector, colon etc. have to return a vector of type RBufTrait and RVecTrait
- subsetting 
    * currently the index operators are all passed as const vars. All cases/combinations have to be implemented. 
- remove BaseType everywhere
- remove all const classifiers (at least where possible)

## Functions

- add: abs

## Derivatives

- calc Derivatives based on type during compile time

## RNG

- rewrite Rs RNG lib in C++ (if possible lock free)

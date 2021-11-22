#include "etr.hpp"



int main() {

sexp a = coca(1, 2, 3);
sexp b = coca(a, a);
print(subset(a, 1) == 2);


}

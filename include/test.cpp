#include "etr.hpp"





int main() {

sexp v1 = range(1, 5);
sexp v2 = vector(3, 10);

subassign(v2, colon(1, 5)) = v1 + subset(v2, colon(6, 10));
print(v2);

}

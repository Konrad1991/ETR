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

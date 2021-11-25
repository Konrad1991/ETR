#include "../include/etr.hpp"
using namespace etr;

int main() {

sexp res = vector(20);
subassign(res, 1) = 1;
subassign(res, 2) = 1;

for(auto i: colon(3, 20)) {
  subassign(res, i) = subset(res, i - 1) + subset(res, i - 2);
}

print(res);

}

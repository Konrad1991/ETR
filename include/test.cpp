#include "etr.hpp"


int main() {

  sexp v = colon(1, 10);

  for(auto& i: v) {
    print(i);
  }

}

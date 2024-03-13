#include "../include/etr.hpp"
using namespace etr;

void bs(sexp& arr) {
  sexp size;
  sexp temp;
  sexp swapped;
  size = length(arr);
  swapped = true;
  do {
    swapped = false;
    for(auto i: colon(1, size-1)) {
      if( arr(i) > arr(i + 1) ) {
          temp = arr(i);
          arr(i) = arr(i + 1);
          arr(i + 1) = temp;
          swapped = true;
      }
    }
  } while(swapped);
}

int main() {
  sexp arr = coca(3, 2, 8, 1, 0);
  print(arr);
  bs(arr);
  print();
  print(arr);
}

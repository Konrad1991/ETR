#include "../include/etr.hpp"
using namespace etr;

void bs(sexp& arr) {
  sexp size = length(arr);
  sexp swapped = true;

  do {
    swapped = false;

    for(auto i: colon(1, size-1)) {

      if(subset(arr, i) > subset(arr, i + 1) ) {
          sexp temp = subset(arr, i);
          subassign(arr, i) = subset(arr, i + 1);
          subassign(arr, i + 1) = temp;
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

#include "etr.hpp"

int mod(double inp, int div) {
  int ret = static_cast<int>(inp) % div;
  return ret;
}

void fizzbuzz(vec inp) {
  for(auto& i: inp) {
    if( (mod(i, 3) == 0) & (mod(i, 5) == 0) ) {
      print("fizz buzz");
      print(i);
    } else if(mod(i, 3) == 0) {
      print("fizz");
      print(i);
    } else if(mod(i, 5) == 0) {
      print("buzz");
      print(i);
    }
  }
}


int main() {

  vec inp = colon(1, 30);
  fizzbuzz(inp);

}

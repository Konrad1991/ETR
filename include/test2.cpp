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
  //fizzbuzz(inp);

  vec v1 = colon(1, 10);
  vec v2 = colon(11, 20);
  vec sub1 = colon(1, 4);
  vec sub2 = colon(2, 5);
  mat m(5, 4);
  m = v2;

  self(v1, 1) = 100.;
  self(v1, sub2) = 200.;
  print(v1);

  vec sub3 = colon(1,2);
  self(m, sub3, sub3) = subset(m, sub3, sub3) + 3.;
  for(int i = 0; m.size(); i++) {
    std::cout << m[i] << std::endl;
  }
  //print(m);

}

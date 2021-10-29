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

double i2d(int inp) {
  return static_cast<double>(inp);
}

void fill(mat& m) {
  for(int i = 0; i < m.size(); i++) {
    m[i] = i2d(i);
  }
}


int main() {

  vec v1 = colon(1, 10);
  print(subset(v1, 1));
  print();
  vec sub1 = colon(1, 3);
  print(subset(v1, sub1));
  print();
  mat m1(6, 6, 9.1);
  fill(m1);
  print(m1);
  print();
  print(subset(m1, 2, 3));
  print();
  print(subset(m1, sub1, sub1));
  print();
  print(subset(m1, 1, ' '));
  print();
  print(subset(m1, 5, ' '));
  print();
  mat inp = subset(m1, ' ', sub1);
  /*
  for(int i = 0; i < inp.size(); i++) {
    std::cout << inp[i] << std::endl;
  }


  mat inp2 = subset(m1, sub1, ' ');
  for(int i = 0; i < inp2.size(); i++) {
    std::cout << inp2[i] << std::endl;
  }
  */

}

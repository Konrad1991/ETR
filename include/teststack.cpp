#include "./etr_bits/stack.hpp"

void print(std::vector<int>& inp) {
  for(int i = 0; i < inp.size(); i++) {
    std::cout << inp[i] << std::endl;
  }
}

int main() {

  STCK s;
  std::vector<int> one{0, 1, 2};
  std::vector<int> two{0, 1, 2};
  std::vector<int> three{0, 1, 2};
  std::vector<int> four{0, 1, 2};
  s = one;
  s = two;
  s = three;
  s = four;
  std::vector<int> a;
  std::vector<int> b;
  std::vector<int> c;
  std::vector<int> d;


  s.get(a);
  s.get(b);
  s.get(c);
  s.get(d);

  print(a);
  print(b);
  print(c);
  print(d);
  
}

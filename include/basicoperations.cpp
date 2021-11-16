#include "etr.hpp"

void test(sexp& a) {
  for(auto& i: a) {
    i = 30.;
  }
}

sexp test2(sexp a) {
  for(auto& i: a) {
    i = 40.;
  }
  return a;
}


int main() {

sexp a = range(1, 15);
a = a + 100.;

print(a);

sexp b = matrix(a, 5, 3);
b = b + a;
print(b);

b = range(1, 20);
print(b);

b = matrix(a, 5, 3);


subassign(b, coca(1, 2, 3), 1) = 200;
print(b);
print();
test(b);
print(b);
test2(b);
print(test2(b));


std::vector<double> p{1., 2.};
for(auto& i: p) {
  std::cout << i << std::endl;
}
double* ptr = p.data();
for(int i = 0; i < p.size(); i++) {
  std::cout << ptr[i] << std::endl;
}
ptr = new double[10];
for(int i = 0; i < 10; i++) {
  std::cout << ptr[i] << std::endl;
}

for(auto& i: p) {
  std::cout << i << std::endl;
}

delete[] ptr;


}

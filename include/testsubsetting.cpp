#include "etr.hpp"

void prt(VEC<double> inp) {
	for(int i = 0; i < inp.size(); i++) {
	std::cout << inp[i] << std::endl;
	}
}

int main() {

mat m(3, 5);
m = range(1, 15);


mat msub;
vec sub = range(5,5);
//msub = subset(m, sub, true);

//prt(m);
//prt(sub);
//std::cout << std::endl;
//prt(msub);

//msub = subset(m, true, sub);
//prt(msub);

vec sub1 = range(1, 2);
vec sub2 = range(2, 5);
msub = subset(m, sub1, sub2);
//prt(msub);


mat temp = subset(m,  sub1, true);

//print(m);

print(temp);

subassign(m, sub1, true) = 30.;

//print(m);
//prt(subset(m, sub1, true));

}

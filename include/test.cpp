#include "etr.hpp"

using namespace etr;

int main() {


    int size = 10;

    double* ptr1;
    ptr1 = new double[size];
    int cob = 0;
    sexp a(size, ptr1, cob); // copy
    delete [] ptr1;
    a = vector(3.14, 5);
    print(a);

    print();

    double* ptr2;
    ptr2 = new double[size];
    cob = 1;
    sexp b(size, ptr2, cob); // take ownership
    b = vector(5, 3);
    print(b);

    print();

    double* ptr3;
    ptr3 = new double[size];
    cob = 2;
    sexp c(size, ptr3, cob); // borrow ownership
    //c = vector(5, 3); --> error calls resize
    c = vector(4, 10);
    print(c);

    print();
    sexp d(size, ptr3, cob);
    d = d + 10;
    print(d);
    print();

    delete[] ptr3;

    

}

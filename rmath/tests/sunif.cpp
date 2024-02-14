#include "sunif.hpp"

void RandomState::PutRNGstate() {
    if (RNG_kind > 7 || N01_kind > 5 || Sample_kind > 2) {
        std::cerr << "Internal .Random.seed is corrupt: not saving" << std::endl;
        return;
    }
    unsigned int len_seed = sizeof(unsigned int);
    unsigned int kinds = RNG_kind + 100 * N01_kind + 10000 * Sample_kind;
    //I1 = kinds;
    // issue: understand rest of code in PutRNGstate in main/RNG.c
}

void Unif::set_seed(unsigned int I1_, unsigned int I2_) {
  this -> I1 = I1_; this -> I2 = I2_;
}

void Unif::get_seed(unsigned int& I1_, unsigned int& I2_) {
  I1_ = this -> I1; I2_ = this -> I2;
}

double Unif::operator()() {
  I1= 36969*(I1 & 0177777) + (I1>>16);
  I2= 18000*(I2 & 0177777) + (I2>>16);
  double res = ((I1 << 16)^(I2 & 0177777)) * 2.328306437080797e-10; /* in [0,1) */
  PutRNGstate();
  return res;
}



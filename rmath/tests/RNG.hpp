// within RNG.hpp/RNG.cpp the content of r-source/src/main/RNG.c will be
// rewritten In RNG.c the different RNGs are defined RNGkind() [1]
// "Mersenne-Twister" "Inversion"        "Rejection" The default RNG is Mersenne
// Twister --> is called "kind" in R The default N01 type is INVERSION --> is
// called "normal.kind" in R The default sample type is Rejection --> is called
// "sample.kind" in R

#include <iostream>

namespace RNG_R {

namespace Constants {
const double d2_32 = 4294967296;            // = (double)
const double i2_32m1 = 328306437080797e-10; // = 1/(2^32 - 1)
const double KT = 31322574615479e-10;       // = 2^-3

} // namespace Constants

inline double fixup(double x) {
  // ensure 0 and 1 are never returned
  if (x <= 0.0)
    return 0.5 * Constants::i2_32m1;
  if ((1.0 - x) <= 0.0)
    return 1.0 - 0.5 * Constants::i2_32m1;
  return x;
}

class MersenneTwister {
  const int N = 624;
  int32_t dummy[625];
  int32_t *mt = dummy + 1;
  int mti = 625; // N + 1
  const int M = 397;
  const int MATRIX_A = 0x9908b0df;
  const int UPPER_MASK = 0x80000000;
  const int LOWER_MASK = 0x7fffffff;
  const int TEMPERING_MASK_B = 0x9d2c5680;
  const int TEMPERING_MASK_C = 0xefc60000;

  int TEMPERING_SHIFT_U(int &y) { return y >> 11; }
  int TEMPERING_SHIFT_S(int &y) { return y << 7; }
  int TEMPERING_SHIFT_T(int &y) { return y << 15; }
  int TEMPERING_SHIFT_L(int &y) { return y >> 18; }

  void MT_sgenrand(int32_t seed) {
    // initialise array with seed = MT_sgenrand
    int i;
    for (i = 0; i < N; i++) {
      mt[i] = seed & 0xffff0000;
      seed = 69069 * seed + 1;
      mt[i] |= (seed & 0xffff0000) >> 16;
      seed = 69069 * seed + 1;
    }
    mti = N;
  }
  
public:
  MersenneTwister(int32_t seed) {
    for(int j = 0; j < 50; j++) {
	    seed = (69069 * seed + 1);
	  }
    std::cout << "seed after first mixing " << seed << std::endl;
    for(int j = 0; j < 625; j++) {
	    seed = (69069 * seed + 1);
	    dummy[j] = seed;
	  }
    std::cout << "seed after first mixing 2 " << seed << std::endl;

    MT_sgenrand(seed);
    std::cout << "seed after first mixing 3 " << seed << std::endl;

    dummy[0] = 624;
  }

  double operator()() { // MT_genrand
    int32_t y;
    int32_t mag01[2] = {0x0, MATRIX_A};
    // mag01[x] = x * MATRIX_A  for x=0,1

    mti = dummy[0];
    if (mti >= N) {
      std::cout << "mti >= N" << std::endl;
      // generate N words at one time
      int kk;

      if (mti == N + 1) {
        std::cout << "mti == N +1" << std::endl;
        MT_sgenrand(4357); // a default initial seed is used
      }   // if sgenrand() has not been called,


      for (kk = 0; kk < N - M; kk++) {
        y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
        mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
      }
      std::cout << "y = " << y << std::endl;
      for (; kk < N - 1; kk++) {
        y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
        mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
      }
      y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
      mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];
      mti = 0;
    }

    y = mt[mti++];
    std::cout << "y = " << y << std::endl;
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    dummy[0] = mti;
    return fixup(static_cast<double>(y * 2.3283064365386963e-10)); // reals: [0,1)-interval 
  }

  void FixupSeeds() {
      /*
	    if(initial) I1 = 624;
	    // No action unless user has corrupted .Random.seed 
	    if(I1 <= 0) I1 = 624;
	    // check for all zeroes 
	    for (j = 1; j <= 624; j++)
	    if(RNG_Table[RNG_kind].i_seed[j] != 0) {
		  notallzero = 1;
		    break;
	    }
	   if(!notallzero) Randomize(RNG_kind);
     */
  }
};

} // namespace RNG_R

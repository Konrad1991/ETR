#include <iomanip>    
#include <iostream>
#include <fstream>

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
  const int N = 625;
  int32_t seed_array[625];
  int32_t *mt = seed_array + 1;
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
      for(int j = 0; j < N; j++) {
        seed = (69069 * seed + 1);
        seed_array[j] = seed;
      }
      seed_array[0] = 624;

      // check if all are zero --> if not call Randomize

      std::ofstream outputFile("seed_own.txt");
       if (!outputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
      }
      for(size_t i = 0; i < N; i++) {
        outputFile << seed_array[i] << "\n";
      }
      outputFile.close();
    }

    double operator()(void) {
      int y;
      unsigned int mag01[2]={0x0, 0x9908b0df};
      mti = seed_array[0];
      if (mti >= N) {  // mti >= N --> this is not true as i dont convert currently: 6.2 kinds 10403 
        int kk;
        // if (mti == N+1) { MT_sgenrand(4357); }
        for (kk = 0; kk < N - M; kk++) {
          y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
          mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < N - 1; kk++) {
          y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
          mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
        mti = 0;
      }
      y = mt[mti++];
      y ^= TEMPERING_SHIFT_U(y);
      y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
      y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
      y ^= TEMPERING_SHIFT_L(y);
      seed_array[0] = mti;
      return ( (double)y * 2.3283064365386963e-10 ); /* reals: [0,1)-interval */
    }
};

} // namespace RNG_R
// https://gist.github.com/mclements/3668c89d73e4504f323ca57a71c65602

int main() {
  RNG_R::MersenneTwister ms(1234);
  std::cout << ms() << std::endl;
}



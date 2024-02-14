#include <iostream>
#include <string>
#include <unordered_map>

enum class Nkind {
  WICHMANN_HILL,
  MARSAGLIA_MULTICARRY,
  SUPER_DUPER,
  MERSENNE_TWISTER,
  KNUTH_TAOCP,
  USER_UNIF,
  KNUTH_TAOCP2,
  LECUYER_CMRG
};

enum class N01type{
    BUGGY_KINDERMAN_RAMAGE,
    AHRENS_DIETER,
    BOX_MULLER,
    USER_NORM,
    INVERSION,
    KINDERMAN_RAMAGE
};

enum class Sample_type {
  Rounding,
  Rejection
}; // issue: did not found the list

struct RNG_Info {
  int Nkind;
  std::string name;
  int n_seed;
  int32_t dummy[628]; // allow for optimizing compilers to read over bound
  RNG_Info(int Nkind, const std::string& name, int n_seed) :
    Nkind(Nkind), name(name), n_seed(n_seed) {}
};

template <Nkind>
class RNG_State {
public:
    void print() {
        std::cout << "Generic case" << std::endl;
    }
};

template<>
class RNG_State<Nkind:: WICHMANN_HILL> {
public:
  RNG_Info rf;
  RNG_State(): rf(static_cast<int>(N01type::BUGGY_KINDERMAN_RAMAGE),
              "WICHMANN_HILL", 3) {}
};

/*
static
RNGTAB RNG_Table[] =
{
// kind Nkind	  name	           n_seed      i_seed 
    { WICHMANN_HILL,        BUGGY_KINDERMAN_RAMAGE, "Wichmann-Hill",	     3,	dummy},
    { MARSAGLIA_MULTICARRY, BUGGY_KINDERMAN_RAMAGE, "Marsaglia-MultiCarry",  2,	dummy},
    { SUPER_DUPER,          BUGGY_KINDERMAN_RAMAGE, "Super-Duper",	     2,	dummy},
    { MERSENNE_TWISTER,     BUGGY_KINDERMAN_RAMAGE, "Mersenne-Twister",  1+624,	dummy},
    { KNUTH_TAOCP,          BUGGY_KINDERMAN_RAMAGE, "Knuth-TAOCP",       1+100,	dummy},
    { USER_UNIF,            BUGGY_KINDERMAN_RAMAGE, "User-supplied",         0,	dummy},
    { KNUTH_TAOCP2,         BUGGY_KINDERMAN_RAMAGE, "Knuth-TAOCP-2002",  1+100,	dummy},
    { LECUYER_CMRG,         BUGGY_KINDERMAN_RAMAGE, "L'Ecuyer-CMRG",         6,	dummy},
};
*/

/* A version of Marsaglia-MultiCarry */
class RandomState {
public:
   int RNG_kind = 0;
   int N01_kind = 0;
   int Sample_kind = 0;
  
   unsigned int I1 = 1234;
   unsigned int I2 = 5678;

   RandomState() {}
   RandomState(int RNG_kind_, int N01_kind_, int Sample_kind_, unsigned int I1,
              unsigned int I2)
      : RNG_kind(RNG_kind_), N01_kind(N01_kind_), Sample_kind(Sample_kind_),
        I1(I1), I2(I2) {}
   void PutRNGstate();
};


class Unif: public RandomState {

public:
  Unif() : RandomState() {}
  Unif(int RNG_kind_, int N01_kind_, int Sample_kind_, unsigned int I1, unsigned int I2)
        : RandomState(RNG_kind_, N01_kind_, Sample_kind_, I1, I2) {}
  double operator()();

  void set_seed(unsigned int I1_, unsigned int I2_);
  void get_seed(unsigned int &I1_, unsigned int &I2_);
};



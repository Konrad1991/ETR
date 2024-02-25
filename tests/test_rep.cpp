/*
        Var1       Var2
1 arithmetic arithmetic  done
2        Vec arithmetic  done
3  Operation arithmetic  done
4 arithmetic        Vec  done 
5        Vec        Vec  done
6  Operation        Vec  done
7 arithmetic  Operation  done
8        Vec  Operation
9  Operation  Operation

In Operation also Rvecs are included
*/

#define STANDALONE
#include "../include/etr.hpp"
using namespace etr;
#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"

bool deq(double a, double b) {
      return std::fabs(a - b) < 1E-3;
}

template<typename L, typename R>
bool eq(L inp1, R inp2) {
  ass(inp1.size() == inp2.size(), "Error");
  bool test = true;
  for(int i = 0; i < inp1.size(); i++) {
    if(deq(inp1[i], inp2[i]) == false) {
      test = false;
      break;
    }
  }
  return test;
}

template<typename T>
bool eq(T inp1, double inp2) {
  bool test = true;
  for(int i = 0; i < inp1.size(); i++) {
    if(deq(inp1[i], inp2) == false) {
      test = false;
      break;
    }
  }

  return test;
}

bool eqb(Vec<bool> inp1, Vec<bool> inp2) {
  ass(inp1.size() == inp2.size(), "Error");
  bool test = true;
  for(int i = 0; i < inp1.size(); i++) {
    if(inp1[i] != inp2[i]) {
      test = false;
      break;
    }
  }
  return test;
}

TEST_CASE( "vector & rep" ) {
  Vec<double> a = rep(1.5, 5);
  Vec<double> atrue = coca(1.5, 1.5, 1.5, 1.5, 1.5);
  REQUIRE(eq(a, atrue));
  
  Vec<int> b = rep(3, 3); 
  REQUIRE(eq(b, std::vector<int>{3, 3, 3}));

  print(Vec<int>(3) + 0.0);
  // Vec<int> c = rep(coca(1.0, 2.0, 3.0) - 0.0, 2);

  /*
  print(c);
  
  sexp d = coca(1, 2, 3) + coca(1, 2, 3);
  print(d);

  sexp e = coca(1, 2, 3) + 3.14;
  print(e);

  REQUIRE(eq(c, std::vector<int>{1, 2, 3, 1, 2, 3}));
  */
}



#include "../include/etr.hpp"


#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"

bool deq(double a, double b) {
      return std::fabs(a - b) < 1E-3;
}


bool eq(sexp inp1, sexp inp2) {

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




bool eq(sexp inp1, double inp2) {

  bool test = true;

  for(int i = 0; i < inp1.size(); i++) {
    if(deq(inp1[i], inp2) == false) {
      test = false;
      break;
    }
  }

  return test;
}




bool eqb(VEC<bool> inp1, VEC<bool> inp2) {

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

TEST_CASE( "plus" ) {

  sexp s, v, m;
  s = 1;
  s = s + 3;
  REQUIRE(subset(s, 1)[0] == 4);

  v = s + vector(4, 4);
  REQUIRE(eq(v, vector(8, 4)) == true);

  v = vector(4, 4);
  v = v + 30;
  REQUIRE(eq(v, vector(34, 4)) == true);

  REQUIRE(eq(v + 3, vector(37, 4)) == true);
  REQUIRE(eq(3 + v, vector(37, 4)) == true);

  m = s + matrix(2, 2, 2);
  REQUIRE(eq(m, vector(6, 4)));


  m = matrix(2, 2, 2);
  m = m + 40;
  REQUIRE(eq(m, vector(42, 4)));

  m = v + m;
  REQUIRE(eq(m, vector(76, 4)));

  m = m + v;
  REQUIRE(eq(m, vector(110, 4)));
}



TEST_CASE( "minus" ) {

  sexp s, v, m;
  s = 1;
  s = s - 3;
  REQUIRE(subset(s, 1)[0] == -2);

  v = s - vector(4, 4);
  REQUIRE(eq(v, vector(-6, 4)));

  v = vector(4, 4);
  v = v - 30;
  REQUIRE(eq(v, vector(-26, 4)) == true);
  REQUIRE(eq(v - 3, vector(-29, 4)) == true);
  REQUIRE(eq(3 - v, vector(29, 4)) == true);

  m = s - matrix(2, 2, 2);
  REQUIRE(eq(m, vector(-4, 4)));

  m = matrix(2, 2, 2);
  m = m - 40;
  REQUIRE(eq(m, vector(-38, 4)));

  m = v - m;
  REQUIRE(eq(m, vector(12, 4)));

  m = m - v;
  REQUIRE(eq(m, vector(38, 4)));

}




TEST_CASE( "divide" ) {

  sexp s, v, m;
  s = 3;
  s = s / 3;
  REQUIRE(subset(s, 1)[0] == 1);

  v = s / vector(4, 4);
  REQUIRE(eq(v, vector(0.25, 4)));

  v = vector(4, 4);
  v = v / 2;
  REQUIRE(eq(v, vector(2, 4)));
  REQUIRE(eq(v / 3., vector(2./3., 4)) == true);
  REQUIRE(eq(3. / v, vector(3./2., 4)) == true);

  m = s / matrix(2, 2, 2);
  REQUIRE(eq(m, vector(0.5, 4)));

  m = matrix(2, 2, 2);
  m = m / 40;
  REQUIRE(eq(m, vector(0.05, 4)));

  m = v / m;
  REQUIRE(eq(m, vector(40, 4)));

  m = m / v;
  REQUIRE(eq(m, vector(20, 4)));

}



TEST_CASE( "multiply" ) {

  sexp s, v, m;
  s = 3;
  s = s * 3;
  REQUIRE(subset(s, 1)[0] == 9);

  v = s * vector(4, 4);
  REQUIRE(eq(v, vector(36, 4)));

  v = vector(4, 4);
  v = v * 2;
  REQUIRE(eq(v, vector(8, 4)));
  REQUIRE(eq(v * 3., vector(24, 4)) == true);
  REQUIRE(eq(3*v, vector(24, 4)) == true);



  m = s * matrix(2, 2, 2);
  for(auto i: m) {
    REQUIRE(i == 18);
  }


  m = matrix(2, 2, 2);
  m = m * 40;
  for(auto i: m) {
    REQUIRE(i == 80);
  }


  m = v * m;
  for(auto i: m) {
    REQUIRE(i == 640);
  }

  m = m * v;
  for(auto i: m) {
    REQUIRE(i == 5120);
  }


}




TEST_CASE( "colon" ) {

  REQUIRE(eq(colon(1, 3), coca(1, 2, 3)) == true);
  REQUIRE(eq(colon(1., 3.), coca(1, 2, 3)) == true);
  REQUIRE(eq(colon(1., 3), coca(1, 2, 3)) == true);
  REQUIRE(eq(colon(1, 3.), coca(1, 2, 3)) == true);

  sexp temp1(1, 1.0);
  REQUIRE(eq(colon(temp1, 3.), coca(1, 2, 3)) == true);
  REQUIRE(eq(colon(temp1, 3), coca(1, 2, 3)) == true);

  sexp temp2(1, 3.0);
  REQUIRE(eq(colon(1., temp2), coca(1, 2, 3)) == true);
  REQUIRE(eq(colon(1, temp2), coca(1, 2, 3)) == true);

  REQUIRE(eq(colon(temp1, temp2), coca(1, 2, 3)) == true);

  REQUIRE(length(1) == length(3.14));
  REQUIRE(length(1) == length(true));

  sexp temp3 = matrix(4, 2, 2);
  sexp temp4 = matrix(5, 3, 4);

  REQUIRE(dim(temp3)[0] == 2);
  REQUIRE(dim(temp3)[1] == 2);

  REQUIRE(dim(temp4)[0] == 3);
  REQUIRE(dim(temp4)[1] == 4);

}


TEST_CASE( "allocation" ) {

  sexp a = vector(50);
  REQUIRE(length(a) == 50);

  sexp b = vector(3.14, 50);
  REQUIRE(eq(b, vector(3.14, 50)));

  sexp c = vector(b);
  REQUIRE(eq(c, vector(3.14, 50)));

  sexp d = matrix(3.5, 2, 2);
  REQUIRE(eq(d, vector(3.5, 4)));

  sexp e = matrix(2, 5);
  REQUIRE(length(e) == 10);

  sexp f = matrix(d, 4, 1);
  REQUIRE(eq(f, vector(3.5, 4)));
}


TEST_CASE( "comparison == " ) {
  sexp v1 = coca(1, 2, 3, 4);
  sexp v2 = coca(1, 2, 4, 4);

  VEC<bool> res(4);
  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = true;

  VEC<bool> a = v1 == v2;
  REQUIRE(eqb(a, res) == true);
  REQUIRE(eqb(v1 == v2, res) == true);
  REQUIRE(eqb(v1 == coca(1, 2, 4, 4), res) == true);
  REQUIRE(eqb(coca(1,2,3,4) == v2, res) == true);
  REQUIRE(eqb(coca(1, 2, 3, 4) == coca(1, 2, 4, 4), res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = false;
  VEC<bool> b = v1 == 3;
  REQUIRE(eqb(b, res) == true);
  REQUIRE(eqb(v1 == 3, res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = false;
  VEC<bool> c = 3 == v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3==v1, res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = false;
  VEC<bool> d = v1 == 3.0;
  REQUIRE(eqb(d, res) == true);
  REQUIRE(eqb(v1 == 3.0, res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = false;
  VEC<bool> e = 3.0 == v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3.0==v1, res) == true);
}


TEST_CASE( "comparison >= " ) {
  sexp v1 = coca(1, 2, 3, 4);
  sexp v2 = coca(1, 2, 4, 4);

  VEC<bool> res(4);
  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = true;

  VEC<bool> a = v1 >= v2;
  REQUIRE(eqb(a, res) == true);
  REQUIRE(eqb(v1 >= v2, res) == true);
  REQUIRE(eqb(v1 >= coca(1, 2, 4, 4), res) == true);
  REQUIRE(eqb(coca(1,2,3,4) >= v2, res) == true);
  REQUIRE(eqb(coca(1, 2, 3, 4) >= coca(1, 2, 4, 4), res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = true;
  VEC<bool> b = v1 >= 3;
  REQUIRE(eqb(b, res) == true);
  REQUIRE(eqb(v1 >= 3, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = true;
  res[3] = false;
  VEC<bool> c = 3 >= v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3>=v1, res) == true);


  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = true;
  VEC<bool> d = v1 >= 3.0;
  REQUIRE(eqb(d, res) == true);
  REQUIRE(eqb(v1 >= 3.0, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = true;
  res[3] = false;
  VEC<bool> e = 3.0 >= v1;
  REQUIRE(eqb(e, res) == true);
  REQUIRE(eqb(3.0>=v1, res) == true);
}

TEST_CASE( "comparison > " ) {
  sexp v1 = coca(1, 2, 3, 5);
  sexp v2 = coca(1, 2, 4, 4);

  VEC<bool> res(4);
  res[0] = false;
  res[1] = false;
  res[2] = false;
  res[3] = true;

  VEC<bool> a = v1 > v2;
  REQUIRE(eqb(a, res) == true);
  REQUIRE(eqb(v1 > v2, res) == true);
  REQUIRE(eqb(v1 > coca(1, 2, 4, 4), res) == true);
  REQUIRE(eqb(coca(1,2,3,5) > v2, res) == true);
  REQUIRE(eqb(coca(1, 2, 3, 5) > coca(1, 2, 4, 4), res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = false;
  res[3] = true;
  VEC<bool> b = v1 > 3.;
  REQUIRE(eqb(b, res) == true);
  REQUIRE(eqb(v1 > 3., res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = false;
  VEC<bool> c = 3. > v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3.>v1, res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = false;
  res[3] = true;
  VEC<bool> d = v1 > 3;
  REQUIRE(eqb(d, res) == true);
  REQUIRE(eqb(v1 > 3, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = false;
  VEC<bool> e = 3 > v1;
  REQUIRE(eqb(e, res) == true);
  REQUIRE(eqb(3>v1, res) == true);
}


TEST_CASE( "comparison <= " ) {
  sexp v1 = coca(1, 2, 3, 5);
  sexp v2 = coca(1, 2, 4, 4);

  VEC<bool> res(4);
  res[0] = true;
  res[1] = true;
  res[2] = true;
  res[3] = false;

  VEC<bool> a = v1 <= v2;
  REQUIRE(eqb(a, res) == true);
  REQUIRE(eqb(v1 <= v2, res) == true);
  REQUIRE(eqb(v1 <= coca(1, 2, 4, 4), res) == true);
  REQUIRE(eqb(coca(1,2,3,5) <= v2, res) == true);
  REQUIRE(eqb(coca(1, 2, 3, 5) <= coca(1, 2, 4, 4), res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = true;
  res[3] = false;
  VEC<bool> b = v1 <= 3.;
  REQUIRE(eqb(b, res) == true);
  REQUIRE(eqb(v1 <= 3., res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = true;
  VEC<bool> c = 3. <= v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3.<=v1, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = true;
  res[3] = false;
  VEC<bool> d = v1 <= 3;
  REQUIRE(eqb(d, res) == true);
  REQUIRE(eqb(v1 <= 3, res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = true;
  VEC<bool> e = 3 <= v1;
  REQUIRE(eqb(e, res) == true);
  REQUIRE(eqb(3<=v1, res) == true);
}


TEST_CASE( "comparison < " ) {
  sexp v1 = coca(1, 2, 3, 5);
  sexp v2 = coca(1, 2, 4, 6);

  VEC<bool> res(4);
  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = true;

  VEC<bool> a = v1 < v2;
  REQUIRE(eqb(a, res) == true);
  REQUIRE(eqb(v1 < v2, res) == true);
  REQUIRE(eqb(v1 < coca(1, 2, 4, 6), res) == true);
  REQUIRE(eqb(coca(1,2,3,5) < v2, res) == true);
  REQUIRE(eqb(coca(1, 2, 3, 5) < coca(1, 2, 4, 6), res) == true);

  res[0] = true;
  res[1] = false;
  res[2] = false;
  res[3] = false;
  VEC<bool> b = v1 < 2.;
  REQUIRE(eqb(b, res) == true);
  REQUIRE(eqb(v1 < 2., res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = false;
  res[3] = true;
  VEC<bool> c = 3. < v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3.<v1, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = false;
  VEC<bool> d = v1 < 3;
  REQUIRE(eqb(d, res) == true);
  REQUIRE(eqb(v1 < 3, res) == true);

  res[0] = false;
  res[1] = false;
  res[2] = false;
  res[3] = true;
  VEC<bool> e = 3 < v1;
  REQUIRE(eqb(e, res) == true);
  REQUIRE(eqb(3<v1, res) == true);
}



TEST_CASE( "comparison != " ) {
  sexp v1 = coca(1, 2, 3, 5);
  sexp v2 = coca(1, 2, 4, 6);

  VEC<bool> res(4);
  res[0] = false;
  res[1] = false;
  res[2] = true;
  res[3] = true;

  VEC<bool> a = v1 != v2;
  REQUIRE(eqb(a, res) == true);
  REQUIRE(eqb(v1 < v2, res) == true);
  REQUIRE(eqb(v1 < coca(1, 2, 4, 6), res) == true);
  REQUIRE(eqb(coca(1,2,3,5) != v2, res) == true);
  REQUIRE(eqb(coca(1, 2, 3, 5) != coca(1, 2, 4, 6), res) == true);

  res[0] = true;
  res[1] = false;
  res[2] = true;
  res[3] = true;
  VEC<bool> b = v1 != 2.;
  REQUIRE(eqb(b, res) == true);
  REQUIRE(eqb(v1 != 2., res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = true;
  VEC<bool> c = 3. != v1;
  REQUIRE(eqb(c, res) == true);
  REQUIRE(eqb(3.!=v1, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = true;
  VEC<bool> d = v1 != 3;
  REQUIRE(eqb(d, res) == true);
  REQUIRE(eqb(v1 != 3, res) == true);

  res[0] = true;
  res[1] = true;
  res[2] = false;
  res[3] = true;
  VEC<bool> e = 3 != v1;
  REQUIRE(eqb(e, res) == true);
  REQUIRE(eqb(3!=v1, res) == true);
}



TEST_CASE( "concatenate" ) {

  sexp a = coca(1, 2, 3);
  sexp res1(3);
  res1[0] = 1.;
  res1[1] = 2.;
  res1[2] = 3.;
  REQUIRE(eq(a, res1) == true);

  sexp b = coca(a, 100);
  sexp res2(4);
  res2[0] = 1.;
  res2[1] = 2.;
  res2[2] = 3.;
  res2[3] = 100.;
  REQUIRE(eq(b, res2) == true);

  sexp c = coca(100, a);
  sexp res3(4);
  res3[0] = 100.;
  res3[1] = 1.;
  res3[2] = 2.;
  res3[3] = 3.;
  REQUIRE(eq(c, res3) == true);


  sexp d = coca(a, a);
  sexp res4(6);
  res4[0] = 1.;
  res4[1] = 2.;
  res4[2] = 3.;
  res4[3] = 1.;
  res4[4] = 2.;
  res4[5] = 3.;
  REQUIRE(eq(d, res4) == true);

}


TEST_CASE( "exponent & log" ) {
  sexp a = coca(1, 2, 3, 4);
  a = a^2;
  sexp res(4);
  res[0] = 1.;
  res[1] = 4.;
  res[2] = 9.;
  res[3] = 16.;
  REQUIRE(eq(a, res) == true);

  sexp b = coca(1, 2, 3, 4);
  b = exp(b, 2);
  REQUIRE(eq(b, res) == true);

  REQUIRE(exp(2, 2) == 4);

  a = coca(1, 2, 3, 4);
  a = ln(a);
  res[0] = 0.;
  res[1] = 0.693147;
  res[2] = 1.098612;
  res[3] = 1.386294;
  REQUIRE(eq(a, res) == true);

  REQUIRE(ln(1) == 0);

}

TEST_CASE( "printing" ) {

  sexp scalar = 1.5;
  sexp vec = vector(3.14, 2);
  sexp mat = matrix(3.14, 2, 3);

  print(1);
  print(3.14);
  print("text");
  print(true);
  print(scalar);
  print(vec);
  print(mat);
  print();
  print(coca(1,2));
  print(matrix(3, 2, 1));

}



TEST_CASE( "vector subsetting" ) {

  sexp a = colon(1, 5);
  sexp b = coca(1, 3, 5);
  sexp res(3);
  res[0] = 1;
  res[1] = 3;
  res[2] = 5;

  REQUIRE(eq(subset(a), a) == true);
  REQUIRE(eq(subset(a, 1), 1) == true);
  REQUIRE(eq(subset(a, 1.5), 1) == true);
  REQUIRE(eq(subset(a, nullptr), a) == true);
  REQUIRE(eq(subset(a, true), a) == true);
  REQUIRE(eq(subset(a, false), vector(0)) == true);
  REQUIRE(eq(subset(a, b), res) == true);
  REQUIRE(eq(subset(a, coca(1, 3, 5)), res) == true);


  VEC<bool> rb(5);
  rb[0] = true;
  rb[1] = false;
  rb[2] = false;
  rb[3] = false;
  rb[4] = false;
  REQUIRE(subset(a, a == b)[0] == 1);
}



TEST_CASE( "matrix subsetting" ) {

  sexp a = matrix(colon(1, 15), 3, 5);
  sexp r = coca(1, 3);
  sexp c = coca(1, 2, 5, 3);
  sexp res(8);
  res[0] = 1;
  res[1] = 3;
  res[2] = 4;
  res[3] = 6;
  res[4] = 13;
  res[5] = 15;
  res[6] = 7;
  res[7] = 9;
  REQUIRE(eq(subset(a, r, c), res) == true);
  REQUIRE(eq(subset(a, coca(1, 3), c), res) == true);
  REQUIRE(eq(subset(a, r, coca(1,2,5,3)), res) == true);
  REQUIRE(eq(subset(a, coca(1,3), coca(1,2,5,3)), res) == true);
  REQUIRE(eq(subset(a, true, true), a) == true);
  REQUIRE(eq(subset(a, true, nullptr), a) == true);
  REQUIRE(eq(subset(a, nullptr, true), a) == true);
  REQUIRE(eq(subset(a, nullptr, nullptr), a) == true);
  REQUIRE(eq(subset(a, false, true), vector(0)) == true);
  REQUIRE(eq(subset(a, true, false), vector(0)) == true);

  REQUIRE( eq(subset(a, 1, 1), 1) == true);
  REQUIRE( eq(subset(a, 1, 1.5),1)== true);
  REQUIRE( eq(subset(a, 1.5, 1), 1)== true);
  REQUIRE( eq(subset(a, 1.5, 1.5), 1)== true);

  res = coca(1, 4, 7, 10, 13);
  REQUIRE(eq(subset(a, 1, true), res) == true);
  REQUIRE(eq(subset(a, 1.5, true), res) == true);
  REQUIRE(eq(subset(a, 1, false), vector(0)) == true);
  REQUIRE(eq(subset(a, 1, nullptr), res) == true);
  REQUIRE(eq(subset(a, 1.5, nullptr), res) == true);

  res = coca(1, 4, 13, 7);
  REQUIRE(eq(subset(a, 1, c), res) == true);

  sexp temp1 = coca(1, 1, 1, 1, 2);
  sexp temp2 = coca(1, 1, 1, 1, 1);
  res = coca(1, 4, 7, 10);
  REQUIRE(eq(subset(a, 1, temp1 == temp2), res) == true);

  res = coca(1, 2, 3);
  REQUIRE(eq(subset(a, true, 1), res) == true);
  REQUIRE(eq(subset(a, nullptr, 1), res) == true);

  res = coca(4, 6);
  REQUIRE(eq(subset(a, r, 2), res) == true);

  temp1 = coca(1, 2, 3);
  temp2 = coca(1, 3, 3);
  res = coca(1, 3);
  REQUIRE(eq(subset(a, temp1 == temp2, 1), res) == true);

  REQUIRE(subset(a, 1.5, 1.5)[0] == 1);

  res = coca(1, 7);
  REQUIRE(eq(subset(a, 1.5, coca(1, 3)), res) == true);

  temp1 = coca(1, 5);
  temp2 = coca(1, 1);
  res = coca(1);
  REQUIRE(eq(subset(a, 1.5, temp1 == temp2), res) == true);

  res = coca(1, 2, 3);
  REQUIRE(eq(subset(a, true, 1.5), res) == true);
  REQUIRE(eq(subset(a, nullptr, 1.5), res) == true);

  res = coca(1, 2, 2);
  REQUIRE(eq(subset(a, coca(1, 2, 2), 1.5), res) == true);

  temp1 = coca(1, 2, 3);
  temp2 = coca(1, 1, 3);
  res = coca(13, 15);
  REQUIRE(eq(subset(a, temp1 == temp2, 5.5), res) == true);


  c = coca(1, 2, 5);
  res = coca(1, 2, 3, 4, 5, 6, 13, 14, 15);
  REQUIRE(eq(subset(a, true, c), res) == true);
  REQUIRE(eq(subset(a, nullptr, c), res) == true);

  res = coca(1, 2, 3, 7, 8, 9);
  REQUIRE(eq(subset(a, true, temp1 == temp2), res) == true);
  REQUIRE(eq(subset(a, nullptr, temp1 == temp2), res) == true);

  r = coca(2);
  res = coca(2, 5, 8, 11, 14);
  REQUIRE(eq(subset(a, r, true), res) == true);

  res = coca(1, 2, 3, 7, 8, 9);
  REQUIRE(eq(subset(a, true, temp1 == temp2), res) == true);
}




TEST_CASE( "subassign vector" ) {

sexp a, pos, temp;

a = vector(colon(0, 9));
temp = a;

subassign(a, 1) = 100;
subassign(a, 2.5) = 200;
REQUIRE(subset(a, 1)[0] == 100.0);
REQUIRE(subset(a, 2.5)[0] == 200.0);
a = temp;

pos = coca(1, 6, 7, 2);
subassign(a, pos) = range(1, 4);
REQUIRE(subset(a, 1)[0] == 1.0);
REQUIRE(subset(a, 6)[0] == 2.0);
REQUIRE(subset(a, 7)[0] == 3.0);
REQUIRE(subset(a, 2)[0] == 4.0);
a = temp;

VEC<bool> pb(4);
pb[0] = true;
pb[1] = true;
pb[2] = false;
pb[3] = true;
subassign(a, pb) = range(1, 3);
REQUIRE(subset(a, 1)[0] == 1.0);
REQUIRE(subset(a, 2)[0] == 2.0);
REQUIRE(subset(a, 4)[0] == 3.0);
a = temp;


subassign(a, true) = -60;
for(auto i: a) {
  REQUIRE(i == -60);
}
subassign(a, nullptr) = -50;
for(auto i: a) {
  REQUIRE(i == -50);
}

}



TEST_CASE( "subassign matrix" ) {

  sexp a, r, c, temp;
  VEC<bool> cb(8);
  VEC<bool> rb(6);

  a = matrix(colon(0, 34), 5, 7);
  temp = a;
  r = coca(1, 2, 5);
  c = coca(1, 3, 2);
  cb[0] = true;
  cb[1] = true;
  cb[2] = true;
  cb[3] = true;
  cb[4] = false;
  cb[5] = false;
  cb[6] = false;
  cb[7] = true;

  rb[0] = true;
  rb[1] = false;
  rb[2] = true;
  rb[3] = true;
  rb[4] = true;
  rb[5] = true;

subassign(a, 1, 1) = 100;
subassign(a, 1, 2.5) = 200;
REQUIRE(subset(a, 1, 1)[0] == 100.0);
REQUIRE(subset(a, 1, 2.5)[0] == 200.0);

c = coca(1, 5);
subassign(a, 3, c) = coca(1000, 2000);
subassign(a, 4, cb) = coca(100, 200, 300, 400, 500);
REQUIRE(subset(a, 3, 1)[0] == 1000.0);
REQUIRE(subset(a, 3, 5)[0] == 2000.0);

REQUIRE(subset(a, 4, cb)[0] == 500.0);
REQUIRE(subset(a, 4, cb)[1] == 200.0);
REQUIRE(subset(a, 4, cb)[2] == 300.0);
REQUIRE(subset(a, 4, cb)[3] == 400.0);
REQUIRE(subset(a, 4, cb)[4] == 500.0);


a = temp;
subassign(a, true, 5) = coca(-1, -2, -3, -4, -5);
subassign(a, nullptr, 1) = coca(-1, -2, -3, -4, -5);
REQUIRE(subset(a, true, 5)[0] == -1);
REQUIRE(subset(a, true, 5)[1] == -2);
REQUIRE(subset(a, true, 5)[2] == -3);
REQUIRE(subset(a, true, 5)[3] == -4);
REQUIRE(subset(a, true, 5)[4] == -5);

REQUIRE(subset(a, true, 1)[0] == -1);
REQUIRE(subset(a, true, 1)[1] == -2);
REQUIRE(subset(a, true, 1)[2] == -3);
REQUIRE(subset(a, true, 1)[3] == -4);
REQUIRE(subset(a, true, 1)[4] == -5);
a = temp;

r = coca(1, 2, 3);
subassign(a, r, 2) = coca(1.5, 2.5, 3.5);
VEC<bool> rb_(6);
rb_[0] = true;
rb_[1] = true;
rb_[2] = true;
rb_[3] = false;
rb_[4] = false;
rb_[5] = true;
subassign(a, rb_, 3) = coca(1, 2, 3, 50);
REQUIRE(subset(a, rb_, 3)[0] == 50);
REQUIRE(subset(a, rb_, 3)[1] == 2);
REQUIRE(subset(a, rb_, 3)[2] == 3);
a = temp;

subassign(a, true, true) = -50;
for(auto i: a) {
  REQUIRE(i == -50);
}
subassign(a, true, nullptr) = -60;
for(auto i: a) {
  REQUIRE(i == -60);
}

a = temp;

c = coca(1, 5, 7);
subassign(a, true, c) = colon(101, 115);
REQUIRE(subset(a, true, c)[0] == 101.0);
REQUIRE(subset(a, true, c)[1] == 102.0);
REQUIRE(subset(a, true, c)[2] == 103.0);
REQUIRE(subset(a, true, c)[3] == 104.0);
REQUIRE(subset(a, true, c)[4] == 105.0);
REQUIRE(subset(a, true, c)[5] == 106.0);
REQUIRE(subset(a, true, c)[6] == 107.0);
REQUIRE(subset(a, true, c)[7] == 108.0);
REQUIRE(subset(a, true, c)[8] == 109.0);
REQUIRE(subset(a, true, c)[9] == 110.0);
REQUIRE(subset(a, true, c)[10] == 111.0);
REQUIRE(subset(a, true, c)[11] == 112.0);
REQUIRE(subset(a, true, c)[12] == 113.0);
REQUIRE(subset(a, true, c)[13] == 114.0);
REQUIRE(subset(a, true, c)[14] == 115.0);
a = temp;



VEC<bool> cb_(8);
cb_[0] = true;
cb_[1] = false;
cb_[2] = false;
cb_[3] = false;
cb_[4] = false;
cb_[5] = false;
cb_[6] = true;
cb_[7] = true;
subassign(a, true, cb_) = colon(91, 105);
REQUIRE(subset(a, 1, 1)[0] == 101.0);
REQUIRE(subset(a, 2, 1)[0] == 102.0);
REQUIRE(subset(a, 3, 1)[0] == 103.0);
REQUIRE(subset(a, 4, 1)[0] == 104.0);
REQUIRE(subset(a, 5, 1)[0] == 105.0);
REQUIRE(subset(a, 1, 7)[0] == 96.0);
REQUIRE(subset(a, 2, 7)[0] == 97.0);
REQUIRE(subset(a, 3, 7)[0] == 98.0);
REQUIRE(subset(a, 4, 7)[0] == 99.0);
REQUIRE(subset(a, 5, 7)[0] == 100.0);

a = temp;


subassign(a, nullptr, true) = -10;
for(auto i: a) {
  REQUIRE(i == -10);
}
a = temp;


r = coca(1, 5, 3);
subassign(a, r, true) = colon(1, 21);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 5, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 2)[0] == 4.0);
REQUIRE(subset(a, 5, 2)[0] == 5.0);
REQUIRE(subset(a, 3, 2)[0] == 6.0);
REQUIRE(subset(a, 1, 3)[0] == 7.0);
REQUIRE(subset(a, 5, 3)[0] == 8.0);
REQUIRE(subset(a, 3, 3)[0] == 9.0);
REQUIRE(subset(a, 1, 4)[0] == 10.0);
REQUIRE(subset(a, 5, 4)[0] == 11.0);
REQUIRE(subset(a, 3, 4)[0] == 12.0);
REQUIRE(subset(a, 1, 5)[0] == 13.0);
REQUIRE(subset(a, 5, 5)[0] == 14.0);
REQUIRE(subset(a, 3, 5)[0] == 15.0);
REQUIRE(subset(a, 1, 6)[0] == 16.0);
REQUIRE(subset(a, 5, 6)[0] == 17.0);
REQUIRE(subset(a, 3, 6)[0] == 18.0);
REQUIRE(subset(a, 1, 7)[0] == 19.0);
REQUIRE(subset(a, 5, 7)[0] == 20.0);
REQUIRE(subset(a, 3, 7)[0] == 21.0);
a = temp;


VEC<bool> temp_(2);
temp_[0] = true;
temp_[1] = true;
subassign(a, temp_, true) = range(1, 14);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 2, 1)[0] == 2.0);
REQUIRE(subset(a, 1, 2)[0] == 3.0);
REQUIRE(subset(a, 2, 2)[0] == 4.0);
REQUIRE(subset(a, 1, 3)[0] == 5.0);
REQUIRE(subset(a, 2, 3)[0] == 6.0);
REQUIRE(subset(a, 1, 4)[0] == 7.0);
REQUIRE(subset(a, 2, 4)[0] == 8.0);
REQUIRE(subset(a, 1, 5)[0] == 9.0);
REQUIRE(subset(a, 2, 5)[0] == 10.0);
REQUIRE(subset(a, 1, 6)[0] == 11.0);
REQUIRE(subset(a, 2, 6)[0] == 12.0);
REQUIRE(subset(a, 1, 7)[0] == 13.0);
REQUIRE(subset(a, 2, 7)[0] == 14.0);
a = temp;


subassign(a, nullptr, nullptr) = -20;
for(auto i: a) {
  REQUIRE(i == -20);
}
a = temp; print();


r = coca(1, 5, 3);
c = coca(1, 7, 5);
subassign(a, r, c) = range(1, 9);

REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 5, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 7)[0] == 4.0);
REQUIRE(subset(a, 5, 7)[0] == 5.0);
REQUIRE(subset(a, 3, 7)[0] == 6.0);
REQUIRE(subset(a, 1, 5)[0] == 7.0);
REQUIRE(subset(a, 5, 5)[0] == 8.0);
REQUIRE(subset(a, 3, 5)[0] == 9.0);
a = temp;


VEC<bool> temp2(4);
temp2[0] = true;
temp2[1] = true;
temp2[2] = false;
temp2[3] = true;
subassign(a, r, temp2) = colon(1, 9);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 5, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 2)[0] == 4.0);
REQUIRE(subset(a, 5, 2)[0] == 5.0);
REQUIRE(subset(a, 3, 2)[0] == 6.0);
REQUIRE(subset(a, 1, 4)[0] == 7.0);
REQUIRE(subset(a, 5, 4)[0] == 8.0);
REQUIRE(subset(a, 3, 4)[0] == 9.0);

a = temp;
c = coca(1, 7, 2);
subassign(a, temp2, c) = range(1, 9);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 2, 1)[0] == 2.0);
REQUIRE(subset(a, 4, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 7)[0] == 4.0);
REQUIRE(subset(a, 2, 7)[0] == 5.0);
REQUIRE(subset(a, 4, 7)[0] == 6.0);
REQUIRE(subset(a, 1, 2)[0] == 7.0);
REQUIRE(subset(a, 2, 2)[0] == 8.0);
REQUIRE(subset(a, 4, 2)[0] == 9.0);
a = temp;


VEC<bool> temp3(3);
temp3[0] = true;
temp3[1] = true;
temp3[2] = true;

VEC<bool> temp4(3);
temp4[0] = true;
temp4[1] = false;
temp4[2] = true;
subassign(a, temp3, temp4) = range(1, 6);
REQUIRE(subset(a, 1, 1)[0] == 1.0);
REQUIRE(subset(a, 2, 1)[0] == 2.0);
REQUIRE(subset(a, 3, 1)[0] == 3.0);
REQUIRE(subset(a, 1, 3)[0] == 4.0);
REQUIRE(subset(a, 2, 3)[0] == 5.0);
REQUIRE(subset(a, 3, 3)[0] == 6.0);
print(sinus(0));

}

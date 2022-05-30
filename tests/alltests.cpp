#include "../include/etr.hpp"
using namespace etr;

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

bool check_all_same(VEC<bool>&& v) {
  bool start = v[0];

  for(int i = 1; i < v.size(); i++) {
    if(start != v[i]) {
      return false;
    }
  }

  return true;
}

TEST_CASE( "comparisons" ) {
  sexp v1 = coca(1, 2, 3);
  sexp v2 = coca(1, 1, 1);
  sexp v3 = coca(5, 5, 5);

  REQUIRE(check_all_same(v1 == v2) == false);
  REQUIRE(check_all_same(v1 != v3) == true);
  REQUIRE(check_all_same(v3 >= v2) == true);
  REQUIRE(check_all_same(v1 <= v2) == false);
  REQUIRE(check_all_same(v1 > v2) == false);
  REQUIRE(check_all_same(v1 < v3) == true);
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
  REQUIRE(eq(subset(a, coca(1, 3), coca(1,2,5,3)), res) == true);
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
  REQUIRE(eq(subset(a, 1, coca(1,1,1,1,2) == coca(1,1,1,1,1)), res) == true);

  res = coca(1, 2, 3);
  REQUIRE(eq(subset(a, true, 1), res) == true);
  REQUIRE(eq(subset(a, nullptr, 1), res) == true);

  res = coca(4, 6);
  REQUIRE(eq(subset(a, r, 2), res) == true);
  REQUIRE(eq(subset(a, coca(1, 3), 2), res) == true);

  temp1 = coca(1, 2, 3);
  temp2 = coca(1, 3, 3);
  res = coca(1, 3);
  REQUIRE(eq(subset(a, temp1 == temp2, 1), res) == true);
  REQUIRE(eq(subset(a, coca(1,2,3) == coca(1,3,3), 1), res) == true);

  REQUIRE(subset(a, 1.5, 1.5)[0] == 1);

  res = coca(1, 7);
  REQUIRE(eq(subset(a, 1.5, coca(1, 3)), res) == true);

  temp1 = coca(1, 5);
  temp2 = coca(1, 1);
  res = coca(1);
  REQUIRE(eq(subset(a, 1.5, temp1 == temp2), res) == true);
  REQUIRE(eq(subset(a, 1.5, coca(1,5) == coca(1,1)), res) == true);

  res = coca(1, 2, 3);
  REQUIRE(eq(subset(a, true, 1.5), res) == true);
  REQUIRE(eq(subset(a, nullptr, 1.5), res) == true);

  res = coca(1, 2, 2);
  REQUIRE(eq(subset(a, coca(1, 2, 2), 1.5), res) == true);

  temp1 = coca(1, 2, 3);
  temp2 = coca(1, 1, 3);
  res = coca(13, 15);
  REQUIRE(eq(subset(a, temp1 == temp2, 5.5), res) == true);
  REQUIRE(eq(subset(a, coca(1,2,3) == coca(1,1,3), 5.5), res) == true);


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

  r = coca(1, 3);
  res = coca(1, 3, 4, 6, 7, 9, 10, 12, 13, 15);
  REQUIRE(eq(subset(a, r, nullptr), res) == true);

  temp1 = coca(1, 3, 3);
  temp2 = coca(1, 2, 3);
  REQUIRE(eq(subset(a, temp1 == temp2, nullptr), res) == true);

  r = coca(1, 3, 1);
  c = coca(1, 5);
  res = coca(1, 3, 1, 13, 15, 13);
  REQUIRE(eq(subset(a, r, c), res) == true);

  temp1 = coca(1, 3, 5, 4, 5);
  temp2 = coca(1, 2, 3, 3, 5);
  REQUIRE(eq(subset(a, r, temp1 == temp2), res ) == true);

  temp1 = coca(1, 3, 5);
  temp2 = coca(1, 2, 5);
  res = coca(1, 3, 13, 15);
  REQUIRE(eq(subset(a,temp1 == temp2, c), res ) == true);


  sexp temp3 = coca(1, 2, 2, 2, 5);
  sexp temp4 = coca(1, 3, 3, 3, 5);
  REQUIRE(eq(subset(a,temp1 == temp2, temp3 == temp4), res ) == true);
}




TEST_CASE( "subassign vector" ) {
  sexp a = colon(1, 5);
  sexp t = a;
  sexp b = coca(1, 3, 5);
  sexp res;

  subassign(a, a) = colon(2, 6);
  res = colon(2, 6);
  REQUIRE(eq(a, res) == true);
  a = t;
  res = a;


  subassign(a, 1) = 100;
  res[0] = 100;
  REQUIRE(eq(a, res) == true);
  a = t;


  subassign(a, 1.5) = 100;
  res[0] = 100;
  REQUIRE(eq(a, res) == true);
  a = t;

  subassign(a, nullptr) = colon(2, 6);
  res = colon(2, 6);
  REQUIRE(eq(a, res) == true);
  a = t;

  subassign(a, true) = colon(2, 6);
  res = colon(2, 6);
  REQUIRE(eq(a, res) == true);
  a = t;


  subassign(a, b) = coca(10, 30, 50);
  res = coca(10,2, 30,4, 50);
  REQUIRE(eq(a, res) == true);
  a = t;

  subassign(a, coca(1, 3, 5)) = coca(10, 30, 50);
  res = coca(10,2, 30,4, 50);
  REQUIRE(eq(a, res) == true);
  a = t;


  subassign(a, a == b) = coca(10, 30, 50);
  res = coca(10,2, 3,4, 5);
  REQUIRE(eq(a, res) == true);
  a = t;

}


void test_subass(sexp& inp, sexp&& r, sexp&& c, sexp fill, sexp& res) {
  subassign(inp, r, c) = fill;
  REQUIRE(eq(inp, res) == true);
  inp = matrix(colon(1, 15), 3, 5);
  res = colon(1, 15);
}

void test_subass(sexp& inp, sexp& r, sexp& c, sexp fill, sexp& res) {
  subassign(inp, r, c) = fill;
  REQUIRE(eq(inp, res) == true);
  inp = matrix(colon(1, 15), 3, 5);
  res = colon(1, 15);
}


TEST_CASE( "subassign matrix" ) {
  sexp a = matrix(colon(1, 15), 3, 5);
  sexp r = coca(1, 3);
  sexp c = coca(1, 2, 5);
  sexp res;
  sexp fill = 10;
  res = colon(1, 15);
  res[0] = 10;
  res[2] = 10;
  res[3] = 10;
  res[5] = 10;
  res[12] = 10;
  res[14] = 10;
  test_subass(a, r, c, fill, res);
  res[0] = 10;
  res[2] = 10;
  res[3] = 10;
  res[5] = 10;
  res[12] = 10;
  res[14] = 10;
  test_subass(a, coca(1, 3), coca(1, 2, 5), fill, res);


  res = vector(10, 15);
  subassign(a, true, true) = vector(10, 15);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = vector(10, 15);
  subassign(a, true, nullptr) = vector(10, 15);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = vector(10, 15);
  subassign(a, nullptr, true) = vector(10, 15);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = vector(10, 15);
  subassign(a, nullptr, nullptr) = vector(10, 15);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);



  res = colon(1, 15);
  res[0] = 100;
  subassign(a, 1, 1) = 100.;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = colon(1, 15);
  res[0] = 100;
  subassign(a, 1.5, 1) = 100.;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = colon(1, 15);
  res[0] = 100;
  subassign(a, 1, 1.5) = 100.;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = colon(1, 15);
  res[0] = 100;
  subassign(a, 1.6, 1.7) = 100.;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[6] = 100;
  res[9] = 100;
  res[12] = 100;
  subassign(a, 1, true) = vector(100, 5);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[6] = 100;
  res[9] = 100;
  res[12] = 100;
  subassign(a, 1.5, true) = vector(100, 5);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[6] = 100;
  res[9] = 100;
  res[12] = 100;
  subassign(a, 1, nullptr) = vector(100, 5);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[6] = 100;
  res[9] = 100;
  res[12] = 100;
  subassign(a, 1.5, nullptr) = vector(100, 5);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[12] = 100;
  c = coca(1, 2, 5);
  subassign(a, 1, c) = vector(100, 3);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[12] = 100;
  c = coca(1, 2, 5);
  subassign(a, 1.5, c) = vector(100, 3);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);





  sexp temp1 = coca(1, 1, 1, 1, 2);
  sexp temp2 = coca(1, 1, 1, 1, 1);
  subassign(a, 1, temp1 == temp2) = vector(100, 4);
  res = colon(1, 15);
  res[0] = 100;
  res[3] = 100;
  res[6] = 100;
  res[9] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);
  subassign(a, 1, coca(1, 1, 1, 1, 2) == coca(1, 1, 1, 1, 1)) = vector(100, 4);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  subassign(a, true, 1) = vector(100, 3);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);
  subassign(a, nullptr, 1) = vector(100, 3);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  r = coca(1, 3);
  subassign(a, r, 2) = vector(100, 2);
  res = colon(1, 15);
  res[3] = 100;
  res[5] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);
  subassign(a, coca(1, 3), 2) = vector(100, 2);
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  temp1 = coca(1, 2, 3);
  temp2 = coca(1, 3, 3);
  res = colon(1, 15);
  subassign(a, temp1 == temp2, 1) = vector(100, 2);
  res[0] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);
  subassign(a, coca(1, 2, 3) == coca(1, 3, 3)) = vector(200, 2);
  res[0] = 200;
  res[2] = 200;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  subassign(a, 1.5, 1.5) = 12;
  res = colon(1, 15);
  res[0] = 12;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  res = colon(1, 15);
  subassign(a, 1.5, coca(1, 3)) = vector(200, 2);
  res[0] = 200;
  res[6] = 200;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  temp1 = coca(1, 5);
  temp2 = coca(1, 1);
  res = colon(1, 15);
  subassign(a, 1.5, temp1 == temp2) = vector(300, 1);
  res[0] = 300;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);
  subassign(a, 1.5, coca(1, 5) == coca(1, 1)) = vector(400, 1);
  res[0] = 400;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  subassign(a, true, 1.5) = vector(100, 3);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  subassign(a, nullptr, 1.5) = vector(100, 3);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  subassign(a, coca(1, 2, 3), 1.5) = vector(100, 3);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  temp1 = coca(1, 2, 3);
  temp2 = coca(1, 1, 3);
  subassign(a, temp1 == temp2, 1.5) = vector(100, 2);
  res = colon(1, 15);
  res[0] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  subassign(a, coca(1, 2, 3) == coca(1, 1, 3), 1.5) = vector(100, 6);
  res = colon(1, 15);
  res[0] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);



  c = coca(1, 2, 5);
  subassign(a, true, c) = vector(100, 9);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  res[3] = 100;
  res[4] = 100;
  res[5] = 100;
  res[12] = 100;
  res[13] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  c = coca(1, 2, 5);
  subassign(a, nullptr, c) = vector(100, 9);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  res[3] = 100;
  res[4] = 100;
  res[5] = 100;
  res[12] = 100;
  res[13] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  temp1 = coca(1, 2, 3, 4, 5);
  temp2 = coca(1, 0, 0,0, 5);
  c = coca(1, 2, 5);
  subassign(a, true, temp1 == temp2) = vector(100, 9);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  res[12] = 100;
  res[13] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  c = coca(1, 2, 5);
  subassign(a, nullptr, temp1 == temp2) = vector(100, 9);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  res[12] = 100;
  res[13] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  subassign(a, coca(2), true) = vector(100, 5);
  res = colon(1, 15);
  res[1] = 100;
  res[4] = 100;
  res[7] = 100;
  res[10] = 100;
  res[13] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  r = coca(2);
  subassign(a, r, true) = vector(100, 5);
  res = colon(1, 15);
  res[1] = 100;
  res[4] = 100;
  res[7] = 100;
  res[10] = 100;
  res[13] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  r = coca(2);
  subassign(a, r, nullptr) = vector(100, 5);
  res = colon(1, 15);
  res[1] = 100;
  res[4] = 100;
  res[7] = 100;
  res[10] = 100;
  res[13] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  temp1 = coca(1, 5);
  temp2 = coca(1, 6);
  subassign(a, true, temp1 == temp2) = vector(100, 3);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[2] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);



  temp1 = coca(1, 3, 3);
  temp2 = coca(1, 2, 3);
  subassign(a, temp1 == temp2, nullptr) = vector(100, 10);
  res = colon(1, 15);
  res[0] = 100;
  res[2] = 100;
  res[3] = 100;
  res[5] = 100;
  res[6] = 100;
  res[8] = 100;
  res[9] = 100;
  res[11] = 100;
  res[12] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  r = coca(1, 3);
  c = coca(1, 5);
  subassign(a, r, c) = vector(100, 4);
  res = colon(1, 15);
  res[0] = 100;
  res[2] = 100;
  res[12] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  r = coca(1, 3);
  temp1 = coca(1, 3, 5, 4, 5);
  temp2 = coca(1, 2, 3, 3, 5);
  subassign(a, r, temp1 == temp2) = vector(100, 4);
  res = colon(1, 15);
  res[0] = 100;
  res[2] = 100;
  res[12] = 100;
  res[14] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);


  temp1 = coca(1, 2, 6);
  temp2 = coca(1, 2, 5);
  c = coca(1, 4);
  subassign(a, temp1 == temp2, c) = vector(100, 4);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[9] = 100;
  res[10] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);

  temp1 = coca(1, 2, 6);
  temp2 = coca(1, 2, 5);
  sexp temp3 = coca(1, 2, 2, 2, 5);
  sexp temp4 = coca(1, 3, 3, 3, 5);
  subassign(a, temp1 == temp2, temp3 == temp4) = vector(100, 4);
  res = colon(1, 15);
  res[0] = 100;
  res[1] = 100;
  res[12] = 100;
  res[13] = 100;
  REQUIRE(eq(a, res) == true);
  a = matrix(colon(1, 15), 3, 5);
}



TEST_CASE( "trigo" ) {

double pi = 3.14159265359;

sexp a = coca(0, pi/6, pi/2, pi);
sexp b = sinus(a);
sexp res = coca(0, 0.5, 1, 0);
subassign(b, 1) = sinus(0);
REQUIRE(eq(b, res) == true);


a = coca(0, 0.5, 1);
b = asinus(a);
res = coca(0, pi/6, pi/2);
subassign(b, 1) = asinus(0);
REQUIRE(eq(b, res) == true);

a = coca(0, 0.5, 1);
b = sinush(a);
res = coca(0, 0.5210953, 1.175201);
subassign(b, 1) = sinush(0);
REQUIRE(eq(b, res) == true);


a = coca(0, pi/3, pi/2, pi);
b = cosinus(a);
res = coca(1, 0.5, 0, -1);
subassign(b, 1) = cosinus(0);
REQUIRE(eq(b, res) == true);

a = coca(0, 0.5, 1);
b = acosinus(a);
res = coca(pi/2, pi/3, 0);
subassign(b, 1) = acosinus(0);
REQUIRE(eq(b, res) == true);

a = coca(0, 0.5, 1);
b = cosinush(a);
res = coca(1,  1.127626, 1.543081);
subassign(b, 1) = cosinush(0);
REQUIRE(eq(b, res) == true);


a = coca(0, pi/4, pi);
b = tangens(a);
res = coca(0, 1, 0);
subassign(b, 1) = tangens(0);
REQUIRE(eq(b, res) == true);

a = coca(0,  1);
b = atangens(a);
res = coca(0, pi/4);
subassign(b, 1) = atangens(0);
REQUIRE(eq(b, res) == true);


a = coca(0,  1);
b = tangensh(a);
res = coca(0, 0.7615942);
subassign(b, 1) = tangensh(0);
REQUIRE(eq(b, res) == true);


sinus(1);
sinus(1.0);
sinush(1);
sinush(1.0);
asinus(1);
asinus(1.0);

cosinus(1);
cosinus(1.0);
cosinush(1);
cosinush(1.0);
acosinus(1);
acosinus(1.0);

tangens(1);
tangens(1.0);
tangensh(1);
tangensh(1.0);
atangens(1);
atangens(1.0);


}

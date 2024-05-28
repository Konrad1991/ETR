#define STANDALONE_ETR
#include "../include/etr.hpp"
// using namespace etr;

bool deq(double a, double b) { return std::fabs(a - b) < 1E-3; }

template <typename L, typename R> bool eq(L inp1, R inp2) {
  etr::ass(inp1.size() == inp2.size(), "Error");
  bool test = true;
  for (int i = 0; i < inp1.size(); i++) {
    if (deq(inp1[i], inp2[i]) == false) {
      test = false;
      break;
    }
  }
  return test;
}

template <typename T> bool eq(T inp1, double inp2) {
  bool test = true;
  for (int i = 0; i < inp1.size(); i++) {
    if (deq(inp1[i], inp2) == false) {
      test = false;
      break;
    }
  }

  return test;
}

bool eqb(etr::Vec<bool> inp1, etr::Vec<bool> inp2) {
  etr::ass(inp1.size() == inp2.size(), "Error");
  bool test = true;
  for (int i = 0; i < inp1.size(); i++) {
    if (inp1[i] != inp2[i]) {
      test = false;
      break;
    }
  }
  return test;
}

sexp testall(BorrowPtr a, double type_test) {
  sexp size;
  sexp temp;
  sexp ret;
  sexp m1;
  sexp m2;
  sexp b;
  sexp c;
  sexp d;
  sexp e;
  sexp f;
  sexp v;
  sexp m;
  sexp rs;
  sexp cs;
  sexp x;

  if (type_test == etr::i2d(0)) {
    ;
    size = etr::length(a);
    for (auto &i : etr::colon(etr::i2d(1), size)) {
      ;
      for (auto &j : etr::colon(etr::i2d(1), (size - etr::i2d(1)))) {
        ;
        if (etr::subset(a, j) > etr::subset(a, j + etr::i2d(1))) {
          ;
          temp = etr::subset(a, j);
          etr::subset(a, j) = etr::subset(a, j + etr::i2d(1));
          etr::subset(a, j + etr::i2d(1)) = temp;
        };
      };
    };
    return (a);
  } else if (type_test == etr::i2d(1)) {
    ;
    ret = etr::vector_numeric(etr::i2d(20));
    etr::subset(ret, 1) = etr::i2d(1);
    etr::subset(ret, 2) = etr::i2d(1);
    for (auto &i : etr::colon(etr::i2d(3), etr::length(ret))) {
      ;
      etr::subset(ret, i) =
          etr::subset(ret, i - etr::i2d(1)) + etr::subset(ret, i - etr::i2d(2));
    };
    return (ret);
  } else if (type_test == 2.1) {
    ;
    m1 = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(12)), etr::i2d(3),
                     etr::i2d(4));
    m2 = etr::matrix(etr::i2d(50), etr::i2d(3), etr::i2d(4));
    ret = m1 + m2 - etr::i2d(1);
    return (ret);
  } else if (type_test == 2.2) {
    ;
    etr::subset(a, 11) = etr::i2d(20);
  } else if (type_test == 2.3) {
    ;
    etr::subset(a, 0) = etr::i2d(20);
  } else if (type_test == 3.1) {
    ;
    a = a + etr::i2d(3);
    return (a);
  } else if (type_test == 3.2) {
    ;
    a = a + etr::rep(3.14, etr::i2d(4));
    return (a);
  } else if (type_test == 3.3) {
    ;
    a = a + etr::matrix(etr::i2d(3), etr::i2d(2), etr::i2d(2));
    return (a);
  } else if (type_test == 3.4) {
    ;
    a = etr::i2d(1);
    a = a + 3.14;
    return (a);
  } else if (type_test == 3.5) {
    ;
    a = etr::i2d(1);
    a = a + etr::rep(etr::i2d(3), etr::i2d(4));
    return (a);
  } else if (type_test == 3.6) {
    ;
    b = etr::vector_numeric(etr::i2d(2));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    a = a + b;
    return (a);
  } else if (type_test == 3.7) {
    ;
    b = etr::vector_numeric(etr::i2d(9));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    etr::subset(b, 3) = etr::i2d(300);
    etr::subset(b, 4) = etr::i2d(400);
    etr::subset(b, 5) = etr::i2d(500);
    etr::subset(b, 6) = etr::i2d(600);
    etr::subset(b, 7) = etr::i2d(700);
    etr::subset(b, 8) = etr::i2d(800);
    etr::subset(b, 9) = etr::i2d(900);
    a = a + b;
    return (a);
  } else if (type_test == 3.8) {
    ;
    a = etr::i2d(1);
    a = etr::rep(etr::i2d(3), etr::i2d(4)) + a;
    return (a);
  } else if (type_test == 3.9) {
    ;
    a = etr::i2d(1);
    a = etr::i2d(1) + etr::i2d(4);
    return (a);
  } else if (type_test == 3.1) {
    ;
    a = a + a;
    return (a);
  } else if (type_test == 3.11) {
    ;
    a = a + etr::i2d(1);
    return (a);
  } else if (type_test == 3.12) {
    ;
    a = etr::i2d(4) + a;
    return (a);
  } else if (type_test == 3.13) {
    ;
    b = etr::rep(etr::i2d(3), etr::i2d(2));
    a = a + b;
    return (a);
  };
  if (type_test == 4.1) {
    ;
    a = a - etr::i2d(3);
    return (a);
  } else if (type_test == 4.2) {
    ;
    a = a - etr::rep(3.14, etr::i2d(4));
    return (a);
  } else if (type_test == 4.3) {
    ;
    a = a - etr::matrix(etr::i2d(3), etr::i2d(2), etr::i2d(2));
    return (a);
  } else if (type_test == 4.4) {
    ;
    a = etr::i2d(1);
    a = a - 3.14;
    return (a);
  } else if (type_test == 4.5) {
    ;
    a = etr::i2d(1);
    a = a - etr::rep(etr::i2d(3), etr::i2d(4));
    return (a);
  } else if (type_test == 4.6) {
    ;
    b = etr::vector_numeric(etr::i2d(2));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    a = a - b;
    return (a);
  } else if (type_test == 4.7) {
    ;
    b = etr::vector_numeric(etr::i2d(9));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    etr::subset(b, 3) = etr::i2d(300);
    etr::subset(b, 4) = etr::i2d(400);
    etr::subset(b, 5) = etr::i2d(500);
    etr::subset(b, 6) = etr::i2d(600);
    etr::subset(b, 7) = etr::i2d(700);
    etr::subset(b, 8) = etr::i2d(800);
    etr::subset(b, 9) = etr::i2d(900);
    a = a - b;
    return (a);
  } else if (type_test == 4.8) {
    ;
    a = etr::i2d(1);
    a = etr::rep(etr::i2d(3), etr::i2d(4)) - a;
    return (a);
  } else if (type_test == 4.9) {
    ;
    a = etr::i2d(1);
    a = etr::i2d(1) - etr::i2d(4);
    return (a);
  } else if (type_test == 4.1) {
    ;
    a = a - a;
    return (a);
  } else if (type_test == 4.11) {
    ;
    a = a - etr::i2d(1);
    return (a);
  } else if (type_test == 4.12) {
    ;
    a = etr::i2d(4) - a;
    return (a);
  } else if (type_test == 4.13) {
    ;
    b = etr::rep(etr::i2d(3), etr::i2d(2));
    a = a - b;
    return (a);
  } else if (type_test == 5.1) {
    ;
    a = a / etr::i2d(3);
    return (a);
  } else if (type_test == 5.2) {
    ;
    a = a / etr::rep(3.14, etr::i2d(4));
    return (a);
  } else if (type_test == 5.3) {
    ;
    a = a / etr::matrix(etr::i2d(3), etr::i2d(2), etr::i2d(2));
    return (a);
  } else if (type_test == 5.4) {
    ;
    a = etr::i2d(1);
    a = a / 3.14;
    return (a);
  } else if (type_test == 5.5) {
    ;
    a = etr::i2d(1);
    a = a / etr::rep(etr::i2d(3), etr::i2d(4));
    return (a);
  } else if (type_test == 5.6) {
    ;
    b = etr::vector_numeric(etr::i2d(2));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    a = a / b;
    return (a);
  } else if (type_test == 5.7) {
    ;
    b = etr::vector_numeric(etr::i2d(9));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    etr::subset(b, 3) = etr::i2d(300);
    etr::subset(b, 4) = etr::i2d(400);
    etr::subset(b, 5) = etr::i2d(500);
    etr::subset(b, 6) = etr::i2d(600);
    etr::subset(b, 7) = etr::i2d(700);
    etr::subset(b, 8) = etr::i2d(800);
    etr::subset(b, 9) = etr::i2d(900);
    a = a / b;
    return (a);
  } else if (type_test == 5.8) {
    ;
    a = etr::i2d(1);
    a = etr::rep(etr::i2d(3), etr::i2d(4)) / a;
    return (a);
  } else if (type_test == 5.9) {
    ;
    a = etr::i2d(1);
    a = etr::i2d(1) / etr::i2d(4);
    return (a);
  } else if (type_test == 5.1) {
    ;
    a = a / a;
    return (a);
  } else if (type_test == 5.11) {
    ;
    a = a / etr::i2d(1);
    return (a);
  } else if (type_test == 5.12) {
    ;
    a = etr::i2d(4) / a;
    return (a);
  } else if (type_test == 5.13) {
    ;
    b = etr::rep(etr::i2d(3), etr::i2d(2));
    a = a / b;
    return (a);
  } else if (type_test == 6.1) {
    ;
    a = a * etr::i2d(3);
    return (a);
  } else if (type_test == 6.2) {
    ;
    a = a * etr::rep(3.14, etr::i2d(4));
    return (a);
  } else if (type_test == 6.3) {
    ;
    a = a * etr::matrix(etr::i2d(3), etr::i2d(2), etr::i2d(2));
    return (a);
  } else if (type_test == 6.4) {
    ;
    a = etr::i2d(1);
    a = a * 3.14;
    return (a);
  } else if (type_test == 6.5) {
    ;
    a = etr::i2d(1);
    a = a * etr::rep(etr::i2d(3), etr::i2d(4));
    return (a);
  } else if (type_test == 6.6) {
    ;
    b = etr::vector_numeric(etr::i2d(2));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    a = a * b;
    return (a);
  } else if (type_test == 6.7) {
    ;
    b = etr::vector_numeric(etr::i2d(9));
    etr::subset(b, 1) = etr::i2d(100);
    etr::subset(b, 2) = etr::i2d(200);
    etr::subset(b, 3) = etr::i2d(300);
    etr::subset(b, 4) = etr::i2d(400);
    etr::subset(b, 5) = etr::i2d(500);
    etr::subset(b, 6) = etr::i2d(600);
    etr::subset(b, 7) = etr::i2d(700);
    etr::subset(b, 8) = etr::i2d(800);
    etr::subset(b, 9) = etr::i2d(900);
    a = a * b;
    return (a);
  } else if (type_test == 6.8) {
    ;
    a = etr::i2d(1);
    a = etr::rep(etr::i2d(3), etr::i2d(4)) * a;
    return (a);
  } else if (type_test == 6.9) {
    ;
    a = etr::i2d(1);
    a = etr::i2d(1) * etr::i2d(4);
    return (a);
  } else if (type_test == 6.1) {
    ;
    a = a * a;
    return (a);
  } else if (type_test == 6.11) {
    ;
    a = a * etr::i2d(1);
    return (a);
  } else if (type_test == 6.12) {
    ;
    a = etr::i2d(4) * a;
    return (a);
  } else if (type_test == 6.13) {
    ;
    b = etr::rep(etr::i2d(3), etr::i2d(2));
    a = a * b;
    return (a);
  };
  if (type_test == 7.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    c = etr::coca(-etr::i2d(100), a, b, etr::i2d(100));
    d = etr::rep(etr::i2d(1), etr::i2d(2));
    e = etr::matrix(-etr::i2d(1), etr::i2d(2), etr::i2d(2));
    f = etr::coca(c, d, e, etr::i2d(2));
    return (f);
  } else if (type_test == 7.2) {
    ;
    v = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    m = etr::matrix(etr::i2d(2), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::length(v), etr::dim(m));
    return (b);
  } else if (type_test == 8.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a == b);
  } else if (type_test == 8.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    return (a == a);
  } else if (type_test == 8.3) {
    ;
    a = etr::coca(etr::i2d(2), etr::i2d(2), etr::i2d(2));
    return (a == etr::i2d(2));
  } else if (type_test == 9.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(2));
    return (a <= b);
  } else if (type_test == 9.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(4));
    return (a <= a);
  } else if (type_test == 9.3) {
    ;
    a = etr::coca(etr::i2d(2), etr::i2d(2), etr::i2d(2));
    return (a <= etr::i2d(2));
  } else if (type_test == 10.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a < b);
  } else if (type_test == 10.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    return (a < a);
  } else if (type_test == 10.3) {
    ;
    a = etr::coca(etr::i2d(2), etr::i2d(2), etr::i2d(2));
    return (a < etr::i2d(2));
  } else if (type_test == 11.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a > b);
  } else if (type_test == 11.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    return (a > a);
  } else if (type_test == 11.3) {
    ;
    a = etr::coca(etr::i2d(2), etr::i2d(2), etr::i2d(2));
    return (a > etr::i2d(1));
  } else if (type_test == 12.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(3));
    return (a >= b);
  } else if (type_test == 12.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    return (a >= a);
  } else if (type_test == 12.3) {
    ;
    a = etr::coca(etr::i2d(2), etr::i2d(2), etr::i2d(2));
    return (a >= etr::i2d(1));
  } else if (type_test == 13.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(3));
    return (a != b);
  } else if (type_test == 13.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    return (a != a);
  } else if (type_test == 13.3) {
    ;
    a = etr::coca(etr::i2d(2), etr::i2d(2), etr::i2d(2));
    return (a != etr::i2d(1));
  } else if (type_test == 14.1) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b == b - a);
  } else if (type_test == 14.2) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b == etr::coca(etr::i2d(100), etr::i2d(100), etr::i2d(200)));
  } else if (type_test == 14.3) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b != b - a);
  } else if (type_test == 14.4) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b != etr::coca(etr::i2d(100), etr::i2d(100), etr::i2d(200)));
  } else if (type_test == 14.5) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b > b - a);
  } else if (type_test == 14.6) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b < etr::coca(etr::i2d(100), etr::i2d(100), etr::i2d(200)));
  } else if (type_test == 14.7) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b >= b - a);
  } else if (type_test == 14.8) {
    ;
    a = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3));
    b = etr::coca(etr::i2d(5), etr::i2d(6), etr::i2d(7));
    return (a + b <= etr::coca(etr::i2d(100), etr::i2d(100), etr::i2d(200)));
  };
  if (type_test == 15.1) {
    ;
    a = a ^ etr::i2d(2) + etr::ln(etr::i2d(1));
    return (a);
  } else if (type_test == 15.2) {
    ;
    a = a ^ etr::i2d(3);
    return (a);
  } else if (type_test == 15.3) {
    ;
    a = etr::exp(a) + etr::i2d(1);
    return (a);
  } else if (type_test == 15.4) {
    ;
    a = sqroot(a);
    return (a);
  };
  if (type_test == 16.1) {
    ;
    for (auto &i : etr::colon(etr::i2d(1), etr::length(a))) {
      ;
      etr::subset(a, i) = etr::i2d(100);
    };
    return (a);
  } else if (type_test == 16.2) {
    ;
    etr::subset(a, true) = etr::i2d(0);
    return (a);
  } else if (type_test == 16.3) {
    ;
    etr::subset(a, 1) = etr::i2d(0);
    etr::subset(a, 2.3) = etr::i2d(0);
    return (a);
  } else if (type_test == 16.4) {
    ;
    etr::subset(a, true) = etr::i2d(0);
    return (a);
  } else if (type_test == 16.5) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4),
                  etr::i2d(1));
    etr::subset(a, b) = etr::colon(etr::i2d(1), etr::i2d(5));
    return (a);
  } else if (type_test == 16.6) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, 4, 4) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.7) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, 4, 4.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.8) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, 4, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.9) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, 4, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.11) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, 4, etr::coca(etr::i2d(1), etr::i2d(4))) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.12) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(4)), etr::i2d(2),
                    etr::i2d(2));
    etr::subset(a, 1.3, 1) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.13) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(4)), etr::i2d(2),
                    etr::i2d(2));
    etr::subset(a, true, 1) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.14) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(4)), etr::i2d(2),
                    etr::i2d(2));
    etr::subset(a, true, 1) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.15) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(6)), etr::i2d(3),
                    etr::i2d(2));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    etr::subset(a, b, 1) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.16) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(6)), etr::i2d(3),
                    etr::i2d(2));
    etr::subset(a, 1.5, 1.1) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.17) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(6)), etr::i2d(3),
                    etr::i2d(2));
    etr::subset(a, 1.5, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.18) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(6)), etr::i2d(3),
                    etr::i2d(2));
    etr::subset(a, 1.5, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.19) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    etr::subset(a, 1.5, b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.21) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    etr::subset(a, true, 1.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.22) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    etr::subset(a, true, 1.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.23) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b, 1.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.24) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    etr::subset(a, true, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.25) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    etr::subset(a, true, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.26) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(2), etr::i2d(3));
    etr::subset(a, true, b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.27) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    etr::subset(a, true, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.28) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.29) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    etr::subset(a, true, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.31) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, true, b) = etr::i2d(20);
    return (a);
  };
  if (type_test == 16.32) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    etr::subset(a, b, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.33) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    c = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b, c) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.34) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, c + c) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.35) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, a < etr::i2d(5)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.36) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, 1, c + c) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.37) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, 1, b >= etr::i2d(3)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.38) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b + b, 1) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.39) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, b > etr::i2d(3), 4) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.41) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, 3.5, b + b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.42) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, 3.5, b <= etr::i2d(1)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.43) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b + b, 1.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.44) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, b >= etr::i2d(1), 1.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.45) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, true, b + b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.46) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, true, b >= etr::i2d(3)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.47) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b + b, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.48) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, b == etr::i2d(1), true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.49) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, true, b + b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.51) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, true, b >= etr::i2d(3)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.52) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b + b, true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.53) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    etr::subset(a, b == etr::i2d(1), true) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.54) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    etr::subset(a, b + b, b + b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.55) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    c = etr::coca(etr::i2d(2), etr::i2d(4));
    etr::subset(a, b + b, c) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.56) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    c = etr::coca(etr::i2d(2), etr::i2d(4));
    etr::subset(a, c, b + b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.57) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, b + b, c == etr::i2d(2)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.58) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(2), etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, b, c == etr::i2d(2)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.59) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, c == etr::i2d(2), b + b) = etr::i2d(20);
    return (a);
  };
  if (type_test == 16.61) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(2), etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, c == etr::i2d(2), b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.62) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, c == etr::i2d(2), c == etr::i2d(2)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.63) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(2), etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, b, c == etr::i2d(2)) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.64) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    b = etr::coca(etr::i2d(2), etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(2));
    etr::subset(a, c == etr::i2d(2), b) = etr::i2d(20);
    return (a);
  } else if (type_test == 16.65) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::coca(etr::i2d(4), etr::i2d(4));
    etr::subset(b, 1) = etr::at(a, 2);
    etr::subset(b, 2) = etr::at(a, 2);
    return (b);
  } else if (type_test == 16.66) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::subset(a, true);
    c = etr::subset(b, true);
    return (c);
  } else if (type_test == 16.67) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::coca(etr::i2d(1), etr::i2d(5));
    b = etr::subset(a, b);
    return (b);
  } else if (type_test == 16.68) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1, true);
    c = etr::subset(a, 1, true);
    return (b - c);
  } else if (type_test == 16.69) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset(a, 1, b);
    return (b);
  } else if (type_test == 16.71) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1.1, 2);
    return (b);
  } else if (type_test == 16.72) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, 2);
    return (b);
  } else if (type_test == 16.73) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, 2);
    return (b);
  } else if (type_test == 16.74) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset(a, b, 2);
    return (b);
  } else if (type_test == 16.75) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1.1, 2.2);
    return (b);
  } else if (type_test == 16.76) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1.1, true);
    return (b);
  } else if (type_test == 16.77) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1.1, true);
    return (b);
  } else if (type_test == 16.78) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset(a, 1.1, b);
    return (b);
  } else if (type_test == 16.79) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, 2.1);
    return (b);
  } else if (type_test == 16.81) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, 2.1);
    return (b);
  } else if (type_test == 16.82) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset(a, b, 2.5);
    return (b);
  } else if (type_test == 16.83) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, true);
    return (b);
  } else if (type_test == 16.84) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, true);
    return (b);
  } else if (type_test == 16.85) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, true, b);
    return (b);
  } else if (type_test == 16.86) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, true);
    return (b);
  } else if (type_test == 16.87) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, b, true);
    return (b);
  } else if (type_test == 16.88) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, true);
    return (b);
  } else if (type_test == 16.89) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, true, b);
    return (b);
  } else if (type_test == 16.91) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, b, true);
    return (b);
  } else if (type_test == 16.92) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, b, b);
    return (b);
  } else if (type_test == 16.93) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, b + b);
    return (b);
  } else if (type_test == 16.94) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(5), etr::i2d(3), 6.7);
    b = etr::subset(a, b == c);
    return (b);
  } else if (type_test == 16.95) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, 1, b + c);
    return (b);
  } else if (type_test == 16.96) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, 1, b != c);
    return (b);
  } else if (type_test == 16.97) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b + c, 1);
    return (b);
  } else if (type_test == 16.98) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b != c, 2);
    return (b);
  } else if (type_test == 16.99) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, 1.5, b + c);
    return (b);
  };
  if (type_test == 17.1) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, 1.4, b != c);
    return (b);
  } else if (type_test == 17.2) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b + c, 1.5);
    return (b);
  } else if (type_test == 17.3) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b != c, 2.5);
    return (b);
  } else if (type_test == 17.4) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, true, b + c);
    return (b);
  } else if (type_test == 17.5) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1), etr::i2d(2), etr::i2d(3));
    c = etr::coca(etr::i2d(1), etr::i2d(1), etr::i2d(2), etr::i2d(5));
    b = etr::subset(a, true, b == c);
    return (b);
  } else if (type_test == 17.6) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b + c, true);
    return (b);
  } else if (type_test == 17.7) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b == c, true);
    return (b);
  } else if (type_test == 17.8) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, true, b + c);
    return (b);
  } else if (type_test == 17.9) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1), etr::i2d(2), etr::i2d(3));
    c = etr::coca(etr::i2d(1), etr::i2d(1), etr::i2d(2), etr::i2d(5));
    b = etr::subset(a, true, b == c);
    return (b);
  } else if (type_test == 17.11) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b + c, true);
    return (b);
  } else if (type_test == 17.12) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b == c, true);
    return (b);
  } else if (type_test == 17.13) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b + c, b + c);
    return (b);
  } else if (type_test == 17.14) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    rs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, rs, b + c);
    return (b);
  } else if (type_test == 17.15) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    cs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, b + c, cs);
    return (b);
  } else if (type_test == 17.16) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b + c, b == c);
    return (b);
  } else if (type_test == 17.17) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    rs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, rs, b == c);
    return (b);
  } else if (type_test == 17.18) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b == c, b + c);
    return (b);
  } else if (type_test == 17.19) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    cs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, b == c, cs);
    return (b);
  } else if (type_test == 17.21) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b == c, b == c);
    return (b);
  } else if (type_test == 17.22) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(5)));
    return (b);
  } else if (type_test == 17.23) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1, etr::coca(etr::i2d(1), etr::i2d(3)));
    return (b);
  } else if (type_test == 17.24) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(3)), 2);
    return (b);
  } else if (type_test == 17.25) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1.1, etr::coca(etr::i2d(1), etr::i2d(3)));
    return (b);
  } else if (type_test == 17.26) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(3)), 2.5);
    return (b);
  } else if (type_test == 17.27) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.28) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), true);
    return (b);
  } else if (type_test == 17.29) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  };
  if (type_test == 17.31) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), true);
    return (b);
  } else if (type_test == 17.32) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)),
                    etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.33) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(6));
    b = etr::subset(a, etr::coca(etr::i2d(2), etr::i2d(4)));
    return (b);
  } else if (type_test == 17.34) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.35) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), 1);
    return (b);
  } else if (type_test == 17.36) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, 1.5, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.37) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), 1.5);
    return (b);
  } else if (type_test == 17.38) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.39) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), true);
    return (b);
  } else if (type_test == 17.41) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, true, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.42) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), true);
    return (b);
  } else if (type_test == 17.43) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)),
                    etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.44) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    rs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, rs, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  } else if (type_test == 17.45) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    cs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), cs);
    return (b);
  } else if (type_test == 17.46) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), b == c);
    return (b);
  } else if (type_test == 17.47) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                    etr::i2d(3));
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset(a, b == c, etr::coca(etr::i2d(1), etr::i2d(2)));
    return (b);
  };
  if (type_test == 18.1) {
    ;
    etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4),
                             etr::i2d(1))) =
        etr::colon(etr::i2d(1), etr::i2d(5));
    return (a);
  } else if (type_test == 18.2) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, 4, etr::coca(etr::i2d(1), etr::i2d(4))) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.3) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(6)), etr::i2d(3),
                    etr::i2d(2));
    etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(3)), 1) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.4) {
    ;
    etr::subset(a, 1.5, etr::coca(etr::i2d(1), etr::i2d(3))) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.5) {
    ;
    etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), 1.5) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.6) {
    ;
    etr::subset(a, true, etr::coca(etr::i2d(2), etr::i2d(3))) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.7) {
    ;
    etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(2)), true) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.8) {
    ;
    etr::subset(a, true, etr::coca(etr::i2d(1), etr::i2d(2))) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.9) {
    ;
    etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(3)), true) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.91) {
    ;
    etr::subset(a, etr::coca(etr::i2d(1), etr::i2d(3)),
                etr::coca(etr::i2d(1), etr::i2d(2))) = etr::i2d(20);
    return (a);
  } else if (type_test == 18.92) {
    ;
    a = etr::matrix(etr::colon(etr::i2d(1), etr::i2d(16)), etr::i2d(4),
                    etr::i2d(4));
    etr::subset(a, etr::coca(etr::i2d(2), etr::i2d(4))) = etr::i2d(20);
    return (a);
  } else if (type_test == 19.1) {
    ;
    b = etr::at((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(0)), 2);
    return (b);
  } else if (type_test == 19.11) {
    ;
    b = etr::subset((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(0)), 3.5);
    return (b);
  } else if (type_test == 19.12) {
    ;
    b = etr::subset((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(0)), true);
    return (b);
  } else if (type_test == 19.13) {
    ;
    b = etr::subset((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(0)), true);
    return (b);
  } else if (type_test == 19.14) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(5));
    b = etr::subset((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(0)), b);
    return (b);
  } else if (type_test == 19.15) {
    ;
    b = etr::at((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                             etr::i2d(3)) +
                 etr::i2d(0)),
                1, 2);
    return (b);
  } else if (type_test == 19.16) {
    ;
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1, true);
    return (b);
  } else if (type_test == 19.17) {
    ;
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1, true);
    return (b);
  } else if (type_test == 19.18) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1, b);
    return (b);
  } else if (type_test == 19.19) {
    ;
    b = etr::at((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)), etr::i2d(3),
                             etr::i2d(3)) +
                 etr::i2d(0)),
                1, 2);
    return (b);
  } else if (type_test == 19.21) {
    ;
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    true, 2);
    return (b);
  } else if (type_test == 19.22) {
    ;
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    true, 2);
    return (b);
  } else if (type_test == 19.23) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b, 2);
    return (b);
  } else if (type_test == 19.24) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    1.1, 2.3);
    return (b);
  } else if (type_test == 19.25) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    1.1, true);
    return (b);
  } else if (type_test == 19.26) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    1.1, true);
    return (b);
  } else if (type_test == 19.27) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    1.1, b);
    return (b);
  } else if (type_test == 19.28) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, 2.1);
    return (b);
  } else if (type_test == 19.29) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, 2.1);
    return (b);
  } else if (type_test == 19.31) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(3));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    b, 2.5);
    return (b);
  };
  if (type_test == 19.32) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, true);
    return (b);
  } else if (type_test == 19.33) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, true);
    return (b);
  } else if (type_test == 19.34) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, b);
    return (b);
  } else if (type_test == 19.35) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, true);
    return (b);
  } else if (type_test == 19.36) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    b, true);
    return (b);
  } else if (type_test == 19.37) {
    ;
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, true);
    return (b);
  } else if (type_test == 19.38) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    true, b);
    return (b);
  } else if (type_test == 19.39) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    b, true);
    return (b);
  } else if (type_test == 19.41) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::colon(etr::i2d(1), etr::i2d(9)),
                                 etr::i2d(3), etr::i2d(3)) +
                     etr::i2d(0)),
                    b, b);
    return (b);
  } else if (type_test == 19.42) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(1)),
                    b + b);
    return (b);
  } else if (type_test == 19.43) {
    ;
    b = etr::coca(etr::i2d(1), etr::i2d(2), etr::i2d(3), etr::i2d(4));
    c = etr::coca(etr::i2d(1), etr::i2d(5), etr::i2d(3), 6.7);
    b = etr::subset((etr::colon(etr::i2d(1), etr::i2d(6)) + etr::i2d(0)),
                    b == c);
    return (b);
  } else if (type_test == 19.44) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1, b + c);
    return (b);
  } else if (type_test == 19.45) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1, b != c);
    return (b);
  } else if (type_test == 19.46) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, 1);
    return (b);
  } else if (type_test == 19.47) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b != c, 2);
    return (b);
  } else if (type_test == 19.48) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1.5, b + c);
    return (b);
  } else if (type_test == 19.49) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    1.4, b != c);
    return (b);
  } else if (type_test == 19.51) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, 1.5);
    return (b);
  } else if (type_test == 19.52) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b != c, 2.5);
    return (b);
  } else if (type_test == 19.53) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    true, b + c);
    return (b);
  } else if (type_test == 19.54) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1), etr::i2d(2), etr::i2d(3));
    c = etr::coca(etr::i2d(1), etr::i2d(1), etr::i2d(2), etr::i2d(5));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    true, b == c);
    return (b);
  } else if (type_test == 19.55) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, true);
    return (b);
  } else if (type_test == 19.56) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b == c, true);
    return (b);
  } else if (type_test == 19.57) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    true, b + c);
    return (b);
  } else if (type_test == 19.58) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1), etr::i2d(2), etr::i2d(3));
    c = etr::coca(etr::i2d(1), etr::i2d(1), etr::i2d(2), etr::i2d(5));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    true, b == c);
    return (b);
  } else if (type_test == 19.59) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, true);
    return (b);
  } else if (type_test == 19.61) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b == c, true);
    return (b);
  } else if (type_test == 19.62) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, b + c);
    return (b);
  } else if (type_test == 19.63) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    rs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    rs, b + c);
    return (b);
  } else if (type_test == 19.64) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    cs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, cs);
    return (b);
  } else if (type_test == 19.65) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b + c, b == c);
    return (b);
  } else if (type_test == 19.66) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    rs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    rs, b == c);
    return (b);
  } else if (type_test == 19.67) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b == c, b + c);
    return (b);
  } else if (type_test == 19.68) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    cs = etr::coca(etr::i2d(1), etr::i2d(2));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b == c, cs);
    return (b);
  } else if (type_test == 19.69) {
    ;
    b = etr::coca(etr::i2d(0), etr::i2d(1));
    c = etr::coca(etr::i2d(1), etr::i2d(1));
    b = etr::subset((etr::matrix(etr::i2d(0), etr::i2d(3), etr::i2d(3)) +
                     etr::colon(etr::i2d(1), etr::i2d(9))),
                    b == c, b == c);
    return (b);
  } else if (type_test == 20.1) {
    ;
    for (auto &i : etr::colon(etr::i2d(1), etr::at(etr::dim(a), 1))) {
      ;
      for (auto &j : etr::colon(etr::i2d(1), etr::at(etr::dim(a), 2))) {
        ;
        etr::subset(a, i, j) = i + j;
      };
    };
    return (a);
  };
  if (type_test == 21.1) {
    ;
    a = etr::coca(etr::i2d(0), 0.2, 0.4, 0.99);
    b = etr::sinus(a) + etr::asinus(a) + etr::sinush(a) + etr::cosinus(a) +
        etr::acosinus(a) + etr::cosinush(a) + etr::tangens(a) +
        etr::atangens(a) + etr::tangensh(a);
    return (b);
  } else if (type_test == 22.1) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(3));
    etr::subset(a, 1) = etr::NA;
    etr::subset(a, 2) = etr::Inf;
    etr::subset(a, 3) = -etr::Inf;
    return (a);
  } else if (type_test == 22.2) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(3));
    etr::subset(a, 1) = etr::NA;
    etr::subset(a, 2) = etr::Inf;
    etr::subset(a, 3) = -etr::Inf;
    b = etr::isNA(a);
    return (b);
  } else if (type_test == 22.3) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(3));
    etr::subset(a, 1) = etr::NA;
    etr::subset(a, 2) = etr::Inf;
    etr::subset(a, 3) = -etr::Inf;
    b = etr::isInf(a);
    return (b);
  } else if (type_test == 22.4) {
    ;
    a = etr::colon(etr::i2d(1), etr::i2d(3));
    b = etr::isInf(a + etr::i2d(1));
    c = etr::isNA(a + etr::i2d(2));
    d = b + c;
    return (d);
  }
  return (ret);
}

int main() {
  int size = 100;
  double *ptr = new double[size];
  BorrowPtr bp(ptr, size);
  testall(bp, 1.0);
  delete[] ptr;
}

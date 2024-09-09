#include "../calculation.h"

#include <gtest/gtest.h>

#define LIMIT 1e-7

/* SIMPLE ARITHMETIC OPERATIONS */

TEST(calculate, simple_1) {
  s21::Calculation calc;
  std::string str = "3+5";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 8);
}

TEST(calculate, simple_2) {
  s21::Calculation calc;
  std::string str = "10-2";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 8);
}

TEST(calculate, simple_3) {
  s21::Calculation calc;
  std::string str = "4*7";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 28);
}

TEST(calculate, simple_4) {
  s21::Calculation calc;
  std::string str = "20/4";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 5);
}

TEST(calculate, simple_5) {
  s21::Calculation calc;
  std::string str = "20/3";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 6.6666666, LIMIT);
}

TEST(calculate, simple_6) {
  s21::Calculation calc;
  std::string str = "15%4";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 3);
}

TEST(calculate, simple_7) {
  s21::Calculation calc;
  std::string str = "2+(-5+1)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, -2);
}

TEST(calculate, simple_8) {
  s21::Calculation calc;
  std::string str = "-(-5+1)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 4);
}

TEST(calculate, simple_9) {
  s21::Calculation calc;
  std::string str = "(-(-5+1)*3)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 12);
}

TEST(calculate, simple_10) {
  s21::Calculation calc;
  std::string str = "6/(7-7)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_TRUE(std::isinf(result));
}

TEST(calculate, simple_11) {
  s21::Calculation calc;
  std::string str = "(((+2+2)*2))";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 8);
}

TEST(calculate, simple_12) {
  s21::Calculation calc;
  std::string str = "(2+3/4)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 2.75, LIMIT);
}

TEST(calculate, simple_13) {
  s21::Calculation calc;
  std::string str = "0-5-5";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, -10);
}

/* ARITHMETIC OPERATIONS WITH X VARIABLE */

TEST(calculate, x_var_1) {
  s21::Calculation calc;
  std::string str = "x+2.5*(3-11.0001)";
  long double x = 0.123456;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, -19.876794, LIMIT);
}

TEST(calculate, x_var_2) {
  s21::Calculation calc;
  std::string str = "(x-5.00005)/2+3.2*x";
  long double x = 500.01;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 1847.536975, LIMIT);
}

TEST(calculate, x_var_3) {
  s21::Calculation calc;
  std::string str = "x*(2.5+3.5)-4.0000001";
  long double x = -1005876;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, -6035260, LIMIT);
}

TEST(calculate, x_var_4) {
  s21::Calculation calc;
  std::string str = "7/x";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_TRUE(std::isinf(result));
}

TEST(calculate, x_var_5) {
  s21::Calculation calc;
  std::string str = "x%(7-7)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_TRUE(std::isnan(result));
}

/* POW AND SQRT */

TEST(calculate, pow_sqrt_1) {
  s21::Calculation calc;
  std::string str = "2^3+r(16)";
  long double x = -1005876;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 12);
}

TEST(calculate, pow_sqrt_2) {
  s21::Calculation calc;
  std::string str = "r(x^2+4.5)";
  long double x = -1.5;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 2.5980762, LIMIT);
}

TEST(calculate, pow_sqrt_3) {
  s21::Calculation calc;
  std::string str = "(2+3)^2";
  long double x = -1.5;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 25);
}

TEST(calculate, pow_sqrt_4) {
  s21::Calculation calc;
  std::string str = "2^(2^3))";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 256);
}

TEST(calculate, pow_sqrt_5) {
  s21::Calculation calc;
  std::string str = "2^(2)^(3)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 64);
}

TEST(calculate, pow_sqrt_6) {
  s21::Calculation calc;
  std::string str = "r(-5)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_TRUE(std::isnan(result));
}

/* TRIGONOMETRY FUNCTIONS */

TEST(calculate, trigonometry_1) {
  s21::Calculation calc;
  std::string str = "s(x)+c(x)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 1);
}

TEST(calculate, trigonometry_2) {
  s21::Calculation calc;
  std::string str = "t(3.14/4)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 0.9992039, LIMIT);
}

TEST(calculate, trigonometry_3) {
  s21::Calculation calc;
  std::string str = "S(0.5)+C(0.5)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 1.5707963, LIMIT);
}

TEST(calculate, trigonometry_4) {
  s21::Calculation calc;
  std::string str = "c(1)+x/2";
  long double x = 6;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 3.5403023, LIMIT);
}

TEST(calculate, trigonometry_5) {
  s21::Calculation calc;
  std::string str = "-1+3*2-2+c(0)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 4);
}

TEST(calculate, trigonometry_6) {
  s21::Calculation calc;
  std::string str = "s(45)+c(30)*t(60)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 0.9002702, LIMIT);
}

TEST(calculate, trigonometry_7) {
  s21::Calculation calc;
  std::string str = "T(2345)+1";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 2.5703698, LIMIT);
}

/* LOGARITHMIC FUNCTIONS */

TEST(calculate, log_1) {
  s21::Calculation calc;
  std::string str = "l(1)+L(100)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 2);
}

TEST(calculate, log_2) {
  s21::Calculation calc;
  std::string str = "L(l(10))";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 0.3622156, LIMIT);
}

TEST(calculate, log_3) {
  s21::Calculation calc;
  std::string str = "L(x^(2)+1)";
  long double x = 3;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 1);
}

/* SCIENTIFIC NOTATION */

TEST(calculate, sci_notation_1) {
  s21::Calculation calc;
  std::string str = "1.5e2+3.2e-1";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 150.32, LIMIT);
}

TEST(calculate, sci_notation_2) {
  s21::Calculation calc;
  std::string str = "(2.5e3-1.5e2)/(5e1+2)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 45.1923076, LIMIT);
}

/* MIXED OPERATIONS */

TEST(calculate, mixed_1) {
  s21::Calculation calc;
  std::string str = "3.5+4*s(3.14/2)-5/2";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 4.9999987, LIMIT);
}

TEST(calculate, mixed_2) {
  s21::Calculation calc;
  std::string str = "x^2+(3.5+4.0005)*r(9)/3";
  long double x = -3.0002;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, 16.5017000, LIMIT);
}

TEST(calculate, mixed_3) {
  s21::Calculation calc;
  std::string str = "2*(3.5+x)-5%3";
  long double x = 10000;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_EQ(result, 20005);
}

TEST(calculate, mixed_4) {
  s21::Calculation calc;
  std::string str = "((3+5)*(7-2))/4^(2)+s(60)-L(100)*2^(3)+C(0.5)-T(1)";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_NEAR(result, -13.5430112, LIMIT);
}

TEST(calculate, mixed_5) {
  s21::Calculation calc;
  std::string str = "100^(100^(100))";
  long double x = 0;
  calc.Parse(str, x);
  long double result = calc.GetResult();
  EXPECT_TRUE(std::isinf(result));
}
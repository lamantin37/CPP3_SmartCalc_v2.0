#include <gtest/gtest.h>

#include "s21_smartcalc.h"

TEST(CalculatorTest, BasicOperations1) {
  s21::Calculator calc;

  calc.setExpression("2 + 2");
  EXPECT_EQ(calc.eval(), 4);
}

TEST(CalculatorTest, BasicOperations2) {
  s21::Calculator calc;
  calc.setExpression("5 - 3");
  EXPECT_EQ(calc.eval(), 2);
}

TEST(CalculatorTest, BasicOperations3) {
  s21::Calculator calc;
  calc.setExpression("4 * 2");
  EXPECT_EQ(calc.eval(), 8);
}

TEST(CalculatorTest, BasicOperations4) {
  s21::Calculator calc;
  calc.setExpression("8 / 4");
  EXPECT_EQ(calc.eval(), 2);
}

TEST(CalculatorTest, BasicOperations5) {
  s21::Calculator calc;
  calc.setExpression("2 ^ 3");
  EXPECT_EQ(calc.eval(), 8);
}

TEST(CalculatorTest, ModuloOperation6) {
  s21::Calculator calc;
  calc.setExpression("10 mod 3");
  EXPECT_EQ(calc.eval(), 1);
}

TEST(CalculatorTest, ModuloOperation7) {
  s21::Calculator calc;
  calc.setExpression("15 mod 4");
  EXPECT_EQ(calc.eval(), 3);
}

TEST(CalculatorTest, TrigonometricFunctions8) {
  s21::Calculator calc;
  calc.setExpression("cos(0)");
  EXPECT_EQ(calc.eval(), 1);
}

TEST(CalculatorTest, TrigonometricFunctions9) {
  s21::Calculator calc;
  calc.setExpression("tan(0)");
  EXPECT_EQ(calc.eval(), 0);
}

TEST(CalculatorTest, TrigonometricFunctions10) {
  s21::Calculator calc;
  calc.setExpression("sin(0)");
  EXPECT_EQ(calc.eval(), 0);
}

TEST(CalculatorTest, TrigonometricFunctions11) {
  s21::Calculator calc;
  calc.setExpression("acos(1)");
  EXPECT_EQ(calc.eval(), 0);
}

TEST(CalculatorTest, TrigonometricFunctions12) {
  s21::Calculator calc;
  calc.setExpression("asin(0)");
  EXPECT_EQ(calc.eval(), 0);
}

TEST(CalculatorTest, TrigonometricFunctions13) {
  s21::Calculator calc;
  calc.setExpression("atan(0)");
  EXPECT_EQ(calc.eval(), 0);
}

TEST(CalculatorTest, ExponentialAndLogarithmicFunctions14) {
  s21::Calculator calc;
  calc.setExpression("sqrt(4)");
  EXPECT_EQ(calc.eval(), 2);
}

TEST(CalculatorTest, ExponentialAndLogarithmicFunctions15) {
  s21::Calculator calc;
  calc.setExpression("ln(1)");
  EXPECT_EQ(calc.eval(), 0);
}

TEST(CalculatorTest, ExponentialAndLogarithmicFunctions16) {
  s21::Calculator calc;
  calc.setExpression("log(10)");
  EXPECT_EQ(calc.eval(), 1);
}

TEST(CalculatorTest, Parentheses17) {
  s21::Calculator calc;
  calc.setExpression("(2 + 3) * 2");
  EXPECT_EQ(calc.eval(), 10);
}

TEST(CalculatorTest, Parentheses18) {
  s21::Calculator calc;
  calc.setExpression("2 * (3 + 4)");
  EXPECT_EQ(calc.eval(), 14);
}

TEST(CalculatorTest, Parentheses19) {
  s21::Calculator calc;
  calc.setExpression("(2 + 3) * (4 - 1)");
  EXPECT_EQ(calc.eval(), 15);
}

TEST(CalculatorTest, ComplexExpressions20) {
  s21::Calculator calc;
  calc.setExpression("3 + 4 * (2 - 1) / (1 + 1) ^ 2");
  EXPECT_DOUBLE_EQ(calc.eval(), 4);
}

TEST(CalculatorTest, ComplexExpressions22) {
  s21::Calculator calc;
  calc.setExpression("log(log(log(123456789)))");
  EXPECT_DOUBLE_EQ(calc.eval(), -0.041899878188837392);
}

TEST(CalculatorTest, ComplexExpressions23) {
  s21::Calculator calc;
  calc.setExpression("2^3^4");
  EXPECT_DOUBLE_EQ(calc.eval(), 2.4178516392292583e+24);
}

TEST(CalculatorTest, ComplexExpressions24) {
  s21::Calculator calc;
  calc.setExpression("2^(sin(12)*cos(3*(sqrt(16)^2)))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.268817096931564);
}

TEST(CalculatorTest, ComplexExpressions25) {
  s21::Calculator calc;
  calc.setExpression(
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+"
      "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2");
  EXPECT_DOUBLE_EQ(calc.eval(), 2192);
}

TEST(CalculatorTest, ComplexExpressions26) {
  s21::Calculator calc;
  calc.setExpression("ln(2*(2^(atan(sqrt(10/(acos(0.0000001)))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.5203874212153758);
}

TEST(CalculatorTest, ComplexExpressions27) {
  s21::Calculator calc;
  calc.setExpression("tan(1.5 * ln(3) - cos(0.7 + sqrt(25 / asin(0.5))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 6.0218701361445346);
}

TEST(CalculatorTest, ComplexExpressions28) {
  s21::Calculator calc;
  calc.setExpression("acos(0.7 / atan(0.3)) + asin(sin(0.4) * cos(0.5))");
  EXPECT_TRUE(std::isnan(calc.eval()));
}

TEST(CalculatorTest, ComplexExpressions29) {
  s21::Calculator calc;
  calc.setExpression("cos(2.5 + sin(1.2 * tan(0.8 / sqrt(9))))");
  EXPECT_DOUBLE_EQ(calc.eval(), -0.94935339061349433);
}

TEST(CalculatorTest, ComplexExpressions30) {
  s21::Calculator calc;
  calc.setExpression("log(10000) - cos(sin(tan(0.4 + 3.2^2)) * asin(0.5))");
  EXPECT_DOUBLE_EQ(calc.eval(), 3.0256924506975276);
}

TEST(CalculatorTest, ComplexExpressions31) {
  s21::Calculator calc;
  calc.setExpression("sin(cos(tan(acos(asin(atan(atan(acos(1))))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), -0.28061055348533886);
}

TEST(CalculatorTest, ComplexExpressions32) {
  s21::Calculator calc;
  calc.setExpression(
      "(sin(1) + cos(1)) * (tan(1) / (acos(1) - asin(1))) + (atan(1)^2)");
  EXPECT_DOUBLE_EQ(calc.eval(), -0.75314554164716108);
}

TEST(CalculatorTest, ComplexExpressions33) {
  s21::Calculator calc;
  calc.setExpression(
      "sqrt((sin(1) + cos(1)) * (tan(1) / (acos(1) - asin(1))) + (atan(1)^2))");
  EXPECT_TRUE(std::isnan(calc.eval()));
}

TEST(CalculatorTest, ComplexExpressions34) {
  s21::Calculator calc;
  calc.setExpression("1.0 / 1000000000000000000000000000000000.0");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.0000000000000001e-33);
}

TEST(CalculatorTest, ComplexExpressions35) {
  s21::Calculator calc;
  calc.setExpression("acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.59353);
}

TEST(CalculatorTest, ComplexExpressions36) {
  s21::Calculator calc;
  calc.setExpression("log(sin(1e10 / 2999999))");
  EXPECT_TRUE(std::isnan(calc.eval()));
}

TEST(CalculatorTest, ComplexExpressions37) {
  s21::Calculator calc;
  calc.setExpression(
      "1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 "
      "/ (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / (1 / "
      "(1 / (1 / (1 / (1 / 2))))))))))))))))))))))))))))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 0.5);
}

TEST(CalculatorTest, ComplexExpressions38) {
  s21::Calculator calc;
  calc.setExpression(
      "1 / (1 + 1 / (2 + 1 / (3 + 1 / (4 + 1 / (5 + 1 / (6 + 1 / (7 + 1 / (8 + "
      "1 / (9 + 1 / (10 + 1 / (11 + 1 / (12 + 1 / (13 + 1 / (14 + 1 / (15 + 1 "
      "/ (16 + 1 / (17 + 1 / (18 + 1 / (19 + 1 / (20 + 1 / (21 + 1 / (22 + 1 / "
      "(23 + 1 / (24 + 1 / (25 + 1 / (26 + 1 / (27 + 1 / (28 + 1 / (29 + 1 / "
      "(30 + 1 / (31 + 1 / (32 + 1 / 33))))))))))))))))))))))))))))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 0.69777465796400795);
}

int main(int argc, char** argv) {
  double result =
      acos(-0.5) + asin(-0.5) + atan(0.1) * cos(30) * sin(20) * tan(45);
  std::cout << "Результат: " << result << std::endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

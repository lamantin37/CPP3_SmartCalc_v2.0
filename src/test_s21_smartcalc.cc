#include <gtest/gtest.h>

#include <cmath>

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
}  // wolfram: 1.07 // google: -0.04

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
}  // wolfram 8.23 // google 3.02

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
  EXPECT_DOUBLE_EQ(calc.eval(), 1.5935309268233344);
}  // wolfram 1.60032 // google 1.593530

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

TEST(CalculatorTest, ComplexExpressions39) {
  s21::Calculator calc;
  calc.setExpression("ln(2^(sin(3.14) + cos(1.57)) - sqrt(4))");
  EXPECT_TRUE(std::isnan(calc.eval()));
}

TEST(CalculatorTest, ComplexExpressions40) {
  s21::Calculator calc;
  calc.setExpression("cos(2^(tan(3.14) - sin(1.57)) * sqrt(16))");
  EXPECT_DOUBLE_EQ(calc.eval(), -0.41413970498991637);
}

TEST(CalculatorTest, ComplexExpressions41) {
  s21::Calculator calc;
  calc.setExpression("asin(2^(sin(3.14) + cos(1.57)) / sqrt(4))");
  EXPECT_DOUBLE_EQ(calc.eval(), 0.52455587485994881);
}

TEST(CalculatorTest, ComplexExpressions42) {
  s21::Calculator calc;
  calc.setExpression("atan(2^(tan(3.14) - sin(1.57)) + sqrt(16))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.3521014222272312);
}

TEST(CalculatorTest, ComplexExpressions43) {
  s21::Calculator calc;
  calc.setExpression("acos(2.5 * (cos(1) - sin(0.5)) / (tan(1) + 1))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.5112509165719772);
}

TEST(CalculatorTest, ComplexExpressions45) {
  s21::Calculator calc;
  calc.setExpression("sin(cos(tan(1.5^2 - sqrt(16) / ln(10))) * acos(0.7))");
  EXPECT_DOUBLE_EQ(calc.eval(), 0.62302621558935645);
}

TEST(CalculatorTest, ComplexExpressions46) {
  s21::Calculator calc;
  calc.setExpression("sqrt(2^(cos(1.2) - sin(0.8)) * tan(3.6 / sqrt(9)))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.4181289045281718);
}

TEST(CalculatorTest, ComplexExpressions47) {
  s21::Calculator calc;
  calc.setExpression("cos(2.5 + sin(1.2 * tan(0.8 / sqrt(9))) * 3^(ln(2)))");
  EXPECT_DOUBLE_EQ(calc.eval(), -0.99885315255329443);
}

TEST(CalculatorTest, ComplexExpressions48) {
  s21::Calculator calc;
  calc.setExpression("log(2^(sin(1.5) + cos(2.5)) / (tan(0.7) + ln(1.2)))");
  EXPECT_DOUBLE_EQ(calc.eval(), 0.048549088779287458);
}  // wolfram 0.111788 // google 0.04854

TEST(CalculatorTest, ComplexExpressions49) {
  s21::Calculator calc;
  calc.setExpression("2 + (3 - (4 * (5 / (6 + (7 - (8 * (9 / (10 ^ 2))))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 3.3713355048859937);
}

TEST(CalculatorTest, ComplexExpressions50) {
  s21::Calculator calc;
  calc.setExpression(
      "1 + (2 - (3 * (4 / (5 + (6 - (7 * (8 / (9 ^ (10 + (11 - (12 * (13 / (14 "
      "+ (15 - (16 * (17 / (18 ^ 19)))))))))))))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.9090909090909023);
}

TEST(CalculatorTest, ComplexExpressions51) {
  s21::Calculator calc;
  calc.setExpression(
      "1 + (2 - (3 * (4 / (5 + (6 - (7 * (8 / (9 ^ (10 + (11 - (12 * (13 / (14 "
      "+ (15 - (16 * (17 / (18 ^ (19 + (20 - (21 * (22 / (23 ^ "
      "24))))))))))))))))))))))");
  EXPECT_DOUBLE_EQ(calc.eval(), 1.9090909090909023);
}

TEST(CalculatorTest, ComplexExpressions52) {
  s21::Calculator calc;
  calc.setExpression(
      "2 ^ (3 ^ (4 ^ (5 ^ (6 ^ (7 ^ (8 ^ (9 ^ (10 ^ (11 ^ (12 ^ 13))))))))))");
  EXPECT_TRUE(std::isinf(calc.eval()));
}

TEST(CalculatorTest, ComplexExpressions53) {
  s21::Calculator calc;
  calc.setExpression(
      "sin(2) + (cos(3) - (tan(4) * (acos(5) + (asin(6) - (atan(7) * (cos(8) + "
      "(sin(9) ^ (tan(10) + (acos(11) - (asin(12) * (atan(13) / (cos(14) + "
      "(sin(15) - (tan(16) * (acos(17) / (sin(18) ^ (cos(19) + (tan(20) - "
      "(asin(21) * (atan(22) / (cos(23) + (sin(24) - (tan(25) * (acos(26) / "
      "(sin(27) ^ (cos(28) + (tan(29) - (asin(30) * (atan(31) / (cos(32) + "
      "(sin(33) - (tan(34) * (acos(35) / (sin(36) ^ (cos(37) + (tan(38) - "
      "(asin(39) * (atan(40) / (cos(41) + (sin(42) - (tan(43) * (acos(44) / "
      "(sin(45) ^ (cos(46) + (tan(47) - (asin(48) * (atan(49) / (cos(50) + "
      "(sin(51) - (tan(52) * (acos(53) / (sin(54) ^ (cos(55) + (tan(56) - "
      "(asin(57) * (atan(58) / (cos(59) + (sin(60) - (tan(61) * (acos(62) / "
      "(sin(63) ^ (cos(64) + (tan(65) - (asin(66) * (atan(67) / (cos(68) + "
      "(sin(69) - (tan(70) * (acos(71) / (sin(72) ^ (cos(73) + (tan(74) - "
      "(asin(75) * (atan(76) / (cos(77) + (sin(78) - (tan(79) * (acos(80) / "
      "(sin(81) ^ (cos(82) + (tan(83) - (asin(84) * (atan(85) / (cos(86) + "
      "(sin(87) - (tan(88) * (acos(89) / (sin(90) ^ (cos(91) + (tan(92) - "
      "(asin(93) * (atan(94) / (cos(95) + (sin(96) - (tan(97) * (acos(98) / "
      "(sin(99) ^ "
      "(cos(100))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
      ")))))))))))))))))))))))))))))))))))");
  EXPECT_TRUE(std::isnan(calc.eval()));
}

TEST(CalculatorTest, ComplexExpressions54) {
  s21::Calculator calc("x^x^x^x", 2);
  EXPECT_EQ(calc.eval(), 65536);
}

TEST(CalculatorTest, ComplexExpressions55) {
  s21::Calculator calc("-5");
  EXPECT_EQ(calc.eval(), -5);
}

TEST(CalculatorTest, ComplexExpressions56) {
  s21::Calculator calc("-x", 5);
  EXPECT_EQ(calc.eval(), -5);
}

TEST(CalculatorTest, ComplexExpressions57) {
  s21::Calculator calc("-7 + 7 + 100");
  EXPECT_EQ(calc.eval(), 100);
}

TEST(CalculatorTest, ComplexExpressions58) {
  s21::Calculator calc("7 + (-7) + 100");
  EXPECT_EQ(calc.eval(), 100);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

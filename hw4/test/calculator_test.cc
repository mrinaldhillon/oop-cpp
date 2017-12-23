#include "lib/calculator.h"
#include <stdexcept>
#include "gtest/gtest.h"

namespace {
TEST(CalculatorTest, Multiply3by4) {
  EXPECT_EQ(12, Calculator::multiply(3, 4));
}

TEST(CalculatorTest, Multiply2Point5by5Point5) {
  EXPECT_EQ(2.5f * 5.5f, Calculator::multiply(2.5f, 5.5f));
}
TEST(CalculatorTest, Divide3by2) { EXPECT_EQ(1.5f, Calculator::divide(3, 2)); }

TEST(CalculatorTest, Divide2Point5by5Point5) {
  EXPECT_EQ(2.5f / 5.5f, Calculator::divide(2.5f, 5.5f));
}

TEST(CalculatorTest, DividebyZeroThrowsInvalidArgumentException) {
  EXPECT_THROW(Calculator::divide(5, 0), std::invalid_argument);
}
}

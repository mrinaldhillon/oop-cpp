#include <memory>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libaccount.h"

using namespace std;

namespace {
using namespace bank;

class SavingsAccountTest : public ::testing::Test {
 protected:
  SavingsAccount savings_account_{25.0f};
};

class CheckingAccountTest : public ::testing::Test {
 protected:
  shared_ptr<SavingsAccount> savings_account_ =
      make_shared<SavingsAccount>(25.0f);
  CheckingAccount checking_account_{savings_account_, 25.0f};
};

TEST_F(SavingsAccountTest, instantiationToThrowInsufficientFundsException) {
  EXPECT_THROW(SavingsAccount(20.0f), InsufficientFundsException);
}

TEST_F(SavingsAccountTest, deposit50EqualsBalance75) {
  EXPECT_FLOAT_EQ(savings_account_.deposit(50.0f), 75);
}

TEST_F(SavingsAccountTest, withdrawWithSufficientFinds) {
  EXPECT_NO_THROW(savings_account_.withdraw(20.0f));
}

TEST_F(SavingsAccountTest, withdrawToThrowInsufficientSufficientFinds) {
  EXPECT_THROW(savings_account_.withdraw(100.0f), InsufficientFundsException);
}

TEST_F(CheckingAccountTest, instantiationToThrowInsufficientFundsException) {
  EXPECT_THROW(CheckingAccount(savings_account_, 20.0f),
               InsufficientFundsException);
}

TEST_F(CheckingAccountTest, withdrawWithSufficientFinds) {
  checking_account_.deposit(100.0f);
  EXPECT_NO_THROW(checking_account_.withdraw(100.0f));
}

TEST_F(CheckingAccountTest, withdrawToThrowInsufficientSufficientFinds) {
  EXPECT_THROW(checking_account_.withdraw(100.0f), InsufficientFundsException);
}

TEST_F(CheckingAccountTest, withdrawWithPenalty) {
  checking_account_.withdraw(30.0f);
  EXPECT_FLOAT_EQ(checking_account_.getBalance(), -50.0f);
  EXPECT_FLOAT_EQ(savings_account_->getBalance(), 20.0f);
}
}

#include "lib/savings-account.h"
#include "lib/insufficient-funds_exception.h"

namespace bank {

SavingsAccount::SavingsAccount(float opening_deposit) {
  if (opening_deposit < 25)
    throw InsufficientFundsException("Minimum opening deposit: $25");
  balance_ = opening_deposit;
}

float SavingsAccount::getBalance() const { return balance_; }

float SavingsAccount::deposit(float amount /*= 0.0*/) {
  return balance_ += amount;
}

void SavingsAccount::withdraw(float amount /*=0.0*/) {
  if (balance_ - amount < 0) throw InsufficientFundsException();
  balance_ -= amount;
}
}

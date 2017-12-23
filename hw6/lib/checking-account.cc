#include "lib/checking-account.h"
#include "lib/insufficient-funds_exception.h"

using namespace std;
namespace bank {

CheckingAccount::CheckingAccount(
    std::shared_ptr<SavingsAccount> savings_account, float opening_deposit)
    : savings_account_(savings_account) {
  if (opening_deposit < 25)
    throw InsufficientFundsException("Minimum opening deposit: $25");

  balance_ = opening_deposit;
}

float CheckingAccount::getBalance() const { return balance_; }

float CheckingAccount::deposit(float amount /*= 0.0*/) {
  return balance_ += amount;
}

void CheckingAccount::withdraw(float amount /*=0.0*/) {
  if (balance_ > amount) {
    balance_ -= amount;
    return;
  }

  if (balance_ + savings_account_->getBalance() < amount)
    throw InsufficientFundsException();

  amount -= balance_;
  balance_ = 0;
  savings_account_->withdraw(amount);
  chargePenalty(50.0f);
}

void CheckingAccount::chargePenalty(float penalty) { balance_ -= penalty; }
}

#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "lib/account.h"

namespace bank {
class SavingsAccount : public Account {
 public:
  SavingsAccount(float opening_deposit = 0.0);
  float getBalance() const;
  float deposit(float amount = 0.0);
  void withdraw(float amount = 0.0);
};
}

#endif  // SAVINGS_ACCOUNT_H

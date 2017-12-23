#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include <memory>
#include "lib/account.h"
#include "lib/savings-account.h"

namespace bank {
class CheckingAccount : public Account {
 private:
  std::shared_ptr<SavingsAccount> savings_account_;
  void chargePenalty(float penalty);

 public:
  CheckingAccount(std::shared_ptr<SavingsAccount> savings_account,
                  float opening_deposit);
  float getBalance() const;
  float deposit(float amount = 0.0);
  /* TODO: withdraw is MT unsafe at the moment, since it modifies balance of
   * savings_account that may be shared by another thread
   */
  void withdraw(float amount = 0.0);
};
}

#endif  // CHECKING_ACCOUNT_H

#ifndef ACCOUNT_H
#define ACCOUNT_H

namespace bank {
class Account {
 protected:
  float balance_ = 0.0;

 public:
  virtual ~Account() {}
  virtual float getBalance() const = 0;
  virtual float deposit(float amount = 0.0) = 0;
  virtual void withdraw(float amount = 0.0) = 0;
};
}

#endif  // ACCOUNT_H

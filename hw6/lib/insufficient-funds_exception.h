#ifndef INSUFFICIENT_FUNDS_EXCEPTION_H
#define INSUFFICIENT_FUNDS_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace bank {
class InsufficientFundsException : public std::invalid_argument {
 public:
  InsufficientFundsException(const std::string& message)
      : std::invalid_argument(message) {}
  InsufficientFundsException(const char* message)
      : std::invalid_argument(message) {}
  InsufficientFundsException() : std::invalid_argument("Insuffcient Funds!!") {}
};
}

#endif  // INSUFFICIENT_FUNDS_EXCEPTION_H

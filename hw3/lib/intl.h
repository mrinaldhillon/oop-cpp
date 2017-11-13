#ifndef INTL_H
#define INTL_H

#include "lib/student_status.h"

class Intl final : public StudentStatus {
 private:
  const std::string status_ = "International";

 public:
  Intl(float tution) : StudentStatus(tution) {}
  const std::string& GetStatus() const { return status_; }
};

#endif  // INTL_H

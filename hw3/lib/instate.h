#ifndef INSTATE_H
#define INSTATE_H

#include "lib/student_status.h"

class InState final : public StudentStatus {
 private:
  const std::string status_ = "InState";

 public:
  InState(float tution) : StudentStatus(tution) {}
  const std::string& GetStatus() const { return status_; }
};

#endif  // INSTATE_H

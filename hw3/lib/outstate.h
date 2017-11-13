#ifndef OUTSTATE_H
#define OUTSTATE_H

#include "lib/student_status.h"

class OutState final : public StudentStatus {
 private:
  const std::string status_ = "OutState";

 public:
  OutState(float tution) : StudentStatus(tution) {}
  const std::string& GetStatus() const { return status_; }
};

#endif  // OUTSTATE_H

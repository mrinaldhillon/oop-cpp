#ifndef INSTATE_H
#define INSTATE_H

#include "lib/student_status.h"

class InState final : public StudentStatus {
 public:
  InState(float tution) : StudentStatus(tution) {}
  ~InState() = default;
  float GetTution() const { return tution_; }
};

#endif  // INSTATE_H

#ifndef OUTSTATE_H
#define OUTSTATE_H

#include "lib/student_status.h"

class OutState final : public StudentStatus {
 public:
  OutState(float tution) : StudentStatus(tution) {}
  float GetTution() const { return tution_; }
};

#endif  // OUTSTATE_H

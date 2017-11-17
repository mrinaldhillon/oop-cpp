#ifndef INSTATE_H
#define INSTATE_H

#include "lib/student_status.h"

class InState final : public StudentStatus {
 public:
  InState(float tution) : StudentStatus(tution) { status_ = "InState"; }
  InState* clone() const { return new InState(*this); }
};

#endif  // INSTATE_H

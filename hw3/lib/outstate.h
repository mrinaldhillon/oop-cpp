#ifndef OUTSTATE_H
#define OUTSTATE_H

#include "lib/student_status.h"

class OutState final : public StudentStatus {
 public:
  OutState(float tution) : StudentStatus(tution) { status_ = "OutState"; }
  OutState* clone() const { return new OutState(*this); }
};

#endif  // OUTSTATE_H

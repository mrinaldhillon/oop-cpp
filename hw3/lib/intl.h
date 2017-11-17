#ifndef INTL_H
#define INTL_H

#include "lib/student_status.h"

class Intl final : public StudentStatus {
 public:
  Intl(float tution) : StudentStatus(tution) { status_ = "International"; }
  Intl* clone() const { return new Intl(*this); }
};

#endif  // INTL_H

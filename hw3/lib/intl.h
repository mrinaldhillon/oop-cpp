#ifndef INTL_H
#define INTL_H

#include "lib/student_status.h"

class Intl final : public StudentStatus {
 public:
  Intl(float tution) : StudentStatus(tution) {}
  float GetTution() const { return tution_; }
};

#endif  // INTL_H

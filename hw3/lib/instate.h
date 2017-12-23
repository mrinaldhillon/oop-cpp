#ifndef INSTATE_H
#define INSTATE_H

#include <string>
#include "lib/student_status.h"

class InState final : public StudentStatus {
 public:
  InState(float tution);
  float GetTution() const;
  const std::string& GetStatus() const;
};

#endif  // INSTATE_H

#ifndef OUTSTATE_H
#define OUTSTATE_H

#include <string>
#include "lib/student_status.h"

class OutState final : public StudentStatus {
 public:
  OutState(float tution);
  float GetTution() const;
  const std::string& GetStatus() const;
};

#endif  // OUTSTATE_H

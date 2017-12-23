#ifndef INTL_H
#define INTL_H

#include <string>
#include "lib/student_status.h"

class Intl final : public StudentStatus {
 public:
  Intl(float tution);
  float GetTution() const;
  const std::string& GetStatus() const;
};

#endif  // INTL_H

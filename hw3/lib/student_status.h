#ifndef STUDENT_STATUS_H
#define STUDENT_STATUS_H

#include <string>

class StudentStatus {
 protected:
  float tution_ = 0;
  std::string status_ = "NoStatus";

 public:
  virtual ~StudentStatus() {}
  virtual float GetTution() const = 0;
  virtual const std::string& GetStatus() const = 0;
};

#endif  // STUDENT_STATUS_H

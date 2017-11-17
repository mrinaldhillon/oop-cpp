#ifndef STUDENT_STATUS_H
#define STUDENT_STATUS_H

#include <string>

class StudentStatus {
 protected:
  float tution_ = 0;
  std::string status_ = "NoStatus";
  // TBD: Is defining the constructor of abstract for benefit of derived classes
  // a good practice?
  StudentStatus(float tution) { tution_ = tution; }
  StudentStatus() {}

 public:
  virtual ~StudentStatus() {}
  virtual StudentStatus* clone() const = 0;
  virtual float GetTution() const { return tution_; }
  virtual const std::string& GetStatus() const { return status_; }
};

#endif  // STUDENT_STATUS_H

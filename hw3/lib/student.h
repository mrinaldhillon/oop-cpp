#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "lib/student_status.h"

class Student final {
 private:
  std::string name_;
  const StudentStatus* status_ = NULL;

 public:
  Student(const StudentStatus& status, const std::string& name);
  ~Student();
  const std::string& GetName() const;
  float GetTution() const;
  const std::string& GetStatus() const;
  void SetStatus(const StudentStatus& status);
};

#endif  // STUDENT_H

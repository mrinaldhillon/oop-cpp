#ifndef STUDENT_H
#define STUDENT_H

#include <memory>
#include <string>
#include "lib/student_status.h"

class Student final {
 private:
  std::string name_;
  std::unique_ptr<StudentStatus> status_;

 public:
  Student(std::unique_ptr<StudentStatus> status, const std::string& name);
  const std::string& GetName() const;
  float GetTution() const;
  const std::string& GetStatus() const;
  void SetStatus(std::unique_ptr<StudentStatus> status);
};

#endif  // STUDENT_H

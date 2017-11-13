#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "lib/student_status.h"
using namespace std;

class Student final {
 private:
  string name_;
  const StudentStatus* status_;

 public:
  Student(const StudentStatus* status, const string& name);
  ~Student();
  const string& GetName();
  float GetTution();
  void SetStatus(const StudentStatus* status);
};

#endif  // STUDENT_H

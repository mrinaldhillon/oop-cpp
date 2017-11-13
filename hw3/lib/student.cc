#include "lib/student.h"

Student::Student(const StudentStatus* status, const string& name) {
  status_ = status;
  name_ = name;
}

Student::~Student() {
  if (status_) delete status_;
}

const string& Student::GetName() { return name_; }

float Student::GetTution() { return status_->GetTution(); }

void Student::SetStatus(const StudentStatus* status) {
  if (status_) delete status_;
  status_ = status;
}

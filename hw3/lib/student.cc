#include "lib/student.h"
using namespace std;

Student::Student(const StudentStatus& status, const string& name) {
  status_ = status.clone();
  name_ = name;
}

Student::~Student() {
  if (status_) delete status_;
}

const string& Student::GetName() const { return name_; }

float Student::GetTution() const { return status_->GetTution(); }

const std::string& Student::GetStatus() const { return status_->GetStatus(); }

void Student::SetStatus(const StudentStatus& status) {
  StudentStatus* new_status = status.clone();
  if (status_) delete status_;
  status_ = new_status;
}

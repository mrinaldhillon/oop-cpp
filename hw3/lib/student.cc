#include "lib/student.h"
#include <memory>
#include <string>

Student::Student(std::unique_ptr<StudentStatus> status,
                 const std::string& name) {
  status_ = std::move(status);
  name_ = name;
}

const std::string& Student::GetName() const { return name_; }

float Student::GetTution() const { return status_->GetTution(); }

const std::string& Student::GetStatus() const { return status_->GetStatus(); }

void Student::SetStatus(std::unique_ptr<StudentStatus> status) {
  status_ = std::move(status);
}

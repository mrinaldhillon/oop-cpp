#ifndef STUDENT_STATUS_H
#define STUDENT_STATUS_H

class StudentStatus {
 private:
  float tution_;

 protected:
  StudentStatus(float tution) { tution_ = tution; }

 public:
  virtual ~StudentStatus() {}
  float GetTution() const { return tution_; }
  virtual const std::string& GetStatus() const = 0;
};

#endif  // STUDENT_STATUS_H

#ifndef STUDENT_STATUS_H
#define STUDENT_STATUS_H

class StudentStatus {
 protected:
  float tution_;
  StudentStatus(float tution) { tution_ = tution; }

 public:
  virtual ~StudentStatus() {}
  virtual float GetTution() const = 0;  // {return tution_;}
};

#endif  // STUDENT_STATUS_H

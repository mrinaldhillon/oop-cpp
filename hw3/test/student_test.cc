#include <iostream>
#include <vector>
#include "lib/libstudent.h"

int main() {
  vector<Student *> students;

  Student *jon = new Student(new InState(1000), "jon");
  Student *jane = new Student(new OutState(2000), "jane");
  Student *josh = new Student(new Intl(3000), "josh");

  students.push_back(jon);
  students.push_back(jane);
  students.push_back(josh);

  for (Student *student : students) {
    cout << "Student: " << student->GetName()
         << "\ttution: " << student->GetTution() << "\n";
  }

  cout << "Jane qualifies for to be an InState student.. change status!!!\n";
  jane->SetStatus(new InState(1000));
  cout << "Student: jane"
       << "\ttution: " << jane->GetTution() << "\n";

  for (Student *student : students) delete student;

  return 0;
}

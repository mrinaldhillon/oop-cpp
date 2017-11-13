#include <iostream>
#include <vector>
#include "lib/libstudent.h"
using namespace std;

void TestStudent() {
  Student john(new InState(1000), "jon");
  Student jane(new OutState(2000), "jane");
  Student josh(new Intl(3000), "josh");

  vector<Student *> students{&john, &jane, &josh};

  for (Student *student : students) {
    cout << "Student: " << student->GetName()
         << ", Status: " << student->GetStatus()
         << ", tution: " << student->GetTution() << "\n";
  }

  cout << "Jane qualifies for to be an InState student.. change status!!!\n";
  jane.SetStatus(new InState(1000));
  cout << "Student: jane"
       << ", Status: " << jane.GetStatus() << ", tution: " << jane.GetTution()
       << "\n";
}

int main() {
  TestStudent();
  return 0;
}

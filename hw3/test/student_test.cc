#include <iostream>
#include <vector>
#include "lib/libstudent.h"
using namespace std;

void TestStudent() {
  Student john(InState(1000), "jon");
  Student josh(Intl(3000), "josh");
  Student jane(OutState(2000), "jane");

  vector<Student*> students{&john, &josh, &jane};
  for (Student* student : students) {
    cout << "Student: " << student->GetName()
         << ", Status: " << student->GetStatus()
         << ", tution: " << student->GetTution() << "\n";
  }

  cout << "Jane qualifies for to be an InState student.. change status!!!\n";
  jane.SetStatus(InState(1000));
  cout << "Student: " << jane.GetName() << ", Status: " << jane.GetStatus()
       << ", tution: " << jane.GetTution() << "\n";
}

int main() {
  TestStudent();
  return 0;
}

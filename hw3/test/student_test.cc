#include <iostream>
#include <memory>
#include <vector>
#include "lib/libstudent.h"

using namespace std;

void TestStudent() {
  Student john(make_unique<InState>(1000), "jon");
  Student josh(make_unique<Intl>(3000), "josh");
  Student jane(make_unique<OutState>(2000), "jane");

  vector<Student*> students{&john, &josh, &jane};
  for (const auto student : students) {
    cout << "Student: " << student->GetName()
         << ", Status: " << student->GetStatus()
         << ", tution: " << student->GetTution() << "\n";
  }

  cout << "Jane qualifies for to be an InState student.. change status!!!\n";
  jane.SetStatus(make_unique<InState>(1000));
  cout << "Student: " << jane.GetName() << ", Status: " << jane.GetStatus()
       << ", tution: " << jane.GetTution() << "\n";
}

int main() {
  TestStudent();
  return 0;
}

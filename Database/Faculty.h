/* Initializes all the constructors, destructor, functions, and variables of the Faculty class which is a subclass of the Human class. This means
   Faculty members will also have the name, ID, and level variables. Overloaded the comparison operators.
*/
#include <iostream>
#include "DLList.h"
#include "Student.h"
using namespace std;

class Faculty : public Human{
public:
  Faculty();
  Faculty(int theID);
  Faculty(int theID, string theName, string theLevel, string theDepartment);
  ~Faculty();
  string getDepartment();
  void setDepartment(string theDepartment);
  void addAdvisee(int a);
  void removeAdvisee(int a);
  bool hasAdvisees();
  void printInfo();
  void setAdvisees(DLList<int> *a);
  DLList<int>* getAdvisees();
  string writeInfo();

private:
  string department;
  DLList<int>* advisees;

friend bool operator==(Faculty faculty1, Faculty faculty2){
  return (faculty1.getID() == faculty2.getID());
}

friend bool operator!=(Faculty faculty1, Faculty faculty2){
  return (faculty1.getID() != faculty2.getID());
}

friend bool operator<(Faculty faculty1, Faculty faculty2){
  return (faculty1.getID() < faculty2.getID());
}

friend bool operator>(Faculty faculty1, Faculty faculty2){
  return (faculty1.getID() > faculty2.getID());
}

};

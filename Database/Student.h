/* Initialization of the constructors, destrutctor, functions, and variables of the Student class. The student class is a subclass of the Human class.
   Comparison operators have been overloaded.
*/
#include <iostream>
#include "Human.h"
using namespace std;

class Student:public Human{
public:
  Student();
  Student(int theID);
  Student(int theID, string theName, string theLevel, string theMajor, double theGPA, int theAdvisor);
  ~Student();
  string getMajor();
  double getGPA();
  int getAdvisor();
  void setMajor(string theMajor);
  void setGPA(double theGPA);
  void setAdvisor(int theAdvisor);
  void printInfo();
  string writeInfo();

private:
  string major;
  double gpa;
  int advisor;

friend bool operator==(Student student1, Student student2){
  return (student1.getID() == student2.getID());
}

friend bool operator!=(Student student1, Student student2){
  return (student1.getID() != student2.getID());
}

friend bool operator<(Student student1, Student student2){
  return (student1.getID() < student2.getID());
}

friend bool operator>(Student student1, Student student2){
  return (student1.getID() > student2.getID());
}

};

/* Implementation of the constructors, destructor, and functions of the Student class.
*/
#include "Student.h"
#include <string>
using namespace std;

//default constructor
Student::Student() : Human(){
  major = "";
  gpa = 0.0;
  advisor = 0;
}

//overloaded constructor
Student::Student(int theID) : Human(theID, "", ""){
  major = "";
  gpa = 0;
  advisor = 0;
}

//overloaded constructor
Student::Student(int theID, string theName, string theLevel, string theMajor, double theGPA, int theAdvisor) : Human(theID, theName, theLevel){
  major = theMajor;
  gpa = theGPA;
  advisor = theAdvisor;
}

//destructor
Student::~Student(){};

/*
Function name: getMajor
What it does: returns major variable of student
@param: none
@return: string major
*/
string Student::getMajor(){
  return major;
}

/*
Function name: getGPA
What it does: returns gpa variable of the student
@param: none
@return: double gpa
*/
double Student::getGPA(){
  return gpa;
}

/*
Function name: getAdvisor
What it does: returns advisor variable of the student
@param: none
@return: int advisor
*/
int Student::getAdvisor(){
  return advisor;
}

/*
Function name: setMajor
What it does: changes/sets the major variable of the student
@param: string theMajor
@return: none
*/
void Student::setMajor(string theMajor){
  major = theMajor;
}

/*
Function name: setGPA
What it does: changes/sets the gpa variable of the student
@param: double theGPA
@return: none
*/
void Student::setGPA(double theGPA){
  gpa = theGPA;
}

/*
Function name: setAdvisor
What it does: changes/sets the advisor variable of the student
@param: int theAdvisor
@return: none
*/
void Student::setAdvisor(int theAdvisor){
  advisor = theAdvisor;
}

/*
Function name: printInfo
What it does: prints the all the information of the student to cout
@param: none
@return: none
*/
void Student::printInfo(){
  cout << "Student ID: " << getID() << endl;
  cout << "Name : " << getName() << endl;
  cout << "Level: " << getLevel() << endl;
  cout << "Major: " << major << endl;
  cout << "GPA: " << gpa << endl;
  cout << "Advisor: " << advisor << endl;
}

/*
Function name: writeInfo
What it does: writes all the information of the student in txt file format
@param: none
@return: none
*/
string Student::writeInfo(){
  string information;
  information = to_string(getID()) + "|" + getName() + "|" + getLevel() + "|" + major + "|" + to_string(gpa) + "|" + to_string(advisor);
  return information;
}

/* Implementation of the constructors, destructor, and functions of the Faculty class. Can access all private variables and make changes.
*/
#include "Faculty.h"
using namespace std;

//default constructor
Faculty::Faculty() : Human(){
  department = "";
  advisees = new DLList<int>();
}

//overloaded constructor
Faculty::Faculty(int theID) : Human(theID, "", "") {
  department = "";
  advisees = new DLList<int>();
}

//overloaded constructor
Faculty::Faculty(int theID, string theName, string theLevel, string theDepartment) : Human(theID, theName, theLevel){
  department = theDepartment;
  advisees = new DLList<int>();
}

//destructor
Faculty::~Faculty(){};

/*
Function name: getDepartment
What it does: returns the department variable of the Faculty class
@param: none
@return: string department
*/
string Faculty::getDepartment(){
  return department;
}

/*
Function name: setDepartment
What it does: changes/sets department variable
@param: string s
@return: none
*/
void Faculty::setDepartment(string s){
  department = s;
}

/*
Function name: hasAdvisees
What it does: returns true if advisees linked list has items, false if not
@param: none
@return: true or false
*/
bool Faculty::hasAdvisees(){
  if(advisees->isEmpty()){
    return true;
  }
  return false;
}

/*
Function name: addAdvisee
What it does: adds advisee to the linked list
@param: int a
@return: none
*/
void Faculty::addAdvisee(int a){
  advisees->insertBack(a);
}

/*
Function name: setAdvisees
What it does: changes/sets advisee linked list to different one within parameter
@param: DLList<int> *a
@return: none
*/
void Faculty::setAdvisees(DLList<int> *a){
  advisees = a;
}

/*
Function name: getAdvisees
What it does: returns advisees linked list
@param: none
@return: DLList<int>* advisees
*/
DLList<int>* Faculty::getAdvisees(){
  return advisees;
}

/*
Function name: removeAdvisee
What it does: removes an advisee from the linked list
@param: int a
@return: none
*/
void Faculty::removeAdvisee(int a){
  advisees->remove(a);
}

/*
Function name: printInfo
What it does: prints all the information of the faculty member to cout
@param: none
@return: none
*/
void Faculty::printInfo(){
  cout << "Faculty ID: " << getID() << endl;
  cout << "Name: " << getName() << endl;
  cout << "Level: " << getLevel() << endl;
  cout << "Department: " << department << endl;
  cout << "Advisees: ";
  if(advisees->length() == 0){
    cout << "0" << endl;
  }
  else{
    for(int i = 0; i < advisees->length(); i++){
      cout << advisees->findItem(i) << " ";
    }
    cout << endl;
  }
}

/*
Function name: writeInfo
What it does: writes information of faculty member in txt file format
@param: none
@return: string information
*/
string Faculty::writeInfo(){
  string information;
  information = to_string(getID()) + "|" + getName() + "|" + getLevel() + "|" + department + "|";
  if(advisees->length() == 0){
    information += "0";
    information += "|";
    return information;
  }
  else if(advisees->length() == 1){
    information += to_string(advisees->findItem(0));
    information += "|";
    return information;
  }
  else{
    for(int i = 0; i < advisees->length(); i++){
      information += to_string(advisees->findItem(i)) + ",";
    }
    information.erase(information.length() - 1);
    information += "|";
    return information;
  }
}

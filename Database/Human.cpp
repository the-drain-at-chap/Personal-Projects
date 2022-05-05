/* Implementation of the constructors, destructor, and functions of the Human class. Functions give access to variables and access to changing them.
   These functions will be able to be used in both the Faculty and Student classes
*/
#include "Human.h"
using namespace std;

//default constructor
Human::Human(){
  id = 0;
  name = "";
  level = "";
}

//overloaded constructor
Human::Human(int theID, string theName, string theLevel){
  id = theID;
  name = theName;
  level = theLevel;
}

//destructor
Human::~Human(){};

/*
Function name: getID
What it does: returns the id variable of the human
@param: none
@return: int id
*/
int Human::getID(){
  return id;
}

/*
Function name: getName
What it does: returns the name variable of the human
@param: none
@return: string name
*/
string Human::getName(){
  return name;
}

/*
Function name: getLevel
What it does: returns the level variable of the human
@param: none
@return: string level
*/
string Human::getLevel(){
  return level;
}

/*
Function name: setID
What it does: changes/sets the ID variable of the human
@param: int theID
@return: none
*/
void Human::setID(int theID){
  id = theID;
}

/*
Function name: setName
What it does: changes/sets the name variable of the human
@param: string theName
@return: none
*/
void Human::setName(string theName){
  name = theName;
}

/*
Function name: setLevel
What it does: changes/sets the level variable of the human
@param: string theLevel
@return: none
*/
void Human::setLevel(string theLevel){
  level = theLevel;
}

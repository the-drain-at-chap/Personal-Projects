/* This file holds the entire code for running the database, it achieves what the assignment is asking for.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"
#include "Faculty.h"
#include "AStack.h"
using namespace std;

int main(int argc, char* argv[]){

  //variables that need to be declared at beginning of database running
  int input = 0;
  string previousCommand = "";
  int lineCount = 0;
  string usedForLineCount;
  ifstream inputStream;
  ofstream outputStream;
  BST<Student> *studentBST = new BST<Student>();
  BST<Faculty> *facultyBST = new BST<Faculty>();
  AStack<BST<Student>> rollbackStudent(4);
  AStack<BST<Faculty>> rollbackFaculty(4);

  //reads through studentTable.txt file and takes data, creates new one if not found
  inputStream.open("studentTable.txt");
  if(!inputStream.is_open()){
    cout << "Student table file does not exist. Will create new one." << endl;
  }
  else{
    while(getline(inputStream, usedForLineCount)){
      ++lineCount;
    }
    inputStream.close();
    inputStream.open("studentTable.txt");
    for(int i = 0;i < lineCount; i++){
      string information[6];
      for(int j = 0; j < 6; j++){
        if(j == 5){
          getline(inputStream, usedForLineCount, '\n');
          information[j] = usedForLineCount;
        }
        else{
          getline(inputStream, usedForLineCount, '|');
          information[j] = usedForLineCount;
        }
      }
      Student aStudent;
      aStudent.setID(stoi(information[0]));
      aStudent.setName(information[1]);
      aStudent.setLevel(information[2]);
      aStudent.setMajor(information[3]);
      aStudent.setGPA(stod(information[4]));
      aStudent.setAdvisor(stoi(information[5]));
      TreeNode<Student> *studentNode = new TreeNode<Student>(aStudent.getID(), aStudent);
      studentBST->insert(studentNode);
    }
    cout << "Successfully read studentTable.txt" << endl;
    inputStream.close();
  }

  //reads through facultyTable.txt file and takes data, creates new one if not found
  inputStream.open("facultyTable.txt");
  if(!inputStream.is_open()){
    cout << "Faculty table file does not exist. Will create new one." << endl;
  }
  else{
    lineCount = 0;
    usedForLineCount = "";
    while(getline(inputStream, usedForLineCount)){
      ++lineCount;
    }
    inputStream.close();
    inputStream.open("facultyTable.txt");
    int commaCounter = 0;
    for(int i = 0; i < lineCount; i++){
      string information2[4];
      DLList<int> *theAdvisees = new DLList<int>();
      for(int j = 0; j < 5; j++){
        if(j == 4){
          commaCounter = 0;
          getline(inputStream, usedForLineCount, '|');
          for(int k = 0; k < usedForLineCount.length(); k++){
            if(usedForLineCount[k] == ','){
              commaCounter++;
            }
          }
          string delimiter = ",";
          string seperatedAdvisee;
          for(int l = 0; l < commaCounter + 1; l++){
              seperatedAdvisee = usedForLineCount.substr(0, usedForLineCount.find(delimiter));
              theAdvisees->insertBack(stoi(seperatedAdvisee));
              usedForLineCount.erase(0, usedForLineCount.find(delimiter) + delimiter.length());
          }
        }
        else{
          getline(inputStream, usedForLineCount, '|');
          information2[j] = usedForLineCount;
        }
      }
      Faculty aFaculty;
      aFaculty.setID(stoi(information2[0]));
      aFaculty.setName(information2[1]);
      aFaculty.setLevel(information2[2]);
      aFaculty.setDepartment(information2[3]);
      aFaculty.setAdvisees(theAdvisees);
      TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(aFaculty.getID(), aFaculty);
      facultyBST->insert(facultyNode);
    }
    cout << "Successfully read facultyTable.txt" << endl;
    inputStream.close();
  }

  //loop for database to continue running till user exits with 14 command
  do{
    cout << "1. Print all students and their information." << endl;
    cout << "2. Print all faculty and their information." << endl;
    cout << "3. Find and display student information given the student id." << endl;
    cout << "4. Find and display faculty information given the faculty id." << endl;
    cout << "5. Given a student's id, print the name and info of their faculty advisor." << endl;
    cout << "6. Given a faculty id, print all the names and info of his/her advisees." << endl;
    cout << "7. Add a new student." << endl;
    cout << "8. Delete a student given the id." << endl;
    cout << "9. Add a new faculty member." << endl;
    cout << "10. Delete a faculty member given the id." << endl;
    cout << "11. Change a student's advisor given the student id and the new faculty id." << endl;
    cout << "12. Remove an advisee from a faculty member given the ids." << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    cout << "Enter an input between 1 - 14." << endl;
    cin >> input;
    cin.ignore();

    //used if input is not between 1 - 14
    if(input <= 0 || input >= 15){
      cout << "Input must be between 1 - 14." << endl;
      continue;
    }

    //displays all student's data
    if(input == 1){
      if(studentBST->isEmpty()){
        cout << "There are no students." << endl;
        continue;
      }
      else{
        for(int i = 0; i <= studentBST->getMax()->key; i++){
          if(studentBST->contains(i)){
            studentBST->find(i).printInfo();
          }
        }
        continue;
      }
    }

    //displays all faculty data
    else if(input == 2){
      if(facultyBST->isEmpty()){
        cout << "There are no faculty members." << endl;
        continue;
      }
      else{
        for(int i = 0; i <= facultyBST->getMax()->key; i++){
          if(facultyBST->contains(i)){
            facultyBST->find(i).printInfo();
          }
        }
        continue;
      }
    }

    //display specific student data given id
    else if(input == 3){
      int id = 0;
      cout << "Enter the ID of the student: " << endl;
      while(!(cin >> id)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(studentBST->contains(id)){
        studentBST->find(id).printInfo();
        continue;
      }
      else{
        cout << "Student does not exist. Please try again." << endl;
        continue;
      }
    }

    //display specific faculty data given id
    else if(input == 4){
      int id = 0;
      cout << "Enter the ID of the faculty member: " << endl;
      while(!(cin >> id)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(facultyBST->contains(id)){
        facultyBST->find(id).printInfo();
        continue;
      }
      else{
        cout << "Faculty member does not exist. Please try again." << endl;
        continue;
      }
    }

    //given student id, display's advisor's data
    else if(input == 5){
      int id = 0;
      cout << "Enter the ID of the student: " << endl;
      while(!(cin >> id)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(studentBST->contains(id)){
        id = studentBST->find(id).getAdvisor();
        facultyBST->find(id).printInfo();
        continue;
      }
      else{
        cout << "Student does not exist. Please try again." << endl;
        continue;
      }
    }

    //given faculty id, displays all advisees' data
    else if(input == 6){
      int id = 0;
      cout << "Enter the ID of the faculty member: " << endl;
      while(!(cin >> id)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(facultyBST->contains(id)){
        DLList<int> *tempAdvisees = new DLList<int>();
        tempAdvisees = facultyBST->find(id).getAdvisees();
        for(int i = 0; i < tempAdvisees->length(); i++){
          id = tempAdvisees->findItem(i);
          studentBST->find(id).printInfo();
        }
        continue;
      }
      else{
        cout << "Faculty member does not exist. Please try again." << endl;
        continue;
      }
    }

    //add new student to database
    else if(input == 7){
      BST<Student> tempStudentBST = *studentBST;
      BST<Faculty> tempFacultyBST = *facultyBST;
      rollbackStudent.push(tempStudentBST);
      rollbackFaculty.push(tempFacultyBST);
      int id;
      string name;
      string level;
      string major;
      double GPA;
      int advisor;
      cout << "Input the student's ID: " << endl;
      cin >> id;
      cin.ignore();
      cout << "Input the student's name: " << endl;
      getline(cin, name);
      cout << "Input the student's level: " << endl;
      getline(cin, level);
      cout << "Input the student's major: " << endl;
      getline(cin, major);
      cout << "Input the student's GPA: " << endl;
      cin >> GPA;
      cout << "Input the student's advisor ID: " << endl;
      cin >> advisor;
      cin.ignore();
      while(!facultyBST->contains(advisor)){
        cout << "That faculty member does not exist. Enter another advisor's ID: " << endl;
        cin >> advisor;
      }
      Student newStudent(id, name, level, major, GPA, advisor);
      TreeNode<Student> *studentNode = new TreeNode<Student>(newStudent.getID(), newStudent);
      studentBST->insert(studentNode);
      facultyBST->find(advisor).addAdvisee(newStudent.getID());
      cout << "Student successfully added." << endl;
      continue;
    }

    //delete student from database
    else if(input == 8){
      BST<Student> tempStudentBST = *studentBST;
      BST<Faculty> tempFacultyBST = *facultyBST;
      rollbackStudent.push(tempStudentBST);
      rollbackFaculty.push(tempFacultyBST);
      int id;
      cout << "Input the ID of the student you want to delete: " << endl;
      while(!(cin >> id)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(!studentBST->contains(id)){
        cout << "Student does not exist, please try again. " << endl;
        continue;
      }
      else{
        int advisorID = studentBST->find(id).getAdvisor();
        studentBST->remove(id);
        if(advisorID != 0){
          facultyBST->find(advisorID).removeAdvisee(id);
        }
        cout << "Successfully removed student." << endl;
        continue;
      }
    }

    //add faculty to database
    else if(input == 9){
      BST<Student> tempStudentBST = *studentBST;
      BST<Faculty> tempFacultyBST = *facultyBST;
      rollbackStudent.push(tempStudentBST);
      rollbackFaculty.push(tempFacultyBST);
      int id;
      string name;
      string level;
      string department;
      DLList<int> *theAdvisees = new DLList<int>();
      cout << "Input the faculty member's ID: " << endl;
      cin >> id;
      cin.ignore();
      cout << "Input the faculty member's name: " << endl;
      getline(cin,name);
      cout << "Input the faculty member's level: " << endl;
      getline(cin, level);
      cout << "Input the faculty member's department: " << endl;
      getline(cin, department);
      Faculty newFaculty(id, name, level, department);
      newFaculty.setAdvisees(theAdvisees);
      TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(newFaculty.getID(), newFaculty);
      facultyBST->insert(facultyNode);
      cout << "Faculty successfully added." << endl;
      continue;
    }

    //delete faculty from database
    else if(input == 10){
      BST<Student> tempStudentBST = *studentBST;
      BST<Faculty> tempFacultyBST = *facultyBST;
      rollbackStudent.push(tempStudentBST);
      rollbackFaculty.push(tempFacultyBST);
      int id = 0;
      int adviseeID = 0;
      cout << "Enter the ID of the faculty member: " << endl;
      while(!(cin >> id)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(facultyBST->contains(id)){
        int newAdvisorID = 0;
        DLList<int> *tempAdvisees = new DLList<int>();
        tempAdvisees = facultyBST->find(id).getAdvisees();
        while(!tempAdvisees->isEmpty()){
          adviseeID = tempAdvisees->removeFront();
          studentBST->find(adviseeID).setAdvisor(newAdvisorID);
        }
        facultyBST->remove(id);
        cout << "Successfully deleted faculty member." << endl;
        continue;
      }
      else{
        cout << "Faculty member does not exist. Please try again." << endl;
        continue;
      }
    }

    //change a student's advisor to a different one using given student id and new advisor/faculty id
    else if(input == 11){
      BST<Student> tempStudentBST = *studentBST;
      BST<Faculty> tempFacultyBST = *facultyBST;
      rollbackStudent.push(tempStudentBST);
      rollbackFaculty.push(tempFacultyBST);
      int studentID = 0;
      int advisorID = 0;
      cout << "Enter the ID of the student: " << endl;
      while(!(cin >> studentID)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      cout << "Enter the ID of the faculty member: " << endl;
      while(!(cin >> advisorID)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(!studentBST->contains(studentID)){
        cout << "Student does not exist. Please try again." << endl;
        continue;
      }
      if(!facultyBST->contains(advisorID)){
        cout << "Advisor does not exist. Please try again." << endl;
        continue;
      }
      if(studentBST->find(studentID).getAdvisor() == 0){
        studentBST->find(studentID).setAdvisor(advisorID);
        facultyBST->find(advisorID).addAdvisee(studentID);
        continue;
      }
      else{
        int oldAdviseeID = studentBST->find(studentID).getAdvisor();
        facultyBST->find(oldAdviseeID).removeAdvisee(studentID);
        studentBST->find(studentID).setAdvisor(advisorID);
        facultyBST->find(advisorID).addAdvisee(studentID);
        continue;
      }
    }

    //remove advisee from a faculty member using student and faculty ids
    else if(input == 12){
      BST<Student> tempStudentBST = *studentBST;
      BST<Faculty> tempFacultyBST = *facultyBST;
      rollbackStudent.push(tempStudentBST);
      rollbackFaculty.push(tempFacultyBST);
      int adviseeID = 0;
      int facultyID = 0;
      cout << "Enter the ID of the faculty member: " << endl;
      while(!(cin >> facultyID)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(!facultyBST->contains(facultyID)){
        cout << "Faculty member does not exist, please try again." << endl;
        continue;
      }
      cout << "Enter the ID of the advisee you want to delete: " << endl;
      while(!(cin >> adviseeID)){
        cout << "Not a valid ID. Please input again." << endl;
        cin.clear();
      }
      if(!studentBST->contains(adviseeID)){
        cout << "Advisee does not exist. Please try again." << endl;
        continue;
      }
      DLList<int> *tempAdvisees = new DLList<int>();
      tempAdvisees = facultyBST->find(facultyID).getAdvisees();
      if(tempAdvisees->findItem(adviseeID) == 0){
        cout << "Advisee does not exist. Please try again." << endl;
        continue;
      }
      else{
        facultyBST->find(facultyID).removeAdvisee(adviseeID);
        studentBST->find(adviseeID).setAdvisor(0);
        cout << "Successfully removed advisee." << endl;
        continue;
      }
    }

    //rollback
    else if(input == 13){
      BST<Student> tempStudentBST;
      BST<Faculty> tempFacultyBST;
      tempStudentBST = rollbackStudent.pop();
      tempFacultyBST = rollbackFaculty.pop();
      studentBST = &tempStudentBST;
      facultyBST = &tempFacultyBST;
      cout << "Succesfully rolled back." << endl;
      continue;
    }

    //exit and print to txt files
    else if(input == 14){
      string temp;
      ofstream outputfile;
      outputfile.open("studentTable.txt");
      for(int i = 0; i <= studentBST->getMax()->key; i++){
        if(studentBST->contains(i)){
          temp = studentBST->find(i).writeInfo();
          outputfile << temp << endl;
        }
      }
      outputfile.close();
      outputfile.open("facultyTable.txt");
      for(int i = 0; i <= facultyBST->getMax()->key; i++){
        if(facultyBST->contains(i)){
          temp = facultyBST->find(i).writeInfo();
          outputfile << temp << endl;
        }
      }
      outputfile.close();
      return 0;
    }
  }
  while(input != 14);
}

/* Implements all the private variables, public variables, methods, default constructor,
   and destructor needed for a Stack based on Arrays. */

#include "Stack.h"
#include <iostream>
using namespace std;
#include <stdexcept>

template <typename E>
class AStack : public Stack<E>{
private:
  int currentSize;
  int maxSize;
  int current;
  E* stackArray;
public:
  AStack(int sz);
  ~AStack();
  void clear();
  void push(E item);
  E pop();
  E topValue();
  int length();
  bool isEmpty();
};

//default constructor
template <typename E>
AStack<E>::AStack(int sz){
  maxSize = sz;
  current = 0;
  currentSize = 0;
  stackArray = new E[maxSize];
}

//default destructor
template <typename E>
AStack<E>::~AStack(){
  delete[] stackArray;
}

/*
Function name: clear
What it does: deletes current array and creates a new empty one, but still uses max size given by user
@param: none
@return: none
*/
template <typename E>
void AStack<E>::clear(){
  delete[] stackArray;
  currentSize = 0;
  current = 0;
  stackArray = new E[maxSize];
}

/*
Function name: push
What it does: pushes item given by user to the top of the Stack
@param: E item
@return: none
*/
template <typename E>
void AStack<E>::push(E item){
  if(isEmpty()){
    stackArray[0] = item;
    currentSize++;
  }
  else if(currentSize == maxSize){
    E* tempArray = new E[maxSize];
    for(int i = 0; i < maxSize; i++){
      tempArray[i] = stackArray[i];
    }
    maxSize++;
    clear();
    stackArray[0] = item;
    for(int i = 1; i < maxSize; i++){
      stackArray[i] = tempArray[i - 1];
    }
    delete[] tempArray;
    currentSize = maxSize;
  }
  else{
    for(int i = currentSize;i > 0; i--){
      stackArray[i] = stackArray[i - 1];
    }
    stackArray[0] = item;
    currentSize++;
  }
}

/*
Function name: pop
What it does: removes and returns item from the top of the Stack
@param: none
@return: E item stackArray[0]
*/
template <typename E>
E AStack<E>::pop(){
  if(isEmpty()){
    throw std::invalid_argument("Stack is empty!");
  }
  else{
    E item = stackArray[0];
    for(int i = 0; i < currentSize - 1; i++){
      stackArray[i] = stackArray[i + 1];
    }
    currentSize--;
    return item;
  }
}

/*
Function name: topValue
What it does: returns value at top of Stack
@param: none
@return: E item stackArray[0]
*/
template <typename E>
E AStack<E>::topValue(){
  return stackArray[0];
}

/*
Function name: length
What it does: returns the current size of the Stack
@param: none
@return: int currentSize
*/
template <typename E>
int AStack<E>::length(){
  return currentSize;
}

/*
Function name: isEmpty
What it does: checks if Stack holds any values or not
@param: none
@return: true if empty, false if not
*/
template <typename E>
bool AStack<E>::isEmpty(){
  if(currentSize == 0){
    return true;
  }
  else{
    return false;
  }
}

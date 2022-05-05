/* Declares default constructor, destructor, and all the methods used for a Stack abstract class */

template <typename E>
class Stack{
public:
  Stack(){} //default constructor
  virtual ~Stack() {} //base destructor

  //reinitialize the stack
  virtual void clear() = 0;

  //push an elment onto the top of the Stack
  //@param item: elemen being pushed
  virtual void push(E item) = 0;

  //remove the element from the top of the Stack
  //return: element at the top of the Stack
  virtual E pop() = 0;

  //returns the top element of the Stack
  virtual E topValue() = 0;

  //returns length of Stack
  virtual int length() = 0;

  //returns true if Stack is empty, false if not
  virtual bool isEmpty() = 0;
};

#include <iostream>

class Object {
  int row, col;
  ObjectType type;
public: 
  Object(); // constructor
  ~Object():  // destructor
  setCords(int, int);  // set an object's col and row
};

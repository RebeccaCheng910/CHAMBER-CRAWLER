#include <iostream>
#include "objectType.h"


class Info;

class Object {
  int row,col;
  char type;
public: 
  Object(char type); // constructor
  void setCords(int, int);  // set an object's col and row
  

  Info getInfo();  // return object's rol, col and info
};

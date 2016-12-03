#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>
#include "objectType.h"


class Info;

class Object {
  int row,col;
  char type;
public: 
  Object(int, int, char);
  virtual void setCords(int, int);  // set an object's col and row
  virtual Info getInfo() ;  // return object's rol, col and info
};

#endif

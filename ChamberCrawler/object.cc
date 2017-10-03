#include "object.h"
#include "objectType.h"
#include "info.h"


Object::Object(int row, int col, char type): row{row}, col{col},type{type} {
/*
  if (c == '-') || (c == '|') {
    ObjectType = WALL;
  } else if (c == '.') {
    ObjectType = TILE;
  } else if (c == '+') {
    ObjectType = DOOR;
  } else if (c == ' ') {
    ObjectType = SPACE;
  } else if (c == '#') {
    ObjectType = PASSAGE;
  } else if (c == '@') {
    ObjectType = PC;
  }
*/ 
}

// set an object's coort
void Object::setCords(int i, int j) {row = i; col = j;}


Info Object::getInfo() {
  Info x = {row, col, type};
  return x;
}
  

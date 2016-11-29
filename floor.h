#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <vector>
#include <memory>

class TextDisplay;
class Object;

class Floor {
  int row = 25;
  int col = 79;
  std::vector<std::vector<std::unique_ptr<Object>>> theGrid;
  TextDisplay *td;

public: 
  Floor(std::istream *); // constructor
  ~Floor();  // destructor
  friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};


#endif

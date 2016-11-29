#include <iostream>
#include <string>
#include "floor.h"

class Controller {
  Floor *floor;
public:
  Controller();  // constructor
  ~Controller();  // dextructor
  void startGame(std::string filename); // read in a file, and initilize Floor
  void printFloor(); // output the floor
};

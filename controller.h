#include <iostream>
#include <string>
#include "floor.h"

class Player;

class Controller {
  std::shared_ptr<Floor> floor;
  std::shared_ptr<Player> pc;
public:
  Controller();  // constructor
  ~Controller();  // dextructor
  void startGame(std::string filename); // read in a file, and initilize Floor
  void setRace(char);  // read from input and set race
  void printFloor(); // output the floor
};

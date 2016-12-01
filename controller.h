#include <iostream>
#include <string>
#include "floor.h"

class Player;

class Controller {
  bool useDefault;
  std::string file;
  std::shared_ptr<Floor> floor;
  std::shared_ptr<Player> pc;
public:
  Controller(bool, std::string);  // constructor
  ~Controller();  // dextructor
  void startGame(); // read in file, and initilize Floor
  void setRace(char);  // read from input and set race
  void setBoard();  // generate enemies and items
  void printFloor(); // output the floor
};

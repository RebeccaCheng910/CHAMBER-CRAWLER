#include <iostream>
#include <memory>
#include <string>

class Floor;
class Player;

class Controller {
  bool useDefault;
  int floorNum;   // current floor number
  std::string file;
  std::shared_ptr<Floor> floor;
  std::shared_ptr<Player> pc;
public:
  Controller(bool, std::string);  // constructor
  ~Controller();  // destructor
  void startGame(); // read in file, and initilize Floor
  void setRace(char);  // read from input and set race
  void setBoard();  // generate enemies and items
  bool move(bool, std::string);  // move the PC
  bool attack(std::string);
  bool usePotion(std::string);
  int getScore(); 
	void printFloor(); // output the floor
};

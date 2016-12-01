#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class TextDisplay;
class Object;
class Chamber;
class Player;
class Enemy;
class Gold;

class Floor {
  int row = 25;
  int col = 79;
  std::vector<std::vector<std::shared_ptr<Object>>> theGrid;
  std::vector<std::unique_ptr<Chamber>> theChambers;  // vector of 5 chamber
  std::shared_ptr<Player> pc;     // ptr to player character
  std::vector<std::shared_ptr<Enemy>> enemies;   //ptr to 20 enemies
  std::vector<std::shared_ptr<Gold>> gold;
	bool visited[25][79] ={{false}};    // check if the floor tile is added to Chamger
  std::shared_ptr<TextDisplay> td;

public: 
  Floor(std::string); // constructor
  ~Floor();  // destructor
  void findChamber();   //set up chambers, add objects to each chamber
  void findWall(int, int, int); // recursive call to add objects to chamber until hits wall
  void setPlayer(std::shared_ptr<Player> &); // set floor's pc
  void readFile(std::istream &) ; // read in from file and create objects
  friend std::ostream &operator<<(std::ostream &out, const Floor &f);
  char getTD(int, int); // get char in td with given position 
};


#endif

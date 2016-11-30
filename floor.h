#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <vector>
#include <memory>

class TextDisplay;
class Object;
class Chamber;

class Floor {
  int row = 25;
  int col = 79;
  std::vector<std::vector<std::shared_ptr<Object>>> theGrid;
  std::vector<std::unique_ptr<Chamber>> theChambers;  // vector of 5 chamber
  bool visited[25][79] ={{false}};    // check if the floor tile is added to Chamger
  TextDisplay *td;

public: 
  Floor(std::istream *); // constructor
  ~Floor();  // destructor
  void findChamber();   //set up chambers, add objects to each chamber
  void findWall(int, int, int); // recursive call to add objects to chamber until hits wall
  friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};


#endif

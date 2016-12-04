#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class TextDisplay;
class Object;
class Chamber;
class Character;
class Player;
class Enemy;
class Gold;
class Potion;

class Floor {
  int row = 25;
  int col = 79;
  int totalChamber = 5;
  int totalItem = 10;
  int totalEnemy = 20;
  std::vector<std::vector<std::shared_ptr<Object>>> theGrid;
  std::vector<std::unique_ptr<Chamber>> theChambers;  // vector of 5 chamber
  std::shared_ptr<Player> pc;     // ptr to player character
  std::shared_ptr<Object> stair;
  std::vector<std::shared_ptr<Enemy>> enemies;   //ptr to 20 enemies
  std::vector<std::shared_ptr<Gold>> golds;  // ptr to 10 golds
  std::vector<std::shared_ptr<Potion>> potions;  // ptr to 10 potions
  bool visited[25][79] ={{false}};    // check if the floor tile is added to Chamger
  std::shared_ptr<TextDisplay> td;
  
  void generatePotion();
  void generateGold();
  void generateEnemy();

  void moveObject(int, int, int, int, char, const std::shared_ptr<Enemy>&);
  template<typename T> T find(int, int, std::vector<T>);
  void enemiesAttack(int, int);
public: 
  Floor(std::string); // constructor
  ~Floor();  // destructor
  void findChamber();   //set up chambers, add objects to each chamber
  void findWall(int, int, int); // recursive call to add objects to chamber until hits wall
  void setPlayer(std::shared_ptr<Player> &); // set floor's pc
  void readFile(std::istream &) ; // read in from file and create objects
  void generate();  // random generate pc's position and enemies
<<<<<<< HEAD
  void moveEnemy();
  void movePlayer(int, int);  // move pc's position given direction
  std::shared_ptr<Player> &usePotion(int, int);   // use potion given direcion
=======
  void moveEnemy(int, int);
  void movePlayer(int, int, std::string);  // move pc's position given direction
  void attack(int, int); // attack enemy given direction
	void usePotion(int, int);   // use potion given direcion
>>>>>>> 93c56744b77410be029bad1955d22136461abc94
  friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};


#endif

#include "floor.h"
#include "textdisplay.h"
#include <iostream>
#include "object.h"
#include "chamber.h"
#include <memory>
#include <string>
#include <fstream>
#include "info.h"
#include "player.h"
#include "enemy.h"
#include "character.h"
#include "gold.h"
#include "potion.h"
#include <cstdlib>


using namespace std;


// constructor 
Floor::Floor(string filename) {
  ifstream file(filename); // opens the file and read
  istream *in = new ifstream(filename.c_str()); // read in file
  td = make_shared<TextDisplay>(in);
  // initialize vector of chamber pointers
  for (int i = 0; i < totalChamber; ++i) {
    theChambers.emplace_back(make_unique<Chamber>());
  }
  // initilize default objects without populated items
  for (int i = 0; i < row; ++i) {
    vector <shared_ptr<Object>> v;
    theGrid.emplace_back(v);
    string line;
    getline(file, line);
    for (int j = 0; j < col; ++j) {
      char c;
      if (line[j] >='0' && line[j] <='9') {
        c ='.';
      } else if (line[j] >= 'A' && line[j] <= 'Z') {
        c ='.';
      } else if (line[j] == '@' || line [j] =='\\') {
        c = '.';
      } else {
        c = line[j];
      }
      theGrid[i].emplace_back(make_shared<Object>(i,j,c));
    }
  }
  // initialize staircase
  stair = make_shared<Object>(0,0,'\\');
  // set up chamber
  findChamber();
} 

Floor::~Floor() {} 

// set Floor's PC, pass by reference
void Floor::setPlayer(shared_ptr<Player> &playerCharacter) {
  pc = playerCharacter;
  cout << " HP is " << pc->getHP() << endl;
}
  
// set up chamber, add floor tiles to chamber
void Floor::findChamber() {
  int chamberNum = 0;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (theGrid[i][j]->getInfo().type == '.' && visited[i][j] == false) {
        findWall (chamberNum, i, j); 
        ++chamberNum;
     }
   } 
 }
}

// recursive call, add Object ptr to Chamber until hit wall
void Floor::findWall(int chamberNum,int i, int j) {
  if (visited[i][j] == true || i < 0 || i > row || j < 0 || j > col) 
    return;
  visited[i][j] = true;
  if (theGrid[i][j]->getInfo().type != '.') return;
  if (theGrid[i][j]->getInfo().type == '.') { // add to Chamber
    theChambers[chamberNum]->addObjects(theGrid[i][j]);
  }
  findWall(chamberNum, i-1, j); // find upper
  findWall(chamberNum, i+1, j); // find below
  findWall(chamberNum, i, j-1); // find left
  findWall(chamberNum, i, j+1); /// find right
}


// read in from a file is a file exists and populates items and characters
void Floor::readFile(istream &in) {
  char c;
  string line;
  int enemyCount, goldCount, potionCount;

  for (int i = 0; i < row; ++i) {
    getline(in, line);
    for (int j = 0; j < col; ++j) {
     c = line[j];
      if (c == '@') {      
        pc->setCords(i, j);  // set PC's postion
      } else if (c == '\\') {  // set stair's position
        stair->setCords(i,j);
      } else  if (c == 'H') {
        enemies.emplace_back(make_shared<Enemy>(i, j));
        ++enemyCount;
      } else if (c == 'W') {
        enemies.emplace_back(make_shared<Enemy>(i,j));
        ++enemyCount;
      } else if (c == 'E') {
        enemies.emplace_back(make_shared<Enemy>(i,j));
        ++enemyCount;
      } else if (c == 'O') {
        enemies.emplace_back(make_shared<Enemy>(i,j));
        ++enemyCount;
      } else if (c == 'M') {
        enemies.emplace_back(make_shared<Enemy>(i, j));
        ++enemyCount;
      } else if (c == 'D') {
        enemies.emplace_back(make_shared<Enemy>(i,j));
        ++enemyCount;
      } else if (c == 'L') {
        enemies.emplace_back(make_shared<Enemy>(i, j));
        ++enemyCount;
      } else if (c == 0) {  // Restore Health
        potions.emplace_back(make_shared<Potion>(i, j, 0));
	++potionCount;
      } else if (c == 1) {  // Boost Attack 
	potions.emplace_back(make_shared<Potion>(i, j, 1));
	++potionCount;
      } else if (c == 2) {  // Boost Defence
	potions.emplace_back(make_shared<Potion>(i, j, 2));
	++potionCount;
      } else if (c == 3) {  // Poison Health
	potions.emplace_back(make_shared<Potion>(i, j, 3));
	++potionCount;
      } else if (c == 4) {   // Wound Attack
	potions.emplace_back(make_shared<Potion>(i, j,  4));
	++potionCount;
      } else if (c == 5) {   // Wound Defence
 	potions.emplace_back(make_shared<Potion>(i, j,  5));
	++potionCount;
      } else if (c == 6) {  // nomal gold pile
	golds.emplace_back(make_shared<Gold>(i, j, 0));
	++goldCount;
      } else if (c == 7) {  // small hoard
	golds.emplace_back(make_shared<Gold>(i, j, 7));
	++goldCount; 
	} else if (c == 8) {  // merchant hoard
        golds.emplace_back(make_shared<Gold>(i, j, 10));
	++goldCount;
			} else if (c == 9) {   // dragon hoard
				golds.emplace_back(make_shared<Gold>(i, j, 5));
        ++goldCount;
     }
   }
 }
  /* check enemy's position
  cout << "enemy's size is " << enemies.size() << endl;
  for (int i = 0; i < enemies.size(); ++i) {
    cout << "position is " << enemies[i]->getInfo().row << " " << enemies[i]->getInfo().col << endl;
  } 
 */
  /* check gold's position
   cout << "gold's size is " << gold.size() << endl;
   for (int i = 0; i < gold.size(); ++i) {
     cout << "position is " << gold[i]->getInfo().row << " " << gold[i]->getInfo().col << endl;
   } 
  */
}
 

// a file does not exist, random generate enemies and items
void Floor::generate() {
  //generate pc's location
  const int pcChamber = rand() % totalChamber;
  int stairChamber;
  do {
    stairChamber = rand() % totalChamber;
  } while (stairChamber == pcChamber);
  // cout <<  " pc in chamber:"  << pcChamber << endl;   // DEBUG
  // set pc's position
  theChambers[pcChamber]->generatePosition(pc.get());
  // cout << "PC's position" << pc->getInfo().row << " " << pc->getInfo().col << endl;  //DEBUG
  td->setTD(pc->getInfo().row, pc->getInfo().col, pc->getInfo().type);
  // generate stair's location
  theChambers[stairChamber]->generatePosition(stair.get());
  // cout << "stair's position" << stair->getInfo().row << " " << stair->getInfo().col << endl;  //DEBUG
  td->setTD(stair->getInfo().row, stair->getInfo().col, stair->getInfo().type); 
  generatePotion();    // generate potion
  generateGold();
  generateEnemy();
}

void Floor::generatePotion() {
  int potionChamber;
  int potionType;
  for (int i = 0; i < totalItem; ++i) {
    potionChamber = rand() % totalChamber;
    potionType = rand() % 6;
   // cout << "type is " << potionType << endl;     //DeBUG
    potions.emplace_back(make_shared<Potion>(0,0,potionType));
    theChambers[potionChamber]->generatePosition(potions[i].get());
    td->setTD(potions[i]->getInfo().row, potions[i]->getInfo().col, potions[i]->getInfo().type);
  }
}
   
    
void Floor::generateGold() {
  int goldChamber;
  int goldType;
  for (int i = 0; i < totalItem; ++i) {
    goldChamber = rand() % totalChamber;
    goldType = rand() % 8;
    golds.emplace_back(make_shared<Gold>(0,0,goldType));
    theChambers[goldChamber]->generatePosition(golds[i].get());
    td->setTD(golds[i]->getInfo().row, golds[i]->getInfo().col, golds[i]->getInfo().type);
  }
}

// generate enemies without specialized type
void Floor::generateEnemy() {
  int enemyChamber;
	int enemyType;
  for (int i = 0; i < totalEnemy; ++i) {
    enemyChamber = rand() % totalChamber;
    enemyType = rand() % 18;
    enemies.emplace_back(make_shared<Enemy>(0,0));
    theChambers[enemyChamber]->generatePosition(enemies[i].get());
    td->setTD(enemies[i]->getInfo().row, enemies[i]->getInfo().col, enemies[i]->getInfo().type);
   }
 }

// find pointer to Enemy with given row and col 
shared_ptr<Enemy> Floor::getEnemy(int row, int col) {
   int size = enemies.size();
   for (int i = 0; i < size; ++i) {
     if ((enemies[i]->getInfo().row == row) && (enemies[i]->getInfo().col == col)) {
       return enemies[i];
     }
	}
     return nullptr;
}

 
// move all enemies starts from leftmost and upmost
void Floor::moveEnemy() {
  for (auto it = enemies.begin(); it < enemies.end(); ++it) {
		(*it)->setMove(false);
  }
   char c = '.';
   for (int i = 0; i < row; ++i) {
     for (int j = 0; j < col; ++j) {
				 char symbol = td->getTD(i, j);
         if ((symbol == 'H')||(symbol == 'W')||(symbol == 'E')||(symbol == 'O')||(symbol == 'M')||(symbol == 'L')) {
            shared_ptr <Enemy> e = getEnemy(i, j);
						vector <int> directions;
            // cout << "enemy's current position: " << i << " " << j << endl;
             if (e != nullptr && e->getMove() != true) {                              
								if (td->getTD(i,j+1) == c) {
                 directions.emplace_back(0);  // west
                }
								if (td->getTD(i,j-1) == c) {
                 directions.emplace_back(1);  // east
                } 
								if (td->getTD(i+1,j) == c) {
                 directions.emplace_back(2);  // south
                }
								if (td->getTD(i-1,j) == '.') {
                 directions.emplace_back(3);  // north
                } 
								if (td->getTD(i-1,j+1) == c) {
                 directions.emplace_back(4);  // ne
                } 
								if (td->getTD(i+1,j+1) == c) {
                 directions.emplace_back(5);  // se
                } 
								if (td->getTD(i-1,j-1) == c) {
                 directions.emplace_back(6);  // nw
                }
								if (td->getTD(i+1,j-1) == c) {
                 directions.emplace_back(7);  // sw
								}
						int size = directions.size();
						if (size != 0) { 
							int randomDir = directions[rand() % size];
            	int x = i;
            	int y = j;
							if (randomDir == 0) {y++;}
							else if (randomDir == 1) {y--;}
            	else if (randomDir == 2) {x++;}
							else if (randomDir == 3) {x--;}
							else if (randomDir == 4) {x--; y++;}
							else if (randomDir == 5) {x++; y++;}
            	else if (randomDir == 6) {x--; y--;}
            	else if (randomDir == 7) {x++; y--;}
							moveObject(i,j,x,y,symbol,e);
				  }
				} 
			}
	 }
 }
}

						

// move objects to given row and col 
void Floor::moveObject(int old_x, int old_y, int new_x, int new_y, char symbol, const shared_ptr<Enemy>&e) {
	td->setTD(old_x, old_y, '.');
	td->setTD(new_x, new_y, symbol);
	e->setCords(new_x, new_y);
  e->setMove(true);
}
  	

// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}


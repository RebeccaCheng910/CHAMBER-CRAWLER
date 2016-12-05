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
#include <stdexcept>
#include "potioneffect.h"

using namespace std;


// constructor 
Floor::Floor(string filename) {
  ifstream file(filename); // opens the file and read
  ifstream in{filename}; // read in file
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
      } else if (c == '0') {  // Restore Health
        potions.emplace_back(make_shared<Potion>(i, j, 0));
	++potionCount;
      } else if (c == '1') {  // Boost Attack 
	potions.emplace_back(make_shared<Potion>(i, j, 1));
	++potionCount;
      } else if (c == '2') {  // Boost Defence
	potions.emplace_back(make_shared<Potion>(i, j, 2));
	++potionCount;
      } else if (c == '3') {  // Poison Health
	potions.emplace_back(make_shared<Potion>(i, j, 3));
	++potionCount;
      } else if (c == '4') {   // Wound Attack
	potions.emplace_back(make_shared<Potion>(i, j,  4));
	++potionCount;
      } else if (c == '5') {   // Wound Defence
 	potions.emplace_back(make_shared<Potion>(i, j,  5));
	++potionCount;
      } else if (c == '6') {  // nomal gold pile
	golds.emplace_back(make_shared<Gold>(i, j, 0));
	++goldCount;
      } else if (c == '7') {  // small hoard
	golds.emplace_back(make_shared<Gold>(i, j, 7));
	++goldCount; 
      } else if (c == '8') {  // merchant hoard
        golds.emplace_back(make_shared<Gold>(i, j, 10));
	++goldCount;
	} else if (c == '9') {   // dragon hoard
				golds.emplace_back(make_shared<Gold>(i, j, 5));
        ++goldCount;
     }
   }
 }
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
    if (golds[i]->getValue() == 6) {generateDragon(golds[i]->getInfo().row, golds[i]->getInfo().col);}
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

// generate dragons and store in a vector 
void Floor::generateDragon(int x, int y) {
  for (int i = x-1; i <= x+1; ++i) {
		for (int j = y-1; j <= y+1; ++j) {
			if (td->getTD(i, j) == '.') {
				dragons.emplace_back(make_shared<Enemy>(i,j));
				td->setTD(i, j, 'D');
        return;
			}
		}
	}
}

// find pointer in a vector given row and col
template<typename T> T Floor::find(int row, int col, vector<T> v) {
   for (auto it = v.begin(); it != v.end(); ++it) {
		if ((*it) == nullptr) break;
		char c = td->getTD(row, col);
    if (((*it)->getInfo().row == row) && ((*it)->getInfo().col == col) && (c != '.')) {
				return *it;
     }
   } 
    return nullptr;
}
				
 
// move all enemies starts from leftmost and upmost
void Floor::moveEnemy(int x, int y) {
  for (auto it = enemies.begin(); it < enemies.end(); ++it) {
		if (*it) {(*it)->setMove(false);}
  }

  if ((x == 0) && (y == 0)) {}
  else  {
	int row = pc->getInfo().row;
	int col = pc->getInfo().col;
	shared_ptr <Enemy> noMove = find<shared_ptr<Enemy>>(row+x, col+y, enemies);
	if (noMove) {noMove->setMove(true);} // Enemy will not move if it is in a combat
  }
  
  char c = '.';
   for (int i = 0; i < row; ++i) {
     for (int j = 0; j < col; ++j) {
		 char symbol = td->getTD(i, j);
         if ((symbol == 'H')||(symbol == 'W')||(symbol == 'E')||(symbol == 'O')||(symbol == 'M')||(symbol == 'L')) {
            shared_ptr <Enemy> e = find<shared_ptr<Enemy>>(i, j, enemies);
		 vector <int> directions;
            // cout << "enemy's current position: " << i << " " << j << endl;
             if (e && e->getMove() != true) {                              
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

// check player in range for attack 
template<typename T> void Floor::enemiesAttack(int x, int y, vector<T> v) {
	for (int i = x-1;i <= x+1; ++i) {
		for (int j = y-1; j <= y+1; ++j) {
			shared_ptr <Enemy> e = find<shared_ptr<Enemy>>(i, j, v);
			if (e) {
				pc->beAttackedBy(e);
        return;
		  }
		} 
	}
} 


// move pc according to command of game players (no, so, ea, we,ne, nw, se, sw) 
void Floor::movePlayer(int new_x, int new_y, string dir) {
	int x = pc->getInfo().row;
  int y = pc->getInfo().col;
  char c = td->getTD(x + new_x, y + new_y);
  string actionStr = "";
  if (c == '\\') {
		int err = 1;
		throw err;
		td->setTD(x, y, '.');
	} else if ((c == '.') || (c == '#') || (c == '+') || (c == 'G')) {
		// if G is in given direction 
		if (c == 'G') {
			shared_ptr <Gold> g = find<shared_ptr<Gold>>(x+new_x, y+new_y, golds);
			if (g && (g->getGold() == false)) {
				// dragon hoard is not protected 
				int val = g->getValue();  // gold value
        string name;   // gold description
				pc->setGold(pc->getGold() + val);
        if (val == 2) name = "normal pile";
        else if (val == 1) name = "small hoard";
        else if (val == 5) name = "dragon hoard";
        else if (val == 4) name = "merchant hoard";
        g = nullptr;
        actionStr = "A " + name + " is picked up. ";
			}
			else {enemiesAttack(x, y, dragons);}
    }
    td->setTD(x + new_x, y + new_y, '@');
		char original = theGrid[x][y]->getInfo().type;
		td->setTD(x, y, original);
    pc->setCords(x + new_x, y + new_y);
		actionStr += "PC moves " + dir;
		pc->setAction(actionStr);
		moveEnemy(0,0);
		for (int i = x+new_x-1; i <= x+new_x+1; ++i) {
			for (int j = y+new_y-1; j <= y+new_y+1; ++j) {
			  if (td->getTD(i,j) == 'G') {
				  shared_ptr <Gold> g = find<shared_ptr<Gold>>(i, j, golds);
				  if (g->getGold() == true) {      // if PC is within 1 radius of dragon hoard
				  pc->setAction(pc->getAction() + " and attacked by a nearby Dragon. ");
					enemiesAttack(i, j, dragons);
          return;
				  }
			  } else if (td->getTD(i,j) == 'D') {       // if PC is within 1 radius of dragon 
					pc->setAction(pc->getAction() + ". ");
					enemiesAttack(i, j, dragons); 
					return;
        }
				if (td->getTD(i,j) == 'P') {
          pc->setAction(pc->getAction() + " and sees an unknown portion");
          break; 
				}
		  } 
		}
		
		pc->setAction(pc->getAction() + ". ");
    enemiesAttack(x + new_x, y + new_y, enemies);
    
	} else pc->setAction("Invalid direction, PC's way is blocked.");
}


// move each enemy to given position
void Floor::moveObject(int old_x, int old_y, int new_x, int new_y, char symbol, const shared_ptr<Enemy>&e) {
	td->setTD(old_x, old_y, '.');
	td->setTD(new_x, new_y, symbol);
	e->setCords(new_x, new_y);
        e->setMove(true);
}


// attack Enemy given direction 
void Floor::attack(int x, int y) {
	int row = pc->getInfo().row;
  int col = pc->getInfo().col;
  shared_ptr <Enemy> e;
  if (td->getTD(row+x, col+y) == 'G') {
		e = find<shared_ptr<Enemy>>(row+x, col+y,dragons);
  } else { 
	  e = find<shared_ptr<Enemy>>(row+x, col+y, enemies);
	}
	if (e) { 
		bool dead = e->beAttackedBy(pc);
    
		if (dead) {
			pc->setAction(pc->getAction() + e->getInfo().type + " is slained.");
			td->setTD(e->getInfo().row, e->getInfo().col, '.'); 
			e = nullptr;
		} else {
      moveEnemy(x, y);
			pc->beAttackedBy(e);
		}
	} 
	else {
		pc->setAction("Enemy not found.");
	}
}



// use Potion given direction
shared_ptr<Player> &Floor::usePotion(int x, int y) {
  // return Pc's current position
  int row = pc->getInfo().row;
  int col = pc->getInfo().col;
  // get potion's position
  int p_row = row + x;
  int p_col = col + y;
  if (td->getTD(row+x, col+y) != 'P') {
    pc->setAction("Potion not found.");
  } else {
    shared_ptr<Potion> p = find<shared_ptr<Potion>>(p_row, p_col, potions);
    pc = make_shared<PotionEffect>(p->getType(),pc);
    td->setTD(p_row, p_col, theGrid[p_row][p_col]->getInfo().type);
    pc->setAction("PC used a potion(" + p->getName() + ").");
  }
  return pc;
}





// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}


#include "floor.h"
#include "textdisplay.h"
#include <iostream>
#include <sstream>
#include "object.h"
#include "chamber.h"
#include <memory>
#include <string>
#include <fstream>
#include "info.h"
#include "player.h"
#include "enemy.h"
#include "dragon.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orcs.h"
#include "halfling.h"
#include "merchant.h"
#include "character.h"
#include "gold.h"
#include "potion.h"
#include <cstdlib>
#include <stdexcept>
#include "potioneffect.h"
#include "RH.h"
#include "BA.h"
#include "BD.h"
#include "PH.h"
#include "WA.h"
#include "WD.h"

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
        enemies.emplace_back(make_shared<Human>(i,j,'H'));
        ++enemyCount;
      } else if (c == 'W') {
        enemies.emplace_back(make_shared<Dwarf>(i,j,'W'));
        ++enemyCount;
      } else if (c == 'E') {
        enemies.emplace_back(make_shared<Elf>(i,j,'E'));
        ++enemyCount;
      } else if (c == 'O') {
        enemies.emplace_back(make_shared<Orcs>(i,j,'O'));
        ++enemyCount;
      } else if (c == 'M') {
        enemies.emplace_back(make_shared<Merchant>(i,j,'M'));
        ++enemyCount;
      } else if (c == 'D') { 
        dragons.emplace_back(make_shared<Dragon>(i,j,'D'));
      } else if (c == 'L') {
        enemies.emplace_back(make_shared<Halfling>(i,j,'L'));
        ++enemyCount;
      } else if (c == '0') {  // Restore Health
        potions.emplace_back(make_shared<RH>(i, j));
	++potionCount;
      } else if (c == '1') {  // Boost Attack 
	potions.emplace_back(make_shared<BA>(i, j));
	++potionCount;
      } else if (c == '2') {  // Boost Defence
	potions.emplace_back(make_shared<BD>(i, j));
	++potionCount;
      } else if (c == '3') {  // Poison Health
	potions.emplace_back(make_shared<PH>(i, j));
	++potionCount;
      } else if (c == '4') {   // Wound Attack
	potions.emplace_back(make_shared<WA>(i, j));
	++potionCount;
      } else if (c == '5') {   // Wound Defence
 	potions.emplace_back(make_shared<WD>(i, j));
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
    if (potionType == 0) {potions.emplace_back(make_shared<RH>(0,0));}
    else if (potionType == 1) {potions.emplace_back(make_shared<BA>(0,0));}
    else if (potionType == 2) {potions.emplace_back(make_shared<BD>(0,0));}
    else if (potionType == 3) {potions.emplace_back(make_shared<PH>(0,0));}
    else if (potionType == 4) {potions.emplace_back(make_shared<WA>(0,0));}
    else if (potionType == 5) {potions.emplace_back(make_shared<WD>(0,0));}
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
	int t;
  for (int i = 0; i < totalEnemy; ++i) {
    enemyChamber = rand() % totalChamber;
    t = rand() % 18;
		if ((t >= 0) && (t <= 3)) {enemies.emplace_back(make_shared<Human>(0,0,'H'));}
    else if ((t == 4) || (t == 5) || (t == 6)) {enemies.emplace_back(make_shared<Dwarf>(0,0,'W'));} 
    else if ((t >= 7) && (t <= 11)) {enemies.emplace_back(make_shared<Halfling>(0,0,'L'));}
    else if ((t == 12) || (t == 13)) {enemies.emplace_back(make_shared<Elf>(0,0,'E'));}
		else if ((t == 14) || (t == 15)) {enemies.emplace_back(make_shared<Orcs>(0,0,'O'));}
		else if ((t == 16) || (t == 17)) {enemies.emplace_back(make_shared<Merchant>(0,0,'M'));}
    theChambers[enemyChamber]->generatePosition(enemies[i].get());
    td->setTD(enemies[i]->getInfo().row, enemies[i]->getInfo().col, enemies[i]->getInfo().type);
   }
 }

// generate dragons and store in a vector 
void Floor::generateDragon(int x, int y) {
  for (int i = x-1; i <= x+1; ++i) {
		for (int j = y-1; j <= y+1; ++j) {
			if (td->getTD(i, j) == '.') {
				dragons.emplace_back(make_shared<Dragon>(i,j,'D'));
				shared_ptr <Gold> g = find<shared_ptr<Gold>>(x, y, golds);
				     shared_ptr <Dragon> d = find<shared_ptr<Dragon>>(i, j, dragons);
				     if (g) d->setHoard(g);
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
				
// controls movement of enemies 

 
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
				// Merchant
				if (e->getInfo().type == 'M') {
          shared_ptr <Merchant> m = dynamic_pointer_cast<Merchant>(e);
					if (m->getHostility() == true) {
						pc->beAttackedBy(e);
				  	return;
					}
				} else {
				pc->beAttackedBy(e);
        return;
				}
		  }
		} 
	}
} 

void Floor::dragonsAttack(int x, int y) {
		for (int i = x-1;i <= x+1; ++i) {
			for (int j = y-1; j <= y+1; ++j) {
				shared_ptr <Dragon> d = find<shared_ptr<Dragon>>(i, j, dragons);
				if (d) {
					pc->beAttackedBy(d);
					return;
				}
			}
		}
}


// move pc according to command of game players (no, so, ea, we,ne, nw, se, sw) 
void Floor::movePlayer(bool move, int new_x, int new_y, string dir) {
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
			else {dragonsAttack(x, y);}
    }
    td->setTD(x + new_x, y + new_y, '@');
		char original = theGrid[x][y]->getInfo().type;
		td->setTD(x, y, original);
    pc->setCords(x + new_x, y + new_y);
		actionStr += "PC moves " + dir;
		pc->setAction(actionStr);
		if (move) moveEnemy(0,0);

		for (int i = x+new_x-1; i <= x+new_x+1; ++i) {
			for (int j = y+new_y-1; j <= y+new_y+1; ++j) {
			  if (td->getTD(i,j) == 'G') {
				  shared_ptr <Gold> g = find<shared_ptr<Gold>>(i, j, golds);
				  if (g->getGold() == true) {      // if PC is within 1 radius of dragon hoard
				  pc->setAction(pc->getAction() + " and attacked by a nearby Dragon. ");
					dragonsAttack(i, j);
          return;
				  }
			  } else if (td->getTD(i,j) == 'D') {       // if PC is within 1 radius of dragon 
					pc->setAction(pc->getAction() + ". ");
					dragonsAttack(i, j); 
					return;
        }
				if (td->getTD(i,j) == 'P') {
          // check if pc has used this type of potion
          shared_ptr<Potion> p = find(i, j, potions);
          bool known;
   	  string p_type;
          if (shared_ptr<RH> temp = dynamic_pointer_cast<RH>(p)) {
                known = temp->isKnown();
               // temp->setKnown();
    		p_type = temp->getName();
         } else if (shared_ptr<BA> temp = dynamic_pointer_cast<BA>(p)){
                known = temp->isKnown();
		p_type = temp->getName();
         } else if (shared_ptr<BD> temp = dynamic_pointer_cast<BD>(p)){
		known = temp->isKnown();
		p_type = temp->getName();
	} else if (shared_ptr<PH> temp = dynamic_pointer_cast<PH>(p)){
		known = temp->isKnown();
		p_type = temp->getName();
 	}else if (shared_ptr<WA> temp = dynamic_pointer_cast<WA>(p)){
		known = temp->isKnown();
		p_type = temp->getName();
	} else if (shared_ptr<WD> temp = dynamic_pointer_cast<WD>(p)){
		known = temp->isKnown();
		p_type = temp->getName();
	}
         if (known != true) {
         	 pc->setAction(pc->getAction() + " and sees an unknown potion");
                } else {
		pc->setAction(pc->getAction() + " and sees a potion(" + p_type + "). u <direction> to use the potion.");
                }

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
   int type = td->getTD(row+x, col+y);
   if ((type == 'W') || (type == 'O') || (type == 'L') || (type == 'M') || (type == 'H')) {
     shared_ptr <Enemy> e = find<shared_ptr<Enemy>>(row+x, col+y,enemies);
     if (e) {
     	bool dead = e->beAttackedBy(pc);
     	char symbol = e->getInfo().type;
        // attack Merchant, all Merchant becomes hostile
        if (symbol == 'M') {
        shared_ptr <Merchant> m = dynamic_pointer_cast<Merchant>(e);
        m->setHostility(true);
        pc->setAction(pc->getAction() + "Merchants are now hostile. ");
        }
        if (dead) { 
        	pc->setAction(pc->getAction() + symbol + " is slained.");
         	td->setTD(row+x, col+y, '.');
         	// if slained Enemy is Human, drops 2 normal piles of Gold  
          if (symbol == 'H') {
         	int count = 0;
         	while (count < 2 ) {
           		int generate_x = rand()% 25;
           		int generate_y = rand()% 79;
           		if (td->getTD(generate_x, generate_y) == '.') {
             		count++;
             		golds.emplace_back(make_shared<Gold>(generate_x,generate_y,0));  // 2 normal pile generated
             		td->setTD(generate_x,generate_y,'G');
           		}
         	}
					 pc->setAction(pc->getAction() + " Two piles of normal gold generated.");
       	   } // if slained Enemy is Merchant, drops a merchant hoard
     		else if (symbol == 'M') {
       			golds.emplace_back(make_shared<Gold>(row+x,col+y,10));   // 1 merchant hoard generated
       			td->setTD(row+x,col+y,'G');
     		} // if slained Enemy is not Human, Dragon or Merchant, pickes up 1 normal or small pile of Gold
              else {
        		int add = rand() % 2;
            	pc->setGold(add + 1);   // small(1) or normal(2) pile 
         		stringstream s;
         		s << " Gold value increase " << (add+1) << ".";                                                                                          
         		pc->setAction(pc->getAction() + s.str());
     		   }
     		   e = nullptr;
     	    } else {
						moveEnemy(x,y);
						enemiesAttack(row+x, col+y, enemies);
     	    } 
			  }
			} else if (type == 'D') { 
     		shared_ptr<Dragon> g = find<shared_ptr<Dragon>>(row+x, col+y, dragons); 
     		if (g) {
     			bool dead = g->beAttackedBy(pc);
     			if (dead) {
						pc->setAction(pc->getAction() + g->getInfo().type + " is slained.");
     			  shared_ptr<Gold> d = g->getHoard();
						if (d) d->setGold(false);
						td->setTD(row+x, col+y, '.');
     		  } else {
					 	 moveEnemy(0,0);
						 dragonsAttack(row+x, col+y);
				}
			}
    } else {
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
    pc->setAction("PC used a potion (" + p->getName() + ").");
    if (shared_ptr<RH> temp = dynamic_pointer_cast<RH>(p)){
	 temp->setKnown();
    } else if (shared_ptr<BA> temp = dynamic_pointer_cast<BA>(p)) {
         temp->setKnown();
    } else if (shared_ptr<BD> temp = dynamic_pointer_cast<BD>(p)) {
     	temp->setKnown();
    } else if (shared_ptr<PH> temp = dynamic_pointer_cast<PH>(p)) {
  	 temp->setKnown();
   } else if (shared_ptr<WA> temp = dynamic_pointer_cast<WA>(p)) {
     temp->setKnown();
   } else if (shared_ptr<WD> temp = dynamic_pointer_cast<WD>(p)) {
     temp->setKnown();
  }
 }
  return pc;
}



// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}

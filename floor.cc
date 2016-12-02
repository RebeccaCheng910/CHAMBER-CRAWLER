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
        potions.emplace_back(make_shared<Potion>(i, j, '.', 0));
				++potionCount;
			} else if (c == 1) {  // Boost Attack 
				potions.emplace_back(make_shared<Potion>(i, j, '.', 1));
				++potionCount;
			} else if (c == 2) {  // Boost Defence
				potions.emplace_back(make_shared<Potion>(i, j, '.',2));
			  ++potionCount;
			} else if (c == 3) {  // Poison Health
				potions.emplace_back(make_shared<Potion>(i, j, '.', 3));
				++potionCount;
			} else if (c == 4) {   // Wound Attack
				potions.emplace_back(make_shared<Potion>(i, j, '.', 4));
				++potionCount;
			} else if (c == 5) {   // Wound Defence
 				potions.emplace_back(make_shared<Potion>(i, j, '.', 5));
				++potionCount;
      } else if (c == 6) {  // nomal gold pile
				golds.emplace_back(make_shared<Gold>(i, j, '.', 2, true));
				++goldCount;
			} else if (c == 7) {  // small hoard
				golds.emplace_back(make_shared<Gold>(i, j, '.', 1, true));
				++goldCount; 
			} else if (c == 8) {  // merchant hoard
				golds.emplace_back(make_shared<Gold>(i, j, '.', 4, true));
				++goldCount;
			} else if (c == 9) {   // dragon hoard
				golds.emplace_back(make_shared<Gold>(i, j, '.', 6, false));
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
void Floor:: generate() {
  //generate pc's location
  const int pcChamber = rand() % totalChamber;
  int stairChamber;
  do {
    stairChamber = rand() % totalChamber;
  } while (stairChamber == pcChamber);
  cout <<  " pc in chamber:"  << pcChamber << endl;   // DEBUG
  // set pc's position
  theChambers[pcChamber]->generatePosition(pc.get());
  cout << "PC's position" << pc->getInfo().row << " " << pc->getInfo().col << endl;  //DEBUG
  td->setTD(pc->getInfo().row, pc->getInfo().col, pc->getInfo().type);
}



// check character in td given row and col
char Floor::getTD (int x, int y) {
	return td->getTD(x, y);
}



// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}


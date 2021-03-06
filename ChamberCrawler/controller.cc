#include "controller.h"
#include <string>
#include <iostream>
#include "floor.h"
#include <fstream>
#include <sstream>
#include <memory>
#include "character.h"
#include "shade.h"
#include <tuple>
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

using namespace std;


// convert direction to a pair of inte(x, y)
tuple<int, int, string> convert_direc(string direction) {
  int x,y;
  string s;
  
   if (direction == "no") {
     x = -1; y = 0; s = "North";
   } else if (direction =="so")  {
     x = 1; y = 0; s = "South";
   } else if (direction == "ea") {
     x = 0; y = 1; s = "East";
   } else if (direction == "we") {
     x = 0 ; y = -1; s = "West";
   } else if (direction == "ne") {
     x = -1; y = 1; s = "NE";
   } else if (direction == "nw") {
     x = -1; y = -1; s = "NW";
   } else if (direction == "se") {
     x = 1; y = 1; s = "SE";
   } else if (direction == "sw") { 
     x = 1; y = -1; s = "SW";
   } else {   // invalid direction 
     x= 0; y = 0; s = "";
  }
  return make_tuple(x,y,s);
}

// constructor
Controller::Controller(bool useDefault, string fileName):useDefault{useDefault}, file{fileName} {
  floor = nullptr;
  pc = nullptr;
  floorNum = 1;
}

// opens a file and initilize a game
void Controller::startGame() {
  for (int i = 0; i < 10; ++i) {
    cout << endl;
  }
  cout << "Welcome to CC3K." << endl;
  for (int i = 0; i < 5; ++i) {
    cout << endl;
	}
  cout << "Please choose a race" << endl;
  cout << "s - Shade" << endl;
  cout << "d - Drow" << endl;
  cout << "v - Vampire" << endl;
  cout << "g - Grblic" << endl;
  cout << "t - Troll" << endl;
  floor = make_shared<Floor>(file);
}

Controller::~Controller() {
}

// set a PC with no specialized type
void Controller::setRace(char c) {
  if (c == 'd') {
    pc = make_shared<Drow>(); //
  } else if ( c == 'v') {
    pc = make_shared<Vampire>();  //
  } else if (c == 't') {
    pc = make_shared<Troll>();
  } else if (c == 'g') {
    pc = make_shared<Goblin>();
  } else {        // use Shade as default
    pc = make_shared<Shade>();
  }
  floor->setPlayer(pc);  // set floor's  pc
}


// generate enemies if file exists, or consturct enemies if file does not exist
void Controller::setBoard(){
  if (! useDefault) {
    ifstream in{file};
    floor->readFile(in);
  } else { // a file does not exist, random generate
    floor->generate();
  }
}

 
void Controller::printFloor() {
  cout << *floor;
  cout << "Race: " << pc->getRace();
  cout << " Gold: " << pc->getGold();
  for (int i = 0; i < 45; ++i) { 
    cout << " ";
  }
  cout << "Floor " << floorNum << endl;
  cout << "HP: " << pc->getHP() << endl;
  cout << "Atk: " << pc->getAtk() << endl;
  cout << "Def: " << pc->getDef() << endl;
  cout << "Action: " << pc->getAction() << endl;
}

bool Controller::move(bool move, string direction) {
  tuple<int,int,string> p = convert_direc(direction);
  try {
    floor->movePlayer(move, get<0>(p), get<1>(p), get<2>(p));
  } catch( const int n) {  // pc reaches staircase
    ++floorNum;
    // Player won
    if (floorNum > 5) {
			floorNum = 5; 
      stringstream s;
      s << "PC has won with a score of ";
      int score = getScore();
      s << score << ". Congratulations! ";
      printFloor();
			return false;
		}
			
    // create a new board
    floor = make_shared<Floor>(file);
    floor->setPlayer(pc);   // set floor's PC
    setBoard();
    floor = make_shared<Floor>(file);
    int temp_HP = pc->getHP();
    pc = pc->getBase();
    pc->setHP(temp_HP);
    floor->setPlayer(pc);
    setBoard();
    pc->setAction("PC reaches a new floor.");
  }
  if (pc->getStatus()) {pc->setAction(pc->getAction() + "PC is defeated by Enemy.");}
  printFloor();
  return (!pc->getStatus());
}

// attack enemy in given direction 
bool Controller::attack(string direction) {
  tuple<int, int, string> p = convert_direc(direction);
    if (get<0>(p) == 0 && get<1>(p) == 0) {
      pc->setAction("Invalid direction");
    }  else {
		floor->attack(get<0>(p), get<1>(p));
    if (pc->getStatus()) {
			pc->setAction(pc->getAction() + "PC is defeated by Enemy.");
		}
	}
	printFloor();
  return (!pc->getStatus());
}


// use potion in direction
bool Controller::usePotion(string direction)  {
  tuple<int, int, string> p = convert_direc(direction);
  bool success = true;
  if (get<0>(p) == 0 && get<1>(p) == 0) {
    pc->setAction("Invalid direction");
  } else {
    pc = floor->usePotion(get<0>(p), get<1>(p));
    if (pc->getStatus()) {
			pc->setAction("PC is poisoned by Potion to death.");
			success = false;
     }
  }
  printFloor();
  return success;
}

// get player's score and return to main 
int Controller::getScore() {
	int score;
	if (pc->getRace() == "Shade") {
		score = pc->getGold() * 1.5;
	} else {score = pc->getGold();}
	return score;
}





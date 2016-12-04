#include "controller.h"
#include <string>
#include <iostream>
#include "floor.h"
#include <fstream>
#include <memory>
#include "character.h"
#include "shade.h"
#include <tuple>

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
    pc = make_shared<Shade>(); //
  } else if ( c == 'v') {
    pc = make_shared<Shade>();  //
  } else if (c == 't') {
    pc = make_shared<Shade>();
  } else if (c == 'g') {
    pc = make_shared<Shade>();
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

void Controller::move(string direction) {
  tuple<int,int,string> p = convert_direc(direction);
  try {
  	floor->movePlayer(get<0>(p), get<1>(p), get<2>(p));
  } catch( const int n) {  // pc reaches staircase
    ++floorNum;
                  //
  }
  printFloor();
}

// attack enemy in gievn direction 
bool Controller::attack(string direction) {
	tuple<int, int, string> p = convert_direc(direction);
	bool success = true;
	if (get<0>(p) == 0 && get<1>(p) == 0) {
    pc->setAction("Invalid direction");
	} else {
		floor->attack(get<0>(p), get<1>(p));
    if (!pc->getStatus()) {
    	floor->moveEnemy(get<0>(p), get<1>(p));
		} else {
			pc->setAction("You are Dead.");
			success = false;
		}
	}
	printFloor();
  return success;
}


// use potion in direction
bool Controller::usePotion(string direction)  {
  tuple<int, int, string> p = convert_direc(direction);
	bool success = true;
  if (get<0>(p) == 0 && get<1>(p) == 0) {
    pc->setAction("Invalid direction");
  } else {
<<<<<<< HEAD
    pc = floor->usePotion(p.first, p.second);
  }
=======
    floor->usePotion(get<0>(p), get<1>(p));
		if (pc->getStatus()) {
			pc->setAction("You are Dead.");
			success = false;
			
  	}
	}
>>>>>>> 93c56744b77410be029bad1955d22136461abc94
  printFloor();
	return success;
} 

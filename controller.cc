#include "controller.h"
#include <string>
#include <iostream>
#include "floor.h"
#include <fstream>
#include <memory>
#include "character.h"
#include "shade.h"

using namespace std;


// convert direction to a pair of inte(x, y)
pair<int, int> convert_direc(string direction) {
  int x,y;
   if (direction == "no") {
     x = -1; y = 0;
   } else if (direction =="so")  {
     x = 1; y = 0;
   } else if (direction == "ea") {
     x = 0; y = 1;
   } else if (direction == "we") {
     x = 0 ; y = -1;
   } else if (direction == "ne") {
     x = -1; y = 1;
   } else if (direction == "nw") {
     x = -1; y = -1;
   } else if (direction == "se") {
     x = 1; y = 1;
   } else if (direction == "sw") { 
     x = 1; y = -1;
   } else {   // invalid direction 
     x= 0; y = 0;
  }
  return make_pair(x,y);
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
  pair<int,int> p = convert_direc(direction);
  try {
  	floor->movePlayer(p.first, p.second);
  } catch( const int n) {  // pc reaches staircase
    ++floorNum;
                  //
  }
  printFloor();
}



// use potion in direction
void Controller::usePotion(string direction)  {
  pair<int, int> p = convert_direc(direction);
  if (p.first == 0 && p.second == 0) {
    cout << "Invalid direction" << endl;
  } else {
   // floor->
  }
} 


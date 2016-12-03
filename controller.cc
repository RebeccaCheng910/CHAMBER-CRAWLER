#include "controller.h"
#include <string>
#include <iostream>
#include "floor.h"
#include <fstream>
#include <memory>
#include "character.h"
#include "player.h"
#include "shade.h"

using namespace std;

Controller::Controller(bool useDefault, string fileName):useDefault{useDefault}, file{fileName} {
  floor = nullptr;
  pc = nullptr;
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
    pc = make_shared<Player>(); //
  } else if ( c == 'v') {
    pc = make_shared<Player>();  //
  } else if (c == 't') {
    pc = make_shared<Player>();
  } else if (c == 'g') {
    pc = make_shared<Player>();
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
  cout << " Gold: " << pc->getGold() << endl;
  cout << "HP: " << pc->getHP() << endl;
  cout << "Atk: " << pc->getAtk() << endl;
  cout << "Def: " << pc->getDef() << endl;
  cout << "Action: " << pc->getAction() << endl;
  floor->moveEnemy();
  floor->movePlayer(-1,-1);
	cout << *floor;
}

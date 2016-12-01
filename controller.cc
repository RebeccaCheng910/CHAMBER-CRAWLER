#include "controller.h"
#include <string>
#include <iostream>
#include "floor.h"
#include <fstream>
#include <memory>
#include "character.h"
#include "player.h"

using namespace std;

Controller::Controller() {
  floor = nullptr;
  pc = nullptr;
}

// opens a file and initilize a game
void Controller::startGame(string filename) {

  cout << "Welcome! Please choose a race" << endl;
  cout << "s - Shade" << endl;
  cout << "d - Drow" << endl;
  cout << "v - Vampire" << endl;
  cout << "g - Grblic" << endl;
  cout << "t - Troll" << endl;
  floor = make_shared<Floor>(filename);
}

Controller::~Controller() {
}

// set a PC with no specialized type
void Controller::setRace(char c) {
  if (c == 's') {
    pc = make_shared<Player>();
  } else if (c == 'd') {
    pc = make_shared<Player>(); //
  } else if ( c == 'v') {
    pc = make_shared<Player>();  //
  } else if (c == 't') {
    pc = make_shared<Player>();
  } else if (c == 'g') {
    pc = make_shared<Player>();
  }
  floor->setPlayer(pc);  // set floor's  pc
}

void Controller::printFloor() {
  cout << *floor;
}

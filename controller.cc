#include "controller.h"
#include <string>
#include <iostream>
#include "floor.h"
#include <fstream>

using namespace std;

Controller::Controller() {
  floor = nullptr;
}

void Controller::startGame(string filename) {
  istream *in = new ifstream(filename.c_str());
  std::unique_ptr<Floor> floor(new Floor{n});
}

Controller::~Controller() {
  delete floor;
}

void Controller::printFloor() {
  cout << *floor;
}

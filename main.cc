#include <iostream>
#include <string>
#include "controller.h"
using namespace std;

int main (int argc, char *argv[]) {
  string filename;
  if (argc == 1) { // use default file
    filename = "default.txt";
  }
  else { // read in from file
    filename = argv[1];
  }
  
  Controller controller;
  controller.startGame(filename);
  char race;
  cin >> race;
  controller.setRace(race);
  controller.printFloor();
}    

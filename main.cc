#include <iostream>
#include <string>
#include "controller.h"
using namespace std;

int main (int argc, char *argv[]) {
  string filename;
  bool useDefault;
  if (argc == 1) { // use default file
    filename = "default.txt";
    useDefault = true;
  }
  else { // read in from file
    filename = argv[1];
    useDefault = false;
  }
  
  Controller controller{useDefault, filename};
  controller.startGame();
  char race;
  cin >> race;
  controller.setRace(race);
  controller.setBoard();
  controller.printFloor();
}    

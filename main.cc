#include <iostream>
#include <string>
#include <cstdlib>
#include "controller.h"
#include "time.h"
using namespace std;

int main (int argc, char *argv[]) {
  srand(time(NULL));
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
  controller.setRace(race);  // ask for race
  controller.setBoard();     // generate enemies and items
  
  controller.printFloor();

  // reads input
}    

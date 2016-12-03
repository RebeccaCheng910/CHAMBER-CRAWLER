#include <iostream>
#include <string>
#include <cstdlib>
#include "controller.h"
#include "time.h"
using namespace std;

int main (int argc, char *argv[]) {
  cin.exceptions(ios::failbit|ios::eofbit);
 
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

  // reads command
  string cmd;
  bool status = true;  
  try {
    while (status) {   // game continues    
      cin >> cmd;
      if (cmd == "no"|| cmd == "so"|| cmd == "ea"|| 
       		 cmd == "we"|| cmd == "ne"|| cmd == "nw"|| cmd == "se"|| cmd == "sw") {
      	 controller.move(cmd);
      } else {
       	 cout << "Invalid Command"  << endl;
      }
    } 
  } catch(ios::failure) { } 
 } 

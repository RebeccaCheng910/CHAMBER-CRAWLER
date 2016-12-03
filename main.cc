#include <iostream>
#include <string>
#include <cstdlib>
#include "controller.h"
#include "time.h"
using namespace std;

// helper fucntion, check direction read
bool check_direction(string direction) {
  if (direction == "no"|| direction == "so"|| direction == "ea"||
      direction == "we"|| direction == "ne"|| direction == "nw"|| direction == "se"|| direction == "sw")
    return true;
    return false;
}


int main (int argc, char *argv[]) {
  cin.exceptions(ios::failbit|ios::eofbit);
 
  srand(time(NULL));
  string filename;
  bool useDefault;
  if (argc == 1) { // use default file
    filename = "default.txt";
    useDefault = true;
  }  else { // read in from file
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
  string cmd,direction;
  bool status = true;  
  try {
    while (status) {   // game continues    
      cin >> cmd;
      if (check_direction(cmd)) { // move PC
      	 controller.move(cmd);
      } else if (cmd == "u") {  // use potion
         cin >> direction; 
         if (check_direction(direction)) {
          // controller.usePotion(direction);
         } else {  // direction not valid 
           cout << "Invalid Direction" << endl;
         }
      } else {
       	 cout << "Invalid Command"  << endl;
      }
    } 
  } catch(ios::failure) { } 
} 

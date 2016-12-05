#include <iostream>
#include <string>
#include <cstdlib>
#include "controller.h"
#include "time.h"
#include <memory>
using namespace std;

// construct controller and start a new game
void newGame(Controller *controller) {
	controller->startGame();
	char race;
	cin >> race;
	controller->setRace(race);  // select race
	controller->setBoard();   // generate enemies, golds and potions
	controller->printFloor();
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
  newGame(&controller);

  // reads command
  string cmd,direction;
  bool status = true;
  bool success = true;  
  try {
    while (status) {   // game continues    
      cin >> cmd;
      if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" 
            ||cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") { // move PC
      	 controller.move(cmd);
      } else if (cmd == "u") {  // use potion
         cin >> direction; 
         success = controller.usePotion(direction);
			} else if (cmd == "a") {  // attack enemy
				 cin >> direction;
				 success = controller.attack(direction);
      } else if (cmd == "q") return 1;
        else if (cmd == "r") {
					Controller controller{useDefault, filename};
					newGame(&controller);
			} else {
       	 cout << "Invalid Command"  << endl;
      }
			if (!success) {
				cout << "Enter (q) to quit or (r) to restart." << endl;
				string choice;
				cin >> choice;
				if (choice == "q") return 1;
        else if (choice == "r") {
					Controller controller{useDefault, filename};
          newGame(&controller);
				}
			}		
    } 
  } catch(ios::failure) { } 
} 

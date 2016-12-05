#include <iostream>
#include <string>
#include <cstdlib>
#include "controller.h"
#include "time.h"
#include <memory>
using namespace std;

// construct controller and start a new game
void newGame(const shared_ptr<Controller> &controller) {
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

  shared_ptr<Controller> controller = make_shared<Controller>(useDefault, filename);
	newGame(controller);

  // reads command
  string cmd,direction;
  bool success = true;
	bool move = true;
  
  try {
    while (true) {   // game continues    
			if (!success) {
				  int score = controller->getScore();
					cout << "PC has earned " << score << " scores." << endl;
					cout << "Enter (q) to quit or (r) to restart." << endl; 
          string choice;
					cin >> choice;
					 if (choice == "q") return 1;
					 else if (choice == "r") {
						controller = make_shared<Controller>(useDefault, filename);
						newGame(controller);
					 }
			}
      cin >> cmd;
      if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" 
            ||cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") { // move PC 
					success = controller->move(move, cmd);
      } else if (cmd == "u") {  // use potion
         cin >> direction; 
         success = controller->usePotion(direction);
			} else if (cmd == "a") {  // attack enemy
				 cin >> direction;
				 success = controller->attack(direction);
      } else if (cmd == "q") return 1;
        else if (cmd == "r") {
					controller = make_shared<Controller>(useDefault, filename);
					newGame(controller);
			} else if ((cmd == "f") && (move == true)){
					move = false;
					controller->printFloor();
			} else if ((cmd == "f") && (move == false)) {
					move = true;
					controller->printFloor();
			} else {
       	 cout << "Invalid Command"  << endl;
      }
		}	 
  } catch(ios::failure) { } 
}

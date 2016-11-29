#include <iostream> 
#include <string>
using namespace std;

int main (int argc, char *argv[]) {
  string filename = "";
  if (argc == 1) {  // use default file
    filename = "default.txt";
  }
  else {  // read in from a given file
    filename = argv[1];
  }
  
  Controller c;  
  c.startGame(filename);   // start new game
  char race;
  cin >> race;
  c.setPlayer(race);
  
  int count;   // control movements of enemy  
  bool status = true;
  string input, direction;
  
  while (status) {
    cout << "Enter your command : " << endl;
    cin >> input;
    if (input == "r") {
      cerr << "New Game." << endl;
      c.restartGame();
      cin >> race;
      c.setPlayer(race);
    }
    else if (input == "q") {
      cerr << "Defeated." << endl;
      c.exitGame();
      break;
    }
    else if ((input == "f") && (count == 0)) {
      cerr << "Enemies are stopped" << endl;
      count++;
      c.stopEnermy();
    }
    else if ((input == "f") && (count == 1)) {
      cerr << "Enemies start moving" << endl;
      count--;
      c.startEnermy();
    }
    else if ((input == "a") || (input == "u")) {
      cin >> direction;
      if (dirction == ("no"||"so"||"ea"||"we"||"ne"||"nw"||"se"||"sw")) {
        if (input == "a") c.atkEnemy(direction);
        else c.usePotion(direction);
      }
      else cerr << "Invalid direction" << endl;
    }
    else if (input == ("no"||"so"||"ea"||"we"||"ne"||"nw"||"se"||"sw")) {
      c.movePlayer(input);
    }
    else cout << "Invalid Command" << endl;
    
    status = (! c.gameOver());
}
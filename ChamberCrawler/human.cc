#include "human.h"
#include "enemy.h"
#include <string>
 
using namespace std;
 
Human::Human(int row, int col, char type): Enemy{row, col,type} {
  HP = 140;
  Atk = 20;
  Def = 20;
}
  
Human::~Human() {}


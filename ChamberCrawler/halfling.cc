#include "halfling.h"
#include <string>
 
using namespace std;
 
Halfling::Halfling(int row, int col, char type): Enemy{row, col,type} {
  HP = 100;
  Atk = 15;
  Def = 20;
}
  
Halfling::~Halfling() {}


#include "orcs.h"
#include <string>
 
using namespace std;
 
Orcs::Orcs(int row, int col, char type): Enemy{row, col,type} {
  HP = 180;
  Atk = 30;
  Def = 25;
}
  
Orcs::~Orcs() {}

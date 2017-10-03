#include "dwarf.h"
#include <string>
 
using namespace std;
 
Dwarf::Dwarf(int row, int col, char type): Enemy{row, col,type} {
  HP = 100;
  Atk = 20;
  Def = 30;
}
  
Dwarf::~Dwarf() {}

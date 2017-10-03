#include "elf.h"
#include <string>
 
using namespace std;
 
Elf::Elf(int row, int col, char type): Enemy{row, col,type} {
  HP = 140;
  Atk = 30;
  Def = 10;
}
  
Elf::~Elf() {}
 

#ifndef _DWARF_H_
#define _DWARF_H_
   
#include "enemy.h"
#include <string> 
   
class Dwarf: public Enemy {
public:
  Dwarf(int, int, char);
 ~Dwarf();
}; 

#endif

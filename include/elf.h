#ifndef _ELF_H_
#define _ELF_H_
   
#include "enemy.h"
#include <string>
   
   
   
class Elf: public Enemy {
public:
  Elf(int, int, char);
 ~Elf();
}; 

#endif

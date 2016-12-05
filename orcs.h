#ifndef _ORCS_H_
#define _ORCS_H_
   
#include "enemy.h"
#include <string>   
  
   
class Orcs: public Enemy {
public:
  Orcs(int, int, char);
 ~Orcs();
}; 

#endif


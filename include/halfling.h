#ifndef _HALFLING_H_
#define _HALFLING_H_
   
#include "enemy.h"
#include <string> 
   
class Halfling: public Enemy {
public:
  Halfling(int, int, char);
 ~Halfling();
}; 

#endif


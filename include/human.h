#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "enemy.h"   
#include <string>
   
   
   
class Human: public Enemy {
public:
	Human(int, int, char);
	~Human();
}; 

#endif

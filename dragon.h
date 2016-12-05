#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"
#include <string>



class Dragon: public Enemy {
public:
	Dragon(int, int, char);
  ~Dragon();
};

#endif 


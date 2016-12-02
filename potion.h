#ifndef _POTION_H_
#define _POTION_H_
#include "object.h"
#include <string>

class Potion: public Object {
	int type;
	int effectHP;
	int effectAtk;
  int effectDef;
public:
	Potion(int, int, char, int);
  ~Potion();	
	int getType();
	int getEffectHP();
	int getEffectAtk();
  int getEffectDef();
};

#endif


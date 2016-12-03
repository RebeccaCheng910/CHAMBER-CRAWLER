#ifndef _POTION_H_
#define _POTION_H_
#include "object.h"
#include <string>

class Potion: public Object {
	int type;
	int effectHP = 0;
        int effectAtk = 0;
        int effectDef = 0;
public:
	Potion(int, int, int);
        ~Potion();	
	int getType();
	int getEffectHP();
	int getEffectAtk();
        int getEffectDef();
};

#endif


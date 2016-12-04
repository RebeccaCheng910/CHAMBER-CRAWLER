#ifndef _POTION_H_
#define _POTION_H_
#include "object.h"
#include <string>

class Potion: public Object {
	int type;
	std::string name;
public:
	Potion(int, int, int);
        ~Potion();	
	int getType();
	std::string getName();
};

#endif


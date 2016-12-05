#ifndef _POTION_H_
#define _POTION_H_
#include "object.h"
#include <string>

class Potion: public Object {
	int type;
protected:
	std::string name;
public:
	Potion(int, int, int);
        virtual ~Potion() = 0;	
	int getType();
	std::string getName();
	static bool isKnown();  //
};

#endif


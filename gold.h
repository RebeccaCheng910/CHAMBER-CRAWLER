#ifndef _GOLD_H_
#define _GOLD_H_
#include "object.h"
#include <string>

class Gold:public Object {
  int value;
	bool isProtected;
public:
	Gold (int, int, char, int, bool);
	~Gold();
	int getValue();
	bool getGold();
};

#endif


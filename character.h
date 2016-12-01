#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"

class Character: public Object{
protected:
  int HP, Atk, Def;
public:
  Character(char c);
  
};

#endif

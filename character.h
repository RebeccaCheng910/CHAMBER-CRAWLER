#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"

class Character: public Object{
protected:
  int HP, Atk, Def;
public:
  Character(int, int, char);
  virtual int getHP() = 0;    // get character's HP
  virtual int getAtk() = 0;   // get character's Atk
  virtual int getDef() = 0;   // get character's Def
};

#endif

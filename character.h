#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"

// abstract class
class Character: public Object{
protected:
  int HP, Atk, Def;
  std::string race;
public:
  Character(int, int, char);
  virtual int getHP();    // get character's HP
  virtual void setHP(int);   // set character's HP
	virtual int getAtk();   // get character's Atk
  virtual int getDef();  // get character's Def
  virtual std::string getRace();     // get character's racee
  virtual ~Character() = 0;   
};

#endif

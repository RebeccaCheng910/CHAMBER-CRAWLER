#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"

class Enemy:public Character{
public:
  Enemy(int, int);
  int getHP() override;
  int getAtk() override;
  int getDef() override;
};

#endif

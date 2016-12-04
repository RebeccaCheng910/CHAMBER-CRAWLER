#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"
#include <memory>

class Player;

class Enemy:public Character{
	bool hasMoved;
public:
  Enemy(int, int);
  int getMove();
  void setMove(bool);
  int getHP() override;
  int getAtk() override;
  int getDef() override;
  virtual bool beAttackedBy(shared_ptr<Player> &);
};

#endif

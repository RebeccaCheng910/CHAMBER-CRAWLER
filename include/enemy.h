#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"
#include <memory>
#include <string>

class Player;

class Enemy:public Character{
	bool hasMoved;
public:
  Enemy(int, int, char);
  virtual int getMove();
  virtual void setMove(bool);
  virtual bool beAttackedBy(const std::shared_ptr<Player> &);
};

#endif

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

class Player: public Character {
public:
  Player(); // constructor
  int getHP() override;
  int getAtk() override;
  int getDef() override;
};

#endif
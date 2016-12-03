#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include <string>

class Player: public Character {
  int goldValue = 0;
  std::string action;
public:
  Player(); // constructor
  int getHP() override;
  int getAtk() override;
  int getDef() override;
  std::string getAction();
  void setAction(std::string);
  virtual int getGold();   // goblin needs to overload
  virtual ~Player() = 0;   // to make Player abstract
};

#endif

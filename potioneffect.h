#ifndef _POTIONEFFECT_H_
#define _POTIONEFFECT_H_

#include "decorator.h"
#include <memory>

class Player;

class PotionEffect: public Decorator {
  int effectAtk = 0;
  int effectDef = 0;


public:
  PotionEffect(int, std::shared_ptr<Player>);   //constructor
  int getHP() override;
  int getAtk() override;
  int getDef() override;
};

#endif

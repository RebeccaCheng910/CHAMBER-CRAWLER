#include "shade.h"
#include "player.h"

// constructor
Shade::Shade(): Player() {
  HP = 125;
  Atk = 25;
  Def = 25;
  race = "Shade";
  maxHP = 125;
}

//int Shade::getHP() {return HP;}
//int Shade::getAtk() {return Atk;}
//int Shade::getDef() { return Def;}

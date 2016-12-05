#include "shade.h"
#include "player.h"
#include <memory> 

using namespace std;

// constructor
Shade::Shade(): Player() {
  HP = 125;
  Atk = 25;
  Def = 25;
  race = "Shade";
  maxHP = 125;
}

shared_ptr<Player> Shade::getBase() {
	return shared_from_this();
}

//int Shade::getHP() {return HP;}
//int Shade::getAtk() {return Atk;}
//int Shade::getDef() { return Def;}

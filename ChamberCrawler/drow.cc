#include "drow.h"
#include "player.h"
#include <memory>

using namespace std;

// constructor
Drow::Drow(): Player() {
  HP = 150;
  Atk = 25;
  Def = 15;
  race = "Drow";
  maxHP = 150;
}

shared_ptr<Player> Drow::getBase() {
	return shared_from_this();
}

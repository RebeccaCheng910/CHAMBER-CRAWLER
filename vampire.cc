#include "vampire.h"
#include "player.h"
#include <memory>
#include <climits>

using namespace std;

// constructor
Vampire::Vampire(): Player() {
  HP = 50;
  Atk = 25;
  Def = 25;
  race = "Vampire";
  maxHP = INT_MAX;
}

shared_ptr<Player> Vampire::getBase() {
	return shared_from_this();
}

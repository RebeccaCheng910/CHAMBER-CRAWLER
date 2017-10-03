#include "troll.h"
#include "player.h"
#include <memory>

using namespace std;

Troll::Troll(): Player() {
  HP = 120;
  Atk = 25;
  Def = 15;
  race = "Troll";
  maxHP = 120;
}

shared_ptr<Player> Troll::getBase() {
  return shared_from_this();
}

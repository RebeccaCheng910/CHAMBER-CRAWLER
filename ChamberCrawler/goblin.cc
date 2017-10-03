#include "goblin.h"
#include "player.h"
#include <memory>

using namespace std;

Goblin::Goblin(): Player() {
  HP =110;
  Atk = 15;
  Def = 20;
  maxHP= 110;
}

shared_ptr<Player> Goblin::getBase() {
  return shared_from_this();
}

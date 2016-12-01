 #include "player.h"

// constructor
Player::Player(): Character(0, 0, '@') {  // need to explicitly sets player's position
  HP = 125;
  Atk = 25;
  Def = 25;
}


int Player::getHP() {return HP;}
int Player::getAtk() {return Atk;}
int Player::getDef() { return Def;}

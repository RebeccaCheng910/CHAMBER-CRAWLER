#include "player.h"
#include <string>

using namespace std;

// constructor
Player::Player(): Character(0, 0, '@'),action{"Player character has spawned."} { 
 // need to explicitly sets player's position
}


int Player::getHP() {return HP;}
int Player::getAtk() {return Atk;}
int Player::getDef() { return Def;}
string Player::getAction() {return action;}
int Player::getGold() {return goldValue;}

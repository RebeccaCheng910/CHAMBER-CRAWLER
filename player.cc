#include "player.h"
#include <memory>
#include "enemy.h"
#include "info.h"
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

// constructor
Player::Player(): Character(0, 0, '@'),action{"Player character has spawned."} { 
 // need to explicitly sets player's position
}


int Player::getHP() {return HP;}
int Player::getAtk() {return Atk;}
int Player::getDef() { return Def;}
string Player::getAction() {return action;}
void Player::setAction(string s) {action = s;}
int Player::getGold() {return goldValue;}

void Player::beAttackedBy(const shared_ptr<Enemy> &e) {
	int atk = e->getAtk();
	int def = e->getDef();
  // damage calculation
	double d = (100 + def);
  d = (100 / d);
  d = d * atk;
  double damage = ceil(d);
	int attack1 = rand() % 2;  // chance of successful attack is 50% 
  
  bool second = false; // elf's ability to attack twice
  int attack2 = rand() % 2; 

	char symbol = e->getInfo().type;

  if ((symbol == 'O') && (race == "Goblins")) {damage *= 1.5;}
  if ((symbol == 'E') && (race != "Drow")) {second = true;}
  // attack 
  stringstream s;
  if (attack1 == 0) {
		HP -= damage;
		s << symbol << " deals " << damage << " damage to PC. ";
  } else {
    s << symbol << " missed the attack. ";
  } 
  if (second && (attack2 == 0)) {
		HP -= damage;
    s << symbol << " deals " << damage << " damage to PC again. ";
  }
  setAction(getAction() + s.str());
  
  if (HP <= 0) {HP = 0;}
} 
    
  	
Player::~Player() {};  // virtual constructor


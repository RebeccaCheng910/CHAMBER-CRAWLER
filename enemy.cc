#include "enemy.h"
#include "character.h"
#include "player.h"
#include "info.h"
#include <cmath>
#include <cstdlib>
#include <memory>
#include <string>
#include <sstream>

using namespace std;

Enemy::Enemy(int row, int col, char type): Character{row, col,type} {
  HP = 140;  //human
  Atk = 20;
  Def = 20;
  hasMoved = false;
}

int Enemy::getMove() {return hasMoved;}
void Enemy::setMove(bool move) {hasMoved = move;}


bool Enemy::beAttackedBy(const shared_ptr<Player> &pc) {
	int atk = pc->getAtk();
	int def = pc->getDef();
	double d = (100 + def);
	d = (100 / d);
	d = d * atk;
  double damage = ceil(d);
  stringstream s;
	int chance = rand() % 2;
	if ((getInfo().type == 'L') && (chance == 0)) {    // when halfling causes pc to miss the attack 
		s << "PC missed " << getInfo().type << " (" << HP << " HP). ";
	} else {
		HP -= damage;
    if (HP <= 0) {HP = 0;}
		s << "PC deals " << damage << " damage to " << getInfo().type << " (" << HP << " HP). ";
  }
  
  pc->setAction(s.str());
  
	if (HP == 0) {
    return true;
	} 
		return false;
}

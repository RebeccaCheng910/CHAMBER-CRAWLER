#include "enemy.h"
#include "character.h"
#include <cmath>
#include <cstdlib>
#include <memory>

using namespace std;

Enemy::Enemy(int row, int col): Character{row, col,'E'} {
  HP = 140;  //human
  Atk = 20;
  Def = 20;
  hasMoved = false;
}

int Enemy::getMove() {return hasMoved;}
void Enemy::setMove(bool move) {hasMoved = move;}
int Enemy::getHP() { return HP;}
int Enemy::getAtk() {return Atk;}
int Enemy::getDef() {return Def;}

bool Enemy::beAttackedBy(shared_ptr<Player> pc) {
	int atk = pc->getAtk();
	int def = pc->getDef();
	double damage = ceil((100 / (100 + def)) * atk);
	HP -= damage;
  pcAction = "PC deals " + damage + " damage to " + getInfo().type + ". ";
	pc->setAction(pcAction);

	if (HP <= 0) {
		HP = 0;
    pc->setAction("PC slained the Enemy. ")
		return true;
	} else {
		return false;
	}
}

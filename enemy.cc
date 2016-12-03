#include "enemy.h"
#include "character.h"

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
